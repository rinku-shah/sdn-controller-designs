/*
 * Copyright 2017-present Open Networking Foundation
**
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.onosproject.drivers.p4runtime;

import com.google.common.cache.CacheBuilder;
import com.google.common.cache.CacheLoader;
import com.google.common.cache.LoadingCache;
import com.google.common.collect.ImmutableList;
import com.google.common.collect.Lists;
import io.grpc.StatusRuntimeException;
import org.onlab.util.SharedExecutors;
import org.onosproject.drivers.p4runtime.mirror.P4RuntimeTableMirror;
import org.onosproject.drivers.p4runtime.mirror.TimedEntry;
import org.onosproject.net.flow.DefaultFlowEntry;
import org.onosproject.net.flow.FlowEntry;
import org.onosproject.net.flow.FlowRule;
import org.onosproject.net.flow.FlowRuleProgrammable;
import org.onosproject.net.pi.model.PiPipelineInterpreter;
import org.onosproject.net.pi.model.PiPipelineModel;
import org.onosproject.net.pi.model.PiTableId;
import org.onosproject.net.pi.model.PiTableModel;
import org.onosproject.net.pi.runtime.PiCounterCellData;
import org.onosproject.net.pi.runtime.PiCounterCellId;
import org.onosproject.net.pi.runtime.PiTableEntry;
import org.onosproject.net.pi.runtime.PiTableEntryHandle;
import org.onosproject.net.pi.service.PiFlowRuleTranslator;
import org.onosproject.net.pi.service.PiTranslatedEntity;
import org.onosproject.net.pi.service.PiTranslationException;
import org.onosproject.p4runtime.api.P4RuntimeClient.WriteOperationType;

import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.Collectors;

import static com.google.common.collect.Lists.newArrayList;
import static org.onosproject.drivers.p4runtime.P4RuntimeFlowRuleProgrammable.Operation.APPLY;
import static org.onosproject.drivers.p4runtime.P4RuntimeFlowRuleProgrammable.Operation.REMOVE;
import static org.onosproject.net.flow.FlowEntry.FlowEntryState.ADDED;
import static org.onosproject.p4runtime.api.P4RuntimeClient.WriteOperationType.DELETE;
import static org.onosproject.p4runtime.api.P4RuntimeClient.WriteOperationType.INSERT;
import static org.onosproject.p4runtime.api.P4RuntimeClient.WriteOperationType.MODIFY;

/**
 * Implementation of the flow rule programmable behaviour for P4Runtime.
 */
public class P4RuntimeFlowRuleProgrammable
        extends AbstractP4RuntimeHandlerBehaviour
        implements FlowRuleProgrammable {

    // When updating an existing rule, if true, we issue a DELETE operation
    // before inserting the new one, otherwise we issue a MODIFY operation. This
    // is useful fore devices that do not support MODIFY operations for table
    // entries.
    private static final String DELETE_BEFORE_UPDATE = "tableDeleteBeforeUpdate";
    private static final boolean DEFAULT_DELETE_BEFORE_UPDATE = false;

    // If true, we ignore re-installing rules that already exist in the
    // device mirror, i.e. same match key and action.
    private static final String IGNORE_SAME_ENTRY_UPDATE = "tableIgnoreSameEntryUpdate";
    private static final boolean DEFAULT_IGNORE_SAME_ENTRY_UPDATE = false;

    // If true, we avoid querying the device and return what's already known by
    // the ONOS store.
    private static final String READ_FROM_MIRROR = "tableReadFromMirror";
    private static final boolean DEFAULT_READ_FROM_MIRROR = false;

    // If true, we read counters when reading table entries (if table has
    // counters). Otherwise, we don't.
    private static final String SUPPORT_TABLE_COUNTERS = "supportTableCounters";
    private static final boolean DEFAULT_SUPPORT_TABLE_COUNTERS = true;

    // If true, we read all direct counters of a table with one request.
    // Otherwise, we send as many requests as the number of table entries.
    private static final String READ_ALL_DIRECT_COUNTERS = "tableReadAllDirectCounters";
    // FIXME: set to true as soon as the feature is implemented in P4Runtime.
    private static final boolean DEFAULT_READ_ALL_DIRECT_COUNTERS = false;

    private static final int TABLE_ENTRY_LOCK_EXPIRE_TIME_IN_MIN = 10;

    private static final boolean DEBUG_FLAG = false;

    // Needed to synchronize operations over the same table entry.
    private static final LoadingCache<PiTableEntryHandle, Lock>
            ENTRY_LOCKS = CacheBuilder.newBuilder()
            .expireAfterAccess(TABLE_ENTRY_LOCK_EXPIRE_TIME_IN_MIN, TimeUnit.MINUTES)
            .build(new CacheLoader<PiTableEntryHandle, Lock>() {
                @Override
                public Lock load(PiTableEntryHandle handle) {
                    return new ReentrantLock();
                }
            });
    private PiPipelineModel pipelineModel;
    private PiPipelineInterpreter interpreter;
    private P4RuntimeTableMirror tableMirror;
    private PiFlowRuleTranslator translator;

    @Override
    protected boolean setupBehaviour() {

        if (!super.setupBehaviour()) {
            return false;
        }

        if (!device.is(PiPipelineInterpreter.class)) {
            log.warn("Unable to get interpreter of {}", deviceId);
            return false;
        }
        interpreter = device.as(PiPipelineInterpreter.class);
        pipelineModel = pipeconf.pipelineModel();
        tableMirror = handler().get(P4RuntimeTableMirror.class);
        translator = piTranslationService.flowRuleTranslator();
        return true;
    }

    @Override
    public Collection<FlowEntry> getFlowEntries() {

        if (!setupBehaviour()) {
            return Collections.emptyList();
        }

        if (driverBoolProperty(READ_FROM_MIRROR, DEFAULT_READ_FROM_MIRROR)) {
            return getFlowEntriesFromMirror();
        }

        final ImmutableList.Builder<FlowEntry> result = ImmutableList.builder();
        final List<PiTableEntry> inconsistentEntries = Lists.newArrayList();

        for (PiTableModel tableModel : pipelineModel.tables()) {

            final PiTableId piTableId = tableModel.id();

            // Read table entries.
            final Collection<PiTableEntry> installedEntries;
            try {
                // TODO: optimize by dumping entries and counters in parallel
                // From ALL tables with the same request.
                installedEntries = client.dumpTable(piTableId, pipeconf).get();
            } catch (InterruptedException | ExecutionException e) {
                if (!(e.getCause() instanceof StatusRuntimeException)) {
                    // gRPC errors are logged in the client.
                    log.error("Exception while dumping table {} of {}",
                              piTableId, deviceId, e);
                }
                continue; // next table
            }

            if (installedEntries.size() == 0) {
                continue; // next table
            }

            // Read table direct counters (if any).
            final Map<PiTableEntry, PiCounterCellData> counterCellMap =
                    readEntryCounters(installedEntries);

            // Forge flow entries with counter values.
            for (PiTableEntry installedEntry : installedEntries) {

                final FlowEntry flowEntry = forgeFlowEntry(
                        installedEntry, counterCellMap.get(installedEntry));

                if (flowEntry == null) {
                    // Entry is on device but unknown to translation service or
                    // device mirror. Inconsistent. Mark for removal.
                    // TODO: make this behaviour configurable
                    // In some cases it's fine for the device to have rules
                    // that were not installed by us.
                    inconsistentEntries.add(installedEntry);
                } else {
                    result.add(flowEntry);
                }
            }
        }

        if (inconsistentEntries.size() > 0) {
            // Async clean up inconsistent entries.
            SharedExecutors.getSingleThreadExecutor().execute(
                    () -> cleanUpInconsistentEntries(inconsistentEntries));
        }

        return result.build();
    }

    @Override
    public Collection<FlowRule> applyFlowRules(Collection<FlowRule> rules) {
        if(DEBUG_FLAG){
            log.info("!!!!!!!!!!!!!!!!!!!!!!!! inside applyFlowRules");
        }
        return processFlowRules(rules, APPLY);
    }

    @Override
    public Collection<FlowRule> removeFlowRules(Collection<FlowRule> rules) {
        if(DEBUG_FLAG){
                log.info("######################## inside removeFlowRules");
        }

        return processFlowRules(rules, REMOVE);
    }

    private FlowEntry forgeFlowEntry(PiTableEntry entry,
                                     PiCounterCellData cellData) {
        final PiTableEntryHandle handle = PiTableEntryHandle
                .of(deviceId, entry);
        final Optional<PiTranslatedEntity<FlowRule, PiTableEntry>>
                translatedEntity = translator.lookup(handle);
        final TimedEntry<PiTableEntry> timedEntry = tableMirror.get(handle);

        if (!translatedEntity.isPresent()) {
            log.debug("Handle not found in store: {}", handle);
            return null;
        }

        if (timedEntry == null) {
            log.debug("Handle not found in device mirror: {}", handle);
            return null;
        }

        if (cellData != null) {
            return new DefaultFlowEntry(translatedEntity.get().original(),
                                        ADDED, timedEntry.lifeSec(), cellData.packets(),
                                        cellData.bytes());
        } else {
            return new DefaultFlowEntry(translatedEntity.get().original(),
                                        ADDED, timedEntry.lifeSec(), 0, 0);
        }
    }

    private Collection<FlowEntry> getFlowEntriesFromMirror() {
        return tableMirror.getAll(deviceId).stream()
                .map(timedEntry -> forgeFlowEntry(
                        timedEntry.entry(), null))
                .collect(Collectors.toList());
    }

    private void cleanUpInconsistentEntries(Collection<PiTableEntry> piEntries) {
        // log.warn("Found {} entries from {} not on translation store, removing them...",
                //  piEntries.size(), deviceId);
        //piEntries.forEach(entry -> {
          //  log.debug(entry.toString());
            //applyEntry(PiTableEntryHandle.of(deviceId, entry),
              //       entry, null, REMOVE);
       // });
    }

    private Collection<FlowRule> processFlowRules(Collection<FlowRule> rules,
                                                  Operation driverOperation) {

        if (!setupBehaviour()) {
            return Collections.emptyList();
        }

        final ImmutableList.Builder<FlowRule> result = ImmutableList.builder();

        // TODO: send writes in bulk (e.g. all entries to insert, modify or delete).
        // Instead of calling the client for each one of them.

        for (FlowRule ruleToApply : rules) {

            final PiTableEntry piEntryToApply;
            try {
                piEntryToApply = translator.translate(ruleToApply, pipeconf);
            } catch (PiTranslationException e) {
                //log.warn("Unable to translate flow rule for pipeconf '{}': {} - {}",
                 //        pipeconf.id(), e.getMessage(), ruleToApply);
                // Next rule.
                continue;
            }

            final PiTableEntryHandle handle = PiTableEntryHandle
                    .of(deviceId, piEntryToApply);

            // Serialize operations over the same match key/table/device ID.
            ENTRY_LOCKS.getUnchecked(handle).lock();
            try {
                if (applyEntry(handle, piEntryToApply,
                               ruleToApply, driverOperation)) {
                    result.add(ruleToApply);
                }
            } finally {
                ENTRY_LOCKS.getUnchecked(handle).unlock();
            }
        }

        return result.build();
    }

    /**
     * Applies the given entry to the device, and returns true if the operation
     * was successful, false otherwise.
     */
    private boolean applyEntry(PiTableEntryHandle handle,
                               PiTableEntry piEntryToApply,
                               FlowRule ruleToApply,
                               Operation driverOperation) {
        // Depending on the driver operation, and if a matching rule exists on
        // the device, decide which P4 Runtime write operation to perform for
        // this entry.
        final TimedEntry<PiTableEntry> piEntryOnDevice = tableMirror.get(handle);
        final WriteOperationType p4Operation;
        if (driverOperation == APPLY) {
            //if (piEntryOnDevice == null) {
                // Entry is first-timer.
                //p4Operation = INSERT;
            //} else {
              //  if (driverBoolProperty(IGNORE_SAME_ENTRY_UPDATE,
                //                       DEFAULT_IGNORE_SAME_ENTRY_UPDATE)
                  //      && piEntryToApply.action().equals(piEntryOnDevice.entry().action())) {
                   // log.debug("Ignoring re-apply of existing entry: {}", piEntryToApply);
                   // p4Operation = null;
                //} else if (driverBoolProperty(DELETE_BEFORE_UPDATE,
                  //                            DEFAULT_DELETE_BEFORE_UPDATE)) {
                    // Some devices return error when updating existing
                    // entries. If requested, remove entry before
                    // re-inserting the modified one.
                    // applyEntry(handle, piEntryOnDevice.entry(), null, REMOVE);
                    //applyEntry(handle, piEntryToApply, null, REMOVE);
                    //p4Operation = INSERT;
                //} else {

            // @offload design: do MODIFY for ip_op_s1_uplink and ip_op_s2_downlink as the entries are not removed by delete 
            // for tun_egress_s3_uplink we still need to insert as teid differs and we match on te_id
             PiTableId tun_egress = PiTableId.of("c_ingress.uekey_uestate_map");
            if(DEBUG_FLAG){

		 log.info("tun_egress = {}",tun_egress);
            log.info("piEntryToApply.table() = {} ",piEntryToApply.table());
             //log.info("entry = {}",entry);
		}
             if(tun_egress.equals(piEntryToApply.table())){
                 //log.info("inside if1");
                 p4Operation = MODIFY;
             }
             else{
                 p4Operation = INSERT;
             }
               // }
            //}
        } else {
            p4Operation = DELETE;
        }
        if(DEBUG_FLAG){
                log.info("p4Operation = {}",p4Operation);
        }
        if (p4Operation != null) {
            if (writeEntry(piEntryToApply, p4Operation)) {
                if(DEBUG_FLAG){
                    //log.info("########################{} operation done on piEntrytoApply= {}",p4Operation,piEntryToApply);

                }
        // @offload : lets not update stores ans see the beahviour
                // updateStores(handle, piEntryToApply, ruleToApply, p4Operation);
                return true;
            } else {
                if(DEBUG_FLAG){
                    log.info("########################{} operation failed for entry {}",p4Operation,piEntryToApply);
                }
                return false;
            }
        } else {
            // If no operation, let's pretend we applied the rule to the device.
            return true;
        }
    }

    /**
     * Performs a write operation on the device.
     */
    private boolean writeEntry(PiTableEntry entry,
                               WriteOperationType p4Operation) {
        try {
            if (client.writeTableEntries(
                    newArrayList(entry), p4Operation, pipeconf).get()) {
                return true;
            } else {
                // log.warn("Unable to {} table entry in {}: {}",
                        //  p4Operation.name(), deviceId, entry);
            }
        } catch (InterruptedException | ExecutionException e) {
            log.warn("Exception while performing {} table entry operation:",
                     p4Operation, e);
        }
        return false;
    }

    private void updateStores(PiTableEntryHandle handle,
                              PiTableEntry entry,
                              FlowRule rule,
                              WriteOperationType p4Operation) {
        switch (p4Operation) {
            case INSERT:
            case MODIFY:
                tableMirror.put(handle, entry);
                translator.learn(handle, new PiTranslatedEntity<>(rule, entry, handle));
                break;
            case DELETE:
                tableMirror.remove(handle);
                translator.forget(handle);
                break;
            default:
                throw new IllegalArgumentException(
                        "Unknown operation " + p4Operation.name());
        }
    }

    private Map<PiTableEntry, PiCounterCellData> readEntryCounters(
            Collection<PiTableEntry> tableEntries) {
        if (!driverBoolProperty(SUPPORT_TABLE_COUNTERS,
                                DEFAULT_SUPPORT_TABLE_COUNTERS)) {
            return Collections.emptyMap();
        }

        Collection<PiCounterCellData> cellDatas;
        try {
            if (driverBoolProperty(READ_ALL_DIRECT_COUNTERS,
                                   DEFAULT_READ_ALL_DIRECT_COUNTERS)) {
                // FIXME: re-implement reading all counters ONOS-7595, or
                // (even better) read counters when dumping table entries ONOS-7596
                // cellDatas = client.readAllCounterCells(
                //        singleton(counterId), pipeconf).get();
                cellDatas = Collections.emptyList();
            } else {
                Set<PiCounterCellId> cellIds = tableEntries.stream()
                        .filter(e -> tableHasCounter(e.table()))
                        .map(PiCounterCellId::ofDirect)
                        .collect(Collectors.toSet());
                cellDatas = client.readCounterCells(cellIds, pipeconf).get();
            }
            return cellDatas.stream()
                    .collect(Collectors.toMap(c -> c.cellId().tableEntry(), c -> c));
        } catch (InterruptedException | ExecutionException e) {
            if (!(e.getCause() instanceof StatusRuntimeException)) {
                // gRPC errors are logged in the client.
                log.error("Exception while reading table counters from {}: {}",
                          deviceId, e);
            }
            return Collections.emptyMap();
        }
    }

    private boolean tableHasCounter(PiTableId tableId) {
        return pipelineModel.table(tableId).isPresent() &&
                !pipelineModel.table(tableId).get().counters().isEmpty();
    }

    enum Operation {
        APPLY, REMOVE
    }
}
