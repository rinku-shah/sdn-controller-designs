/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/mem_atomic.h>
#include <nfp/mem_ring.h>
#include <nfp/me.h>
#include <nfp/cls.h>
#include "pif_common.h"
#include "pkt_clone.h"

#ifdef PIF_DEBUG
    __export __emem_n(0) uint64_t pif_act_stats[PIF_ACTION_ID_MAX + 1];
#endif

extern __nnr uint32_t calc_fld_bmsk;

#define BITRANGE(var, width, offset) \
    (((var) >> (offset)) & ((1 << (width)) - 1))


static int pif_action_exec_ingress__act_8(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_8 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_8 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_8");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_8");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__fwd_act(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__fwd_act *_pif_act_data = (__xread struct pif_action_actiondata_ingress__fwd_act *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__fwd_act");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__fwd_act");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,prt) */

        /* primitive body */
        standard_metadata->egress_spec = _pif_act_data->prt;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_9(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_9 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_9 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_initial_ctxt_setup_resp *initial_ctxt_setup_resp;
    __lmem struct pif_header_tmpreg *tmpreg;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_9");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_9");
#endif

    initial_ctxt_setup_resp = (__lmem struct pif_header_initial_ctxt_setup_resp *) (_pif_parrep + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW);
    tmpreg = (__lmem struct pif_header_tmpreg *) (_pif_parrep + PIF_PARREP_tmpreg_OFF_LW);

    {
        /* modify_field(tmpreg.ue_key,initial_ctxt_setup_resp.ue_key) */

        /* primitive body */
        tmpreg->ue_key = (initial_ctxt_setup_resp->ue_key << 16) | initial_ctxt_setup_resp->__ue_key_1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_0(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_0 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_0 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_0");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_0");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0000) */

        /* primitive body */
        standard_metadata->egress_spec = 0x0;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_1(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_1 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_1 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_1");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_1");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_2(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_2 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_2 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_2");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_2");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0000) */

        /* primitive body */
        standard_metadata->egress_spec = 0x0;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_3(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_3 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_3 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_3");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_3");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_4(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_4 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_4 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_4");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_4");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(scalars.hasReturned_0,0) */

        /* primitive body */
        scalars->hasReturned_0 = 0x0;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_5(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_5 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_5 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_5");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_5");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_6(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_6 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_6 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_6");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_6");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0300) */

        /* primitive body */
        standard_metadata->egress_spec = 0x300;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_7(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_7 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_7 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_tmpreg *tmpreg;
    __lmem struct pif_header_ue_context_rel_req *ue_context_rel_req;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_7");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_7");
#endif

    tmpreg = (__lmem struct pif_header_tmpreg *) (_pif_parrep + PIF_PARREP_tmpreg_OFF_LW);
    ue_context_rel_req = (__lmem struct pif_header_ue_context_rel_req *) (_pif_parrep + PIF_PARREP_ue_context_rel_req_OFF_LW);

    {
        /* modify_field(tmpreg.ue_key,ue_context_rel_req.ue_num) */

        /* primitive body */
        tmpreg->ue_key = (ue_context_rel_req->ue_num << 16) | ue_context_rel_req->__ue_num_1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__populate_ip_op_tun_s2_downlink(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__populate_ip_op_tun_s2_downlink *_pif_act_data = (__xread struct pif_action_actiondata_ingress__populate_ip_op_tun_s2_downlink *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_tmpreg *tmpreg;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__populate_ip_op_tun_s2_downlink");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__populate_ip_op_tun_s2_downlink");
#endif

    tmpreg = (__lmem struct pif_header_tmpreg *) (_pif_parrep + PIF_PARREP_tmpreg_OFF_LW);

    {
        /* modify_field(tmpreg.tmp_index,egress_port_s2) */

        /* primitive body */
        tmpreg->tmp_index = _pif_act_data->egress_port_s2;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__populate_service_req_uekey_sgwteid_map(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__populate_service_req_uekey_sgwteid_map *_pif_act_data = (__xread struct pif_action_actiondata_ingress__populate_service_req_uekey_sgwteid_map *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_initial_ctxt_setup_req *initial_ctxt_setup_req;
    __lmem struct pif_header_scalars *scalars;
    __lmem struct pif_header_ethernet *ethernet;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_udp *udp;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_tmpvar *tmpvar;
    __lmem struct pif_header_data *data;
    __lmem struct pif_header_ue_service_req *ue_service_req;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__populate_service_req_uekey_sgwteid_map");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__populate_service_req_uekey_sgwteid_map");
#endif

    initial_ctxt_setup_req = (__lmem struct pif_header_initial_ctxt_setup_req *) (_pif_parrep + PIF_PARREP_initial_ctxt_setup_req_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    udp = (__lmem struct pif_header_udp *) (_pif_parrep + PIF_PARREP_udp_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    tmpvar = (__lmem struct pif_header_tmpvar *) (_pif_parrep + PIF_PARREP_tmpvar_OFF_LW);
    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);
    ue_service_req = (__lmem struct pif_header_ue_service_req *) (_pif_parrep + PIF_PARREP_ue_service_req_OFF_LW);
    PIF_PARREP_SET_data_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_udp_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_initial_ctxt_setup_req_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ue_service_req_DIRTY(_pif_ctldata);

    PIF_FLCALC_UPD_INCR_CLEAR(PIF_FLCALC_CALC_0);
    {
        /* add_header(initial_ctxt_setup_req) */

        /* primitive body */
        {
            PIF_PARREP_SET_initial_ctxt_setup_req_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(initial_ctxt_setup_req.epc_traffic_code,0x12) */

        /* primitive body */
        initial_ctxt_setup_req->epc_traffic_code = 0x12;

    }
    {
        /* modify_field(initial_ctxt_setup_req.sep1,ue_service_req.sep1) */

        /* primitive body */
        initial_ctxt_setup_req->sep1 = ((ue_service_req->sep1 >> 8) & 0xffffff);
        initial_ctxt_setup_req->__sep1_1 = ((ue_service_req->sep1 & 0xff) << 16) | ue_service_req->__sep1_1;

    }
    {
        /* modify_field(initial_ctxt_setup_req.sgw_teid,sgwteid) */

        /* primitive body */
        initial_ctxt_setup_req->sgw_teid = ((_pif_act_data->sgwteid >> 24) & 0xff);
        initial_ctxt_setup_req->__sgw_teid_1 = _pif_act_data->sgwteid;

    }
    {
        /* remove_header(data) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_data_VALID(_pif_ctldata);
        }
    }
    {
        /* remove_header(ue_service_req) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_ue_service_req_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(ipv4.ttl,0x40) */

        /* primitive body */
        ipv4->ttl = 0x40;

    }
    {
        /* modify_field(ethernet.dstAddr,ethernet.srcAddr) */

        /* primitive body */
        ethernet->dstAddr = (ethernet->srcAddr << 16) | ((ethernet->__srcAddr_1 >> 16) & 0xffff);
        ethernet->__dstAddr_1 = ethernet->__srcAddr_1;

    }
    {
        /* modify_field(ipv4.dstAddr,ipv4.srcAddr) */

        /* primitive body */
        ipv4->dstAddr = ipv4->srcAddr;

    }
    {
        /* modify_field(scalars.pred,_expression_populate_service_req_uekey_sgwteid_map_0) */
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_0;

        /* primitive body */
        //expression _expression_populate_service_req_uekey_sgwteid_map_0: (((ethernet.srcAddr) == (0x00163ec6a2aa)))
        {
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_1;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_2;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_3;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_4;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_5;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_6;
        //subexpression 2: 0x00163ec6a2aa
        // constant : 0x163ec6a2aa

        //subexpression 0: (ethernet.srcAddr)==(0x00163ec6a2aa)
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_1 = ethernet->__srcAddr_1;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_2 = ethernet->srcAddr;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_3 = 0x3ec6a2aa;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_4 = 0x16;
        /* implicit cast 37 -> 48 */
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_5 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_3;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_6 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_4 & 0x1f;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_0 = (pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_1 == pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_5) && (pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_2 == pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_6);
        }

        scalars->pred = pif_expression__expression_populate_service_req_uekey_sgwteid_map_0_register_0;

    }
    {
        /* modify_field(ethernet.srcAddr,_expression_populate_service_req_uekey_sgwteid_map_1) */
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_6;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_5;

        /* primitive body */
        //expression _expression_populate_service_req_uekey_sgwteid_map_1: ((((ethernet.srcAddr) == (0x00163ec6a2aa))) ?: (0x002222222222) (ethernet.srcAddr))
        {
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_0;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_1;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_2;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_3;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_4;
        //subexpression 5: 0x00163ec6a2aa
        // constant : 0x163ec6a2aa

        //subexpression 1: (ethernet.srcAddr)==(0x00163ec6a2aa)
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_1 = ethernet->__srcAddr_1;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_2 = ethernet->srcAddr;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_3 = 0x3ec6a2aa;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_4 = 0x16;
        /* implicit cast 37 -> 48 */
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_5 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_3;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_6 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_4 & 0x1f;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_0 = (pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_1 == pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_5) && (pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_2 == pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_6);
        //subexpression 2: 0x002222222222
        // constant : 0x2222222222

        //subexpression 0: (((ethernet.srcAddr)==(0x00163ec6a2aa)))?:(0x002222222222)(ethernet.srcAddr)
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_2 = 0x22222222;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_1 = 0x22;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_4 = ethernet->__srcAddr_1;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_3 = ethernet->srcAddr;
        if (pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_0 != 0) {
            pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_6 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_2;
            pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_5 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_1;
        } else {
            pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_6 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_4;
            pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_5 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_3;
        }
        }

        ethernet->srcAddr = pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_5;
        ethernet->__srcAddr_1 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_1_register_6;

    }
    {
        /* modify_field(ipv4.srcAddr,_expression_populate_service_req_uekey_sgwteid_map_2) */
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_0;

        /* primitive body */
        //expression _expression_populate_service_req_uekey_sgwteid_map_2: (((scalars.pred)) ?: (0xc0a80203) (ipv4.srcAddr))
        {
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_1;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_2;
        unsigned int pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_3;
        //subexpression 2: 0xc0a80203
        // constant : 0xc0a80203

        //subexpression 0: ((scalars.pred))?:(0xc0a80203)(ipv4.srcAddr)
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_1 = scalars->pred;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_2 = 0xc0a80203;
        pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_3 = ipv4->srcAddr;
        if (pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_1 != 0) {
            pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_0 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_2;
        } else {
            pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_0 = pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_3;
        }
        }

        ipv4->srcAddr = pif_expression__expression_populate_service_req_uekey_sgwteid_map_2_register_0;

    }
    {
        /* modify_field(tmpvar.tmpUdpPort,udp.srcPort) */

        /* primitive body */
        tmpvar->tmpUdpPort = udp->srcPort;

    }
    {
        /* modify_field(udp.srcPort,udp.dstPort) */

        /* primitive body */
        udp->srcPort = udp->dstPort;

    }
    {
        /* modify_field(udp.dstPort,tmpvar.tmpUdpPort) */

        /* primitive body */
        udp->dstPort = tmpvar->tmpUdpPort;

    }
    {
        /* modify_field(udp.length_,0x0013) */

        /* primitive body */
        udp->length_ = 0x13;

    }
    {
        /* modify_field(ipv4.totalLen,0x0027) */

        /* primitive body */
        ipv4->totalLen = 0x27;

    }
    {
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__populate_uekey_uestate_map(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__populate_uekey_uestate_map *_pif_act_data = (__xread struct pif_action_actiondata_ingress__populate_uekey_uestate_map *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_tmpreg *tmpreg;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__populate_uekey_uestate_map");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__populate_uekey_uestate_map");
#endif

    tmpreg = (__lmem struct pif_header_tmpreg *) (_pif_parrep + PIF_PARREP_tmpreg_OFF_LW);

    {
        /* modify_field(tmpreg.tmp_index,reg_index) */

        /* primitive body */
        tmpreg->tmp_index = _pif_act_data->reg_index;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__populate_ip_op_tun_s2_uplink(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__populate_ip_op_tun_s2_uplink *_pif_act_data = (__xread struct pif_action_actiondata_ingress__populate_ip_op_tun_s2_uplink *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__populate_ip_op_tun_s2_uplink");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__populate_ip_op_tun_s2_uplink");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(standard_metadata.egress_spec,egress_port_s2) */

        /* primitive body */
        standard_metadata->egress_spec = _pif_act_data->egress_port_s2;

    }
    {
        /* modify_field(ipv4.ttl,_expression_populate_ip_op_tun_s2_uplink_0) */
        unsigned int pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_2;

        /* primitive body */
        //expression _expression_populate_ip_op_tun_s2_uplink_0: ((((ipv4.ttl) + (0xff))) & (0xff))
        {
        unsigned int pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_0;
        unsigned int pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_1;
        //subexpression 4: 0xff
        // constant : 0xff

        //subexpression 1: (ipv4.ttl)+(0xff)
        pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_1 = ipv4->ttl;
        pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_2 = 0xff;
        pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_0 = pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_1 + pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_2;
        pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_0 &= 0xff;
        //subexpression 2: 0xff
        // constant : 0xff

        //subexpression 0: (((ipv4.ttl)+(0xff)))&(0xff)
        pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_1 = 0xff;
        pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_2 = pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_0 & pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_1;
        }

        ipv4->ttl = pif_expression__expression_populate_ip_op_tun_s2_uplink_0_register_2;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_21(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_21 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_21 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_21");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_21");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_20(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_20 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_20 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_20");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_20");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0300) */

        /* primitive body */
        standard_metadata->egress_spec = 0x300;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__populate_ctxt_setup_uekey_sgwteid_map(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__populate_ctxt_setup_uekey_sgwteid_map *_pif_act_data = (__xread struct pif_action_actiondata_ingress__populate_ctxt_setup_uekey_sgwteid_map *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_initial_ctxt_setup_resp *initial_ctxt_setup_resp;
    __lmem struct pif_header_packet_in *packet_in;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_offload_initial_ctxt_setup_resp *offload_initial_ctxt_setup_resp;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__populate_ctxt_setup_uekey_sgwteid_map");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__populate_ctxt_setup_uekey_sgwteid_map");
#endif

    initial_ctxt_setup_resp = (__lmem struct pif_header_initial_ctxt_setup_resp *) (_pif_parrep + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW);
    packet_in = (__lmem struct pif_header_packet_in *) (_pif_parrep + PIF_PARREP_packet_in_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    offload_initial_ctxt_setup_resp = (__lmem struct pif_header_offload_initial_ctxt_setup_resp *) (_pif_parrep + PIF_PARREP_offload_initial_ctxt_setup_resp_OFF_LW);
    PIF_PARREP_SET_offload_initial_ctxt_setup_resp_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_packet_in_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_initial_ctxt_setup_resp_DIRTY(_pif_ctldata);

    {
        /* add_header(offload_initial_ctxt_setup_resp) */

        /* primitive body */
        {
            PIF_PARREP_SET_offload_initial_ctxt_setup_resp_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(offload_initial_ctxt_setup_resp.ue_teid,initial_ctxt_setup_resp.ue_teid) */

        /* primitive body */
        offload_initial_ctxt_setup_resp->ue_teid = initial_ctxt_setup_resp->ue_teid;

    }
    {
        /* modify_field(offload_initial_ctxt_setup_resp.sep1,initial_ctxt_setup_resp.sep1) */

        /* primitive body */
        offload_initial_ctxt_setup_resp->sep1 = initial_ctxt_setup_resp->sep1;
        offload_initial_ctxt_setup_resp->__sep1_1 = initial_ctxt_setup_resp->__sep1_1;

    }
    {
        /* modify_field(offload_initial_ctxt_setup_resp.ue_key,initial_ctxt_setup_resp.ue_key) */

        /* primitive body */
        offload_initial_ctxt_setup_resp->ue_key = initial_ctxt_setup_resp->ue_key;
        offload_initial_ctxt_setup_resp->__ue_key_1 = initial_ctxt_setup_resp->__ue_key_1;

    }
    {
        /* modify_field(offload_initial_ctxt_setup_resp.sep2,initial_ctxt_setup_resp.sep2) */

        /* primitive body */
        offload_initial_ctxt_setup_resp->sep2 = initial_ctxt_setup_resp->sep2;
        offload_initial_ctxt_setup_resp->__sep2_1 = initial_ctxt_setup_resp->__sep2_1;

    }
    {
        /* modify_field(offload_initial_ctxt_setup_resp.ue_ip,initial_ctxt_setup_resp.ue_ip) */

        /* primitive body */
        offload_initial_ctxt_setup_resp->ue_ip = initial_ctxt_setup_resp->ue_ip;

    }
    {
        /* modify_field(offload_initial_ctxt_setup_resp.sep3,initial_ctxt_setup_resp.sep2) */

        /* primitive body */
        offload_initial_ctxt_setup_resp->sep3 = (initial_ctxt_setup_resp->sep2 << 16) | ((initial_ctxt_setup_resp->__sep2_1 >> 16) & 0xffff);
        offload_initial_ctxt_setup_resp->__sep3_1 = initial_ctxt_setup_resp->__sep2_1;

    }
    {
        /* modify_field(offload_initial_ctxt_setup_resp.sgw_teid,sgwteid) */

        /* primitive body */
        offload_initial_ctxt_setup_resp->sgw_teid = ((_pif_act_data->sgwteid >> 16) & 0xffff);
        offload_initial_ctxt_setup_resp->__sgw_teid_1 = _pif_act_data->sgwteid;

    }
    {
        /* remove_header(initial_ctxt_setup_resp) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_initial_ctxt_setup_resp_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(standard_metadata.egress_spec,0x0300) */

        /* primitive body */
        standard_metadata->egress_spec = 0x300;

    }
    {
        /* add_header(packet_in) */

        /* primitive body */
        {
            PIF_PARREP_SET_packet_in_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(packet_in.ingress_port,standard_metadata.ingress_port) */

        /* primitive body */
        packet_in->ingress_port = standard_metadata->ingress_port;

    }
    return _pif_return;
}

static int pif_action_exec_egress__act_22(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_egress__act_22 *_pif_act_data = (__xread struct pif_action_actiondata_egress__act_22 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_ethernet *ethernet;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_egress__act_22");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_egress__act_22");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(ethernet.srcAddr,0x002222222222) */

        /* primitive body */
        ethernet->srcAddr = 0x22;
        ethernet->__srcAddr_1 = 0x22222222;

    }
    {
        /* modify_field(ipv4.srcAddr,0xc0a80203) */

        /* primitive body */
        ipv4->srcAddr = 0xc0a80203;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_egress__act_23(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_egress__act_23 *_pif_act_data = (__xread struct pif_action_actiondata_egress__act_23 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_data *data;
    __lmem struct pif_header_ue_context_rel_command *ue_context_rel_command;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_ethernet *ethernet;
    __lmem struct pif_header_ue_context_rel_req *ue_context_rel_req;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_egress__act_23");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_egress__act_23");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);
    ue_context_rel_command = (__lmem struct pif_header_ue_context_rel_command *) (_pif_parrep + PIF_PARREP_ue_context_rel_command_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    ue_context_rel_req = (__lmem struct pif_header_ue_context_rel_req *) (_pif_parrep + PIF_PARREP_ue_context_rel_req_OFF_LW);
    PIF_PARREP_SET_data_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ue_context_rel_req_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ue_context_rel_command_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 1);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        _pif_flc_update_val = ((((ipv4->dstAddr) & 0xffff)) << 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* add_header(ue_context_rel_command) */

        /* primitive body */
        {
            PIF_PARREP_SET_ue_context_rel_command_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(ue_context_rel_command.epc_traffic_code,0x0f) */

        /* primitive body */
        ue_context_rel_command->epc_traffic_code = 0xf;

    }
    {
        /* modify_field(ue_context_rel_command.sep1,ue_context_rel_req.sep1) */

        /* primitive body */
        ue_context_rel_command->sep1 = ((ue_context_rel_req->sep1 >> 8) & 0xffffff);
        ue_context_rel_command->__sep1_1 = ((ue_context_rel_req->sep1 & 0xff) << 16) | ue_context_rel_req->__sep1_1;

    }
    {
        /* remove_header(data) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_data_VALID(_pif_ctldata);
        }
    }
    {
        /* remove_header(ue_context_rel_req) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_ue_context_rel_req_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(ipv4.ttl,0x40) */

        /* primitive body */
        ipv4->ttl = 0x40;

    }
    {
        /* modify_field(ethernet.dstAddr,ethernet.srcAddr) */

        /* primitive body */
        ethernet->dstAddr = (ethernet->srcAddr << 16) | ((ethernet->__srcAddr_1 >> 16) & 0xffff);
        ethernet->__dstAddr_1 = ethernet->__srcAddr_1;

    }
    {
        /* modify_field(ipv4.dstAddr,ipv4.srcAddr) */

        /* primitive body */
        ipv4->dstAddr = ipv4->srcAddr;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 0);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        _pif_flc_update_val = ((((ipv4->dstAddr) & 0xffff)) << 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_ingress__drop_act(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__drop_act *_pif_act_data = (__xread struct pif_action_actiondata_ingress__drop_act *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__drop_act");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__drop_act");
#endif


    {
        /* drop() */

        /* primitive body */
        _pif_return = PIF_RETURN_DROP;
    }
    return _pif_return;
}

static int pif_action_exec_egress__act_26(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_egress__act_26 *_pif_act_data = (__xread struct pif_action_actiondata_egress__act_26 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_data *data;
    __lmem struct pif_header_initial_ctxt_setup_resp *initial_ctxt_setup_resp;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_ethernet *ethernet;
    __lmem struct pif_header_attach_accept *attach_accept;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_egress__act_26");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_egress__act_26");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);
    initial_ctxt_setup_resp = (__lmem struct pif_header_initial_ctxt_setup_resp *) (_pif_parrep + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    attach_accept = (__lmem struct pif_header_attach_accept *) (_pif_parrep + PIF_PARREP_attach_accept_OFF_LW);
    PIF_PARREP_SET_data_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_attach_accept_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_initial_ctxt_setup_resp_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 1);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        _pif_flc_update_val = ((((ipv4->dstAddr) & 0xffff)) << 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* add_header(attach_accept) */

        /* primitive body */
        {
            PIF_PARREP_SET_attach_accept_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(attach_accept.epc_traffic_code,0x08) */

        /* primitive body */
        attach_accept->epc_traffic_code = 0x8;

    }
    {
        /* modify_field(attach_accept.sep1,initial_ctxt_setup_resp.sep1) */

        /* primitive body */
        attach_accept->sep1 = ((initial_ctxt_setup_resp->sep1 >> 8) & 0xffffff);
        attach_accept->__sep1_1 = ((initial_ctxt_setup_resp->sep1 & 0xff) << 16) | initial_ctxt_setup_resp->__sep1_1;

    }
    {
        /* modify_field(attach_accept.ue_key,initial_ctxt_setup_resp.ue_key) */

        /* primitive body */
        attach_accept->ue_key = ((initial_ctxt_setup_resp->ue_key >> 8) & 0xff);
        attach_accept->__ue_key_1 = ((initial_ctxt_setup_resp->ue_key & 0xff) << 16) | initial_ctxt_setup_resp->__ue_key_1;

    }
    {
        /* remove_header(data) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_data_VALID(_pif_ctldata);
        }
    }
    {
        /* remove_header(initial_ctxt_setup_resp) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_initial_ctxt_setup_resp_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(ipv4.ttl,0x40) */

        /* primitive body */
        ipv4->ttl = 0x40;

    }
    {
        /* modify_field(ethernet.dstAddr,ethernet.srcAddr) */

        /* primitive body */
        ethernet->dstAddr = (ethernet->srcAddr << 16) | ((ethernet->__srcAddr_1 >> 16) & 0xffff);
        ethernet->__dstAddr_1 = ethernet->__srcAddr_1;

    }
    {
        /* modify_field(ipv4.dstAddr,ipv4.srcAddr) */

        /* primitive body */
        ipv4->dstAddr = ipv4->srcAddr;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 0);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        _pif_flc_update_val = ((((ipv4->dstAddr) & 0xffff)) << 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_egress__act_27(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_egress__act_27 *_pif_act_data = (__xread struct pif_action_actiondata_egress__act_27 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_udp *udp;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_tmpvar *tmpvar;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_egress__act_27");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_egress__act_27");
#endif

    udp = (__lmem struct pif_header_udp *) (_pif_parrep + PIF_PARREP_udp_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    tmpvar = (__lmem struct pif_header_tmpvar *) (_pif_parrep + PIF_PARREP_tmpvar_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_udp_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((__lmem uint32_t *)ipv4)[0];
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(tmpvar.tmpUdpPort,udp.srcPort) */

        /* primitive body */
        tmpvar->tmpUdpPort = udp->srcPort;

    }
    {
        /* modify_field(udp.srcPort,udp.dstPort) */

        /* primitive body */
        udp->srcPort = udp->dstPort;

    }
    {
        /* modify_field(udp.dstPort,tmpvar.tmpUdpPort) */

        /* primitive body */
        udp->dstPort = tmpvar->tmpUdpPort;

    }
    {
        /* modify_field(udp.length_,0x0013) */

        /* primitive body */
        udp->length_ = 0x13;

    }
    {
        /* modify_field(ipv4.totalLen,0x0027) */

        /* primitive body */
        ipv4->totalLen = 0x27;

    }
    {
        /* modify_field(standard_metadata.egress_port,0x0001) */

        /* primitive body */
        standard_metadata->egress_port = 0x1;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((__lmem uint32_t *)ipv4)[0];
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_egress__act_24(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_egress__act_24 *_pif_act_data = (__xread struct pif_action_actiondata_egress__act_24 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_udp *udp;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_tmpvar *tmpvar;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_egress__act_24");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_egress__act_24");
#endif

    udp = (__lmem struct pif_header_udp *) (_pif_parrep + PIF_PARREP_udp_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    tmpvar = (__lmem struct pif_header_tmpvar *) (_pif_parrep + PIF_PARREP_tmpvar_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_udp_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((__lmem uint32_t *)ipv4)[0];
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(tmpvar.tmpUdpPort,udp.srcPort) */

        /* primitive body */
        tmpvar->tmpUdpPort = udp->srcPort;

    }
    {
        /* modify_field(udp.srcPort,udp.dstPort) */

        /* primitive body */
        udp->srcPort = udp->dstPort;

    }
    {
        /* modify_field(udp.dstPort,tmpvar.tmpUdpPort) */

        /* primitive body */
        udp->dstPort = tmpvar->tmpUdpPort;

    }
    {
        /* modify_field(udp.length_,0x000f) */

        /* primitive body */
        udp->length_ = 0xf;

    }
    {
        /* modify_field(ipv4.totalLen,0x0023) */

        /* primitive body */
        ipv4->totalLen = 0x23;

    }
    {
        /* modify_field(standard_metadata.egress_port,0x0001) */

        /* primitive body */
        standard_metadata->egress_port = 0x1;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((__lmem uint32_t *)ipv4)[0];
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_egress__act_25(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_egress__act_25 *_pif_act_data = (__xread struct pif_action_actiondata_egress__act_25 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_ethernet *ethernet;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_egress__act_25");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_egress__act_25");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(ethernet.srcAddr,0x002222222222) */

        /* primitive body */
        ethernet->srcAddr = 0x22;
        ethernet->__srcAddr_1 = 0x22222222;

    }
    {
        /* modify_field(ipv4.srcAddr,0xc0a80203) */

        /* primitive body */
        ipv4->srcAddr = 0xc0a80203;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_ingress__populate_uekey_guti_map(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__populate_uekey_guti_map *_pif_act_data = (__xread struct pif_action_actiondata_ingress__populate_uekey_guti_map *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__uekey_guti *ingress__uekey_guti;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__populate_uekey_guti_map");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__populate_uekey_guti_map");
#endif

    ingress__uekey_guti = (__lmem struct pif_header_ingress__uekey_guti *) (_pif_parrep + PIF_PARREP_ingress__uekey_guti_OFF_LW);

    {
        /* modify_field(ingress::uekey_guti.guti,guti) */

        /* primitive body */
        ingress__uekey_guti->guti = _pif_act_data->guti;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_18(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_18 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_18 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_18");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_18");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0300) */

        /* primitive body */
        standard_metadata->egress_spec = 0x300;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_19(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_19 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_19 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_scalars *scalars;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_19");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_19");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0000) */

        /* primitive body */
        standard_metadata->egress_spec = 0x0;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_12(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_12 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_12 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_ethernet *ethernet;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_12");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_12");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(ethernet.srcAddr,0x002222222222) */

        /* primitive body */
        ethernet->srcAddr = 0x22;
        ethernet->__srcAddr_1 = 0x22222222;

    }
    {
        /* modify_field(ipv4.srcAddr,0xc0a80203) */

        /* primitive body */
        ipv4->srcAddr = 0xc0a80203;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_13(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_13 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_13 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ethernet *ethernet;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_ue_context_rel_req *ue_context_rel_req;
    __lmem struct pif_header_data *data;
    __lmem struct pif_header_ue_context_rel_command *ue_context_rel_command;
    __lmem struct pif_header_tmpreg *tmpreg;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_13");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_13");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    ue_context_rel_req = (__lmem struct pif_header_ue_context_rel_req *) (_pif_parrep + PIF_PARREP_ue_context_rel_req_OFF_LW);
    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);
    ue_context_rel_command = (__lmem struct pif_header_ue_context_rel_command *) (_pif_parrep + PIF_PARREP_ue_context_rel_command_OFF_LW);
    tmpreg = (__lmem struct pif_header_tmpreg *) (_pif_parrep + PIF_PARREP_tmpreg_OFF_LW);
    PIF_PARREP_SET_data_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ue_context_rel_req_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ue_context_rel_command_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 1);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        _pif_flc_update_val = ((((ipv4->dstAddr) & 0xffff)) << 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* register_write(reg_uestate.value,tmpreg.tmp_index,0x00) */

        /* primitive body */
        {
            unsigned int _pif_index;
            _pif_index = tmpreg->tmp_index;

            if (_pif_index < 65000) {
                __xwrite uint32_t _pif_xreg[1];
                __mem __addr40 struct pif_header_reg_uestate *_pif_hdrptr = (__mem __addr40 struct pif_header_reg_uestate *) &pif_register_reg_uestate[_pif_index];

                _pif_xreg[0] = 0x0;

                mem_write_atomic(_pif_xreg, ((__mem __addr40 uint8_t *)_pif_hdrptr) + 3, 4);
            }
        }
    }
    {
        /* add_header(ue_context_rel_command) */

        /* primitive body */
        {
            PIF_PARREP_SET_ue_context_rel_command_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(ue_context_rel_command.epc_traffic_code,0x0f) */

        /* primitive body */
        ue_context_rel_command->epc_traffic_code = 0xf;

    }
    {
        /* modify_field(ue_context_rel_command.sep1,ue_context_rel_req.sep1) */

        /* primitive body */
        ue_context_rel_command->sep1 = ((ue_context_rel_req->sep1 >> 8) & 0xffffff);
        ue_context_rel_command->__sep1_1 = ((ue_context_rel_req->sep1 & 0xff) << 16) | ue_context_rel_req->__sep1_1;

    }
    {
        /* remove_header(data) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_data_VALID(_pif_ctldata);
        }
    }
    {
        /* remove_header(ue_context_rel_req) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_ue_context_rel_req_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(ipv4.ttl,0x40) */

        /* primitive body */
        ipv4->ttl = 0x40;

    }
    {
        /* modify_field(ethernet.dstAddr,ethernet.srcAddr) */

        /* primitive body */
        ethernet->dstAddr = (ethernet->srcAddr << 16) | ((ethernet->__srcAddr_1 >> 16) & 0xffff);
        ethernet->__dstAddr_1 = ethernet->__srcAddr_1;

    }
    {
        /* modify_field(ipv4.dstAddr,ipv4.srcAddr) */

        /* primitive body */
        ipv4->dstAddr = ipv4->srcAddr;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 0);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        _pif_flc_update_val = ((((ipv4->dstAddr) & 0xffff)) << 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_10(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_10 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_10 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_tmpreg *tmpreg;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_10");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_10");
#endif

    tmpreg = (__lmem struct pif_header_tmpreg *) (_pif_parrep + PIF_PARREP_tmpreg_OFF_LW);

    {
        /* register_write(s2_downlink_egress_port.value,tmpreg.tmp_index,0xffff) */

        /* primitive body */
        {
            unsigned int _pif_index;
            _pif_index = tmpreg->tmp_index;

            if (_pif_index < 65000) {
                __xwrite uint32_t _pif_xreg[1];
                __mem __addr40 struct pif_header_s2_downlink_egress_port *_pif_hdrptr = (__mem __addr40 struct pif_header_s2_downlink_egress_port *) &pif_register_s2_downlink_egress_port[_pif_index];

                _pif_xreg[0] = 0xffff;

                mem_write_atomic(_pif_xreg, ((__mem __addr40 uint8_t *)_pif_hdrptr) + 2, 4);
            }
        }
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_11(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_11 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_11 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_tmpreg *tmpreg;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_11");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_11");
#endif

    tmpreg = (__lmem struct pif_header_tmpreg *) (_pif_parrep + PIF_PARREP_tmpreg_OFF_LW);

    {
        /* register_write(s2_downlink_egress_port.value,tmpreg.tmp_index,0x0000) */

        /* primitive body */
        {
            unsigned int _pif_index;
            _pif_index = tmpreg->tmp_index;

            if (_pif_index < 65000) {
                __xwrite uint32_t _pif_xreg[1];
                __mem __addr40 struct pif_header_s2_downlink_egress_port *_pif_hdrptr = (__mem __addr40 struct pif_header_s2_downlink_egress_port *) &pif_register_s2_downlink_egress_port[_pif_index];

                _pif_xreg[0] = 0x0;

                mem_write_atomic(_pif_xreg, ((__mem __addr40 uint8_t *)_pif_hdrptr) + 2, 4);
            }
        }
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_16(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_16 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_16 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_initial_ctxt_setup_resp *initial_ctxt_setup_resp;
    __lmem struct pif_header_ethernet *ethernet;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_data *data;
    __lmem struct pif_header_tmpreg *tmpreg;
    __lmem struct pif_header_attach_accept *attach_accept;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_16");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_16");
#endif

    initial_ctxt_setup_resp = (__lmem struct pif_header_initial_ctxt_setup_resp *) (_pif_parrep + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);
    tmpreg = (__lmem struct pif_header_tmpreg *) (_pif_parrep + PIF_PARREP_tmpreg_OFF_LW);
    attach_accept = (__lmem struct pif_header_attach_accept *) (_pif_parrep + PIF_PARREP_attach_accept_OFF_LW);
    PIF_PARREP_SET_data_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_attach_accept_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_initial_ctxt_setup_resp_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 1);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        _pif_flc_update_val = ((((ipv4->dstAddr) & 0xffff)) << 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* register_write(reg_uestate.value,tmpreg.tmp_index,0x01) */

        /* primitive body */
        {
            unsigned int _pif_index;
            _pif_index = tmpreg->tmp_index;

            if (_pif_index < 65000) {
                __xwrite uint32_t _pif_xreg[1];
                __mem __addr40 struct pif_header_reg_uestate *_pif_hdrptr = (__mem __addr40 struct pif_header_reg_uestate *) &pif_register_reg_uestate[_pif_index];

                _pif_xreg[0] = 0x1;

                mem_write_atomic(_pif_xreg, ((__mem __addr40 uint8_t *)_pif_hdrptr) + 3, 4);
            }
        }
    }
    {
        /* add_header(attach_accept) */

        /* primitive body */
        {
            PIF_PARREP_SET_attach_accept_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(attach_accept.epc_traffic_code,0x08) */

        /* primitive body */
        attach_accept->epc_traffic_code = 0x8;

    }
    {
        /* modify_field(attach_accept.sep1,initial_ctxt_setup_resp.sep1) */

        /* primitive body */
        attach_accept->sep1 = ((initial_ctxt_setup_resp->sep1 >> 8) & 0xffffff);
        attach_accept->__sep1_1 = ((initial_ctxt_setup_resp->sep1 & 0xff) << 16) | initial_ctxt_setup_resp->__sep1_1;

    }
    {
        /* modify_field(attach_accept.ue_key,initial_ctxt_setup_resp.ue_key) */

        /* primitive body */
        attach_accept->ue_key = ((initial_ctxt_setup_resp->ue_key >> 8) & 0xff);
        attach_accept->__ue_key_1 = ((initial_ctxt_setup_resp->ue_key & 0xff) << 16) | initial_ctxt_setup_resp->__ue_key_1;

    }
    {
        /* remove_header(data) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_data_VALID(_pif_ctldata);
        }
    }
    {
        /* remove_header(initial_ctxt_setup_resp) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_initial_ctxt_setup_resp_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(ipv4.ttl,0x40) */

        /* primitive body */
        ipv4->ttl = 0x40;

    }
    {
        /* modify_field(ethernet.dstAddr,ethernet.srcAddr) */

        /* primitive body */
        ethernet->dstAddr = (ethernet->srcAddr << 16) | ((ethernet->__srcAddr_1 >> 16) & 0xffff);
        ethernet->__dstAddr_1 = ethernet->__srcAddr_1;

    }
    {
        /* modify_field(ipv4.dstAddr,ipv4.srcAddr) */

        /* primitive body */
        ipv4->dstAddr = ipv4->srcAddr;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xff000000, 0);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        _pif_flc_update_val = ((((ipv4->dstAddr) & 0xffff)) << 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_17(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_17 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_17 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_udp *udp;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_tmpvar *tmpvar;
    __lmem struct pif_header_scalars *scalars;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_17");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_17");
#endif

    udp = (__lmem struct pif_header_udp *) (_pif_parrep + PIF_PARREP_udp_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    tmpvar = (__lmem struct pif_header_tmpvar *) (_pif_parrep + PIF_PARREP_tmpvar_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_udp_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((__lmem uint32_t *)ipv4)[0];
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(tmpvar.tmpUdpPort,udp.srcPort) */

        /* primitive body */
        tmpvar->tmpUdpPort = udp->srcPort;

    }
    {
        /* modify_field(udp.srcPort,udp.dstPort) */

        /* primitive body */
        udp->srcPort = udp->dstPort;

    }
    {
        /* modify_field(udp.dstPort,tmpvar.tmpUdpPort) */

        /* primitive body */
        udp->dstPort = tmpvar->tmpUdpPort;

    }
    {
        /* modify_field(udp.length_,0x0013) */

        /* primitive body */
        udp->length_ = 0x13;

    }
    {
        /* modify_field(ipv4.totalLen,0x0027) */

        /* primitive body */
        ipv4->totalLen = 0x27;

    }
    {
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((__lmem uint32_t *)ipv4)[0];
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_14(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_14 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_14 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_udp *udp;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_tmpvar *tmpvar;
    __lmem struct pif_header_scalars *scalars;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_14");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_14");
#endif

    udp = (__lmem struct pif_header_udp *) (_pif_parrep + PIF_PARREP_udp_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    tmpvar = (__lmem struct pif_header_tmpvar *) (_pif_parrep + PIF_PARREP_tmpvar_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_udp_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((__lmem uint32_t *)ipv4)[0];
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(tmpvar.tmpUdpPort,udp.srcPort) */

        /* primitive body */
        tmpvar->tmpUdpPort = udp->srcPort;

    }
    {
        /* modify_field(udp.srcPort,udp.dstPort) */

        /* primitive body */
        udp->srcPort = udp->dstPort;

    }
    {
        /* modify_field(udp.dstPort,tmpvar.tmpUdpPort) */

        /* primitive body */
        udp->dstPort = tmpvar->tmpUdpPort;

    }
    {
        /* modify_field(udp.length_,0x000f) */

        /* primitive body */
        udp->length_ = 0xf;

    }
    {
        /* modify_field(ipv4.totalLen,0x0023) */

        /* primitive body */
        ipv4->totalLen = 0x23;

    }
    {
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    {
        /* modify_field(scalars.hasReturned_0,1) */

        /* primitive body */
        scalars->hasReturned_0 = 0x1;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((__lmem uint32_t *)ipv4)[0];
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_15(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_15 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_15 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_ethernet *ethernet;
    unsigned int _pif_flc_val_calc_0;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_ingress__act_15");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_15");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);

    _pif_flc_val_calc_0 = PIF_HEADER_GET_ipv4___hdrChecksum(ipv4);

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 1);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 1);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    {
        /* modify_field(ethernet.srcAddr,0x002222222222) */

        /* primitive body */
        ethernet->srcAddr = 0x22;
        ethernet->__srcAddr_1 = 0x22222222;

    }
    {
        /* modify_field(ipv4.srcAddr,0xc0a80203) */

        /* primitive body */
        ipv4->srcAddr = 0xc0a80203;

    }

    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) != 0 && PIF_PARREP_ipv4_VALID(_pif_ctldata)) {
        unsigned int _pif_flc_update_val;

        _pif_flc_update_val = ((ipv4->ttl) << 24);
        _pif_flc_update_val |= ((ipv4->protocol) << 16);
        _pif_flc_update_val |= ((ipv4->srcAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff, 0);

        _pif_flc_update_val = ((((ipv4->srcAddr) & 0xffff)) << 16);
        _pif_flc_update_val |= ((ipv4->dstAddr) >> 16);
        _pif_flc_val_calc_0 = pif_flcalc_csum16_update_lw(_pif_flc_val_calc_0, _pif_flc_update_val, 0xffff0000, 0);

        PIF_HEADER_SET_ipv4___hdrChecksum(ipv4, _pif_flc_val_calc_0);
    }
    return _pif_return;
}

static int pif_action_exec_egress__populate_ctxt_release_uekey_sgwteid_map(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_egress__populate_ctxt_release_uekey_sgwteid_map *_pif_act_data = (__xread struct pif_action_actiondata_egress__populate_ctxt_release_uekey_sgwteid_map *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_initial_ctxt_setup_req *initial_ctxt_setup_req;
    __lmem struct pif_header_scalars *scalars;
    __lmem struct pif_header_ethernet *ethernet;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_udp *udp;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_tmpvar *tmpvar;
    __lmem struct pif_header_data *data;
    __lmem struct pif_header_ue_service_req *ue_service_req;
#ifdef PIF_DEBUG
    if (_pif_debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _pif_act_data->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _pif_act_data->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_egress__populate_ctxt_release_uekey_sgwteid_map");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_egress__populate_ctxt_release_uekey_sgwteid_map");
#endif

    initial_ctxt_setup_req = (__lmem struct pif_header_initial_ctxt_setup_req *) (_pif_parrep + PIF_PARREP_initial_ctxt_setup_req_OFF_LW);
    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);
    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    udp = (__lmem struct pif_header_udp *) (_pif_parrep + PIF_PARREP_udp_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
    tmpvar = (__lmem struct pif_header_tmpvar *) (_pif_parrep + PIF_PARREP_tmpvar_OFF_LW);
    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);
    ue_service_req = (__lmem struct pif_header_ue_service_req *) (_pif_parrep + PIF_PARREP_ue_service_req_OFF_LW);
    PIF_PARREP_SET_data_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ipv4_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_udp_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ethernet_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_initial_ctxt_setup_req_DIRTY(_pif_ctldata);
    PIF_PARREP_SET_ue_service_req_DIRTY(_pif_ctldata);

    PIF_FLCALC_UPD_INCR_CLEAR(PIF_FLCALC_CALC_0);
    {
        /* add_header(initial_ctxt_setup_req) */

        /* primitive body */
        {
            PIF_PARREP_SET_initial_ctxt_setup_req_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(initial_ctxt_setup_req.epc_traffic_code,0x12) */

        /* primitive body */
        initial_ctxt_setup_req->epc_traffic_code = 0x12;

    }
    {
        /* modify_field(initial_ctxt_setup_req.sep1,ue_service_req.sep1) */

        /* primitive body */
        initial_ctxt_setup_req->sep1 = ((ue_service_req->sep1 >> 8) & 0xffffff);
        initial_ctxt_setup_req->__sep1_1 = ((ue_service_req->sep1 & 0xff) << 16) | ue_service_req->__sep1_1;

    }
    {
        /* modify_field(initial_ctxt_setup_req.sgw_teid,sgwteid) */

        /* primitive body */
        initial_ctxt_setup_req->sgw_teid = ((_pif_act_data->sgwteid >> 24) & 0xff);
        initial_ctxt_setup_req->__sgw_teid_1 = _pif_act_data->sgwteid;

    }
    {
        /* remove_header(data) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_data_VALID(_pif_ctldata);
        }
    }
    {
        /* remove_header(ue_service_req) */

        /* primitive body */
        {
            PIF_PARREP_CLEAR_ue_service_req_VALID(_pif_ctldata);
        }
    }
    {
        /* modify_field(ipv4.ttl,0x40) */

        /* primitive body */
        ipv4->ttl = 0x40;

    }
    {
        /* modify_field(ethernet.dstAddr,ethernet.srcAddr) */

        /* primitive body */
        ethernet->dstAddr = (ethernet->srcAddr << 16) | ((ethernet->__srcAddr_1 >> 16) & 0xffff);
        ethernet->__dstAddr_1 = ethernet->__srcAddr_1;

    }
    {
        /* modify_field(ipv4.dstAddr,ipv4.srcAddr) */

        /* primitive body */
        ipv4->dstAddr = ipv4->srcAddr;

    }
    {
        /* modify_field(scalars.pred_0,_expression_populate_ctxt_release_uekey_sgwteid_map_0) */
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_0;

        /* primitive body */
        //expression _expression_populate_ctxt_release_uekey_sgwteid_map_0: (((ethernet.srcAddr) == (0x00163ec6a2aa)))
        {
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_1;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_2;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_3;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_4;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_5;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_6;
        //subexpression 2: 0x00163ec6a2aa
        // constant : 0x163ec6a2aa

        //subexpression 0: (ethernet.srcAddr)==(0x00163ec6a2aa)
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_1 = ethernet->__srcAddr_1;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_2 = ethernet->srcAddr;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_3 = 0x3ec6a2aa;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_4 = 0x16;
        /* implicit cast 37 -> 48 */
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_5 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_3;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_6 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_4 & 0x1f;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_0 = (pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_1 == pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_5) && (pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_2 == pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_6);
        }

        scalars->pred_0 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_0_register_0;

    }
    {
        /* modify_field(ethernet.srcAddr,_expression_populate_ctxt_release_uekey_sgwteid_map_1) */
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_6;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_5;

        /* primitive body */
        //expression _expression_populate_ctxt_release_uekey_sgwteid_map_1: ((((ethernet.srcAddr) == (0x00163ec6a2aa))) ?: (0x002222222222) (ethernet.srcAddr))
        {
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_0;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_1;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_2;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_3;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_4;
        //subexpression 5: 0x00163ec6a2aa
        // constant : 0x163ec6a2aa

        //subexpression 1: (ethernet.srcAddr)==(0x00163ec6a2aa)
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_1 = ethernet->__srcAddr_1;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_2 = ethernet->srcAddr;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_3 = 0x3ec6a2aa;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_4 = 0x16;
        /* implicit cast 37 -> 48 */
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_5 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_3;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_6 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_4 & 0x1f;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_0 = (pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_1 == pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_5) && (pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_2 == pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_6);
        //subexpression 2: 0x002222222222
        // constant : 0x2222222222

        //subexpression 0: (((ethernet.srcAddr)==(0x00163ec6a2aa)))?:(0x002222222222)(ethernet.srcAddr)
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_2 = 0x22222222;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_1 = 0x22;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_4 = ethernet->__srcAddr_1;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_3 = ethernet->srcAddr;
        if (pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_0 != 0) {
            pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_6 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_2;
            pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_5 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_1;
        } else {
            pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_6 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_4;
            pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_5 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_3;
        }
        }

        ethernet->srcAddr = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_5;
        ethernet->__srcAddr_1 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_1_register_6;

    }
    {
        /* modify_field(ipv4.srcAddr,_expression_populate_ctxt_release_uekey_sgwteid_map_2) */
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_0;

        /* primitive body */
        //expression _expression_populate_ctxt_release_uekey_sgwteid_map_2: (((scalars.pred_0)) ?: (0xc0a80203) (ipv4.srcAddr))
        {
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_1;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_2;
        unsigned int pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_3;
        //subexpression 2: 0xc0a80203
        // constant : 0xc0a80203

        //subexpression 0: ((scalars.pred_0))?:(0xc0a80203)(ipv4.srcAddr)
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_1 = scalars->pred_0;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_2 = 0xc0a80203;
        pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_3 = ipv4->srcAddr;
        if (pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_1 != 0) {
            pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_0 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_2;
        } else {
            pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_0 = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_3;
        }
        }

        ipv4->srcAddr = pif_expression__expression_populate_ctxt_release_uekey_sgwteid_map_2_register_0;

    }
    {
        /* modify_field(tmpvar.tmpUdpPort,udp.srcPort) */

        /* primitive body */
        tmpvar->tmpUdpPort = udp->srcPort;

    }
    {
        /* modify_field(udp.srcPort,udp.dstPort) */

        /* primitive body */
        udp->srcPort = udp->dstPort;

    }
    {
        /* modify_field(udp.dstPort,tmpvar.tmpUdpPort) */

        /* primitive body */
        udp->dstPort = tmpvar->tmpUdpPort;

    }
    {
        /* modify_field(udp.length_,0x0013) */

        /* primitive body */
        udp->length_ = 0x13;

    }
    {
        /* modify_field(ipv4.totalLen,0x0027) */

        /* primitive body */
        ipv4->totalLen = 0x27;

    }
    {
        /* modify_field(standard_metadata.egress_port,0x0001) */

        /* primitive body */
        standard_metadata->egress_port = 0x1;

    }
    return _pif_return;
}

extern __forceinline int pif_action_exec_op(__lmem uint32_t *parrep, __xread uint32_t *_actdata)
{
    __xread union pif_action_opdata *opdata = (__xread union pif_action_opdata *) _actdata;
    int ret = -1;

    if (opdata->action_id > PIF_ACTION_ID_MAX) {
        /* FIXME: TODO: account for bad action id */
        return -1;
    }

    PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_ACTION, opdata->action_id);
    switch (opdata->action_id) {
    case PIF_ACTION_ID_ingress__act_8:
        ret = pif_action_exec_ingress__act_8(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__fwd_act:
        ret = pif_action_exec_ingress__fwd_act(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_9:
        ret = pif_action_exec_ingress__act_9(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_0:
        ret = pif_action_exec_ingress__act_0(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_1:
        ret = pif_action_exec_ingress__act_1(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_2:
        ret = pif_action_exec_ingress__act_2(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_3:
        ret = pif_action_exec_ingress__act_3(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_4:
        ret = pif_action_exec_ingress__act_4(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_5:
        ret = pif_action_exec_ingress__act_5(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_6:
        ret = pif_action_exec_ingress__act_6(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_7:
        ret = pif_action_exec_ingress__act_7(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__populate_ip_op_tun_s2_downlink:
        ret = pif_action_exec_ingress__populate_ip_op_tun_s2_downlink(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__populate_service_req_uekey_sgwteid_map:
        ret = pif_action_exec_ingress__populate_service_req_uekey_sgwteid_map(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act:
        ret = pif_action_exec_ingress__act(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__populate_uekey_uestate_map:
        ret = pif_action_exec_ingress__populate_uekey_uestate_map(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__populate_ip_op_tun_s2_uplink:
        ret = pif_action_exec_ingress__populate_ip_op_tun_s2_uplink(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_21:
        ret = pif_action_exec_ingress__act_21(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_20:
        ret = pif_action_exec_ingress__act_20(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__populate_ctxt_setup_uekey_sgwteid_map:
        ret = pif_action_exec_ingress__populate_ctxt_setup_uekey_sgwteid_map(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_egress__act_22:
        ret = pif_action_exec_egress__act_22(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_egress__act_23:
        ret = pif_action_exec_egress__act_23(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__drop_act:
        ret = pif_action_exec_ingress__drop_act(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_egress__act_26:
        ret = pif_action_exec_egress__act_26(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_egress__act_27:
        ret = pif_action_exec_egress__act_27(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_egress__act_24:
        ret = pif_action_exec_egress__act_24(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_egress__act_25:
        ret = pif_action_exec_egress__act_25(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__populate_uekey_guti_map:
        ret = pif_action_exec_ingress__populate_uekey_guti_map(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_18:
        ret = pif_action_exec_ingress__act_18(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_19:
        ret = pif_action_exec_ingress__act_19(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_12:
        ret = pif_action_exec_ingress__act_12(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_13:
        ret = pif_action_exec_ingress__act_13(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_10:
        ret = pif_action_exec_ingress__act_10(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_11:
        ret = pif_action_exec_ingress__act_11(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_16:
        ret = pif_action_exec_ingress__act_16(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_17:
        ret = pif_action_exec_ingress__act_17(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_14:
        ret = pif_action_exec_ingress__act_14(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_15:
        ret = pif_action_exec_ingress__act_15(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_egress__populate_ctxt_release_uekey_sgwteid_map:
        ret = pif_action_exec_egress__populate_ctxt_release_uekey_sgwteid_map(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    }
#ifdef PIF_DEBUG
        mem_incr64((__mem __addr40 uint64_t *)(pif_act_stats + opdata->action_id));
#endif

    return ret;
}
