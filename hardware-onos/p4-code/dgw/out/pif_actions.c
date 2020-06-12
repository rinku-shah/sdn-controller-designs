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
        __debug_label("pif_table_hit_ingress__act_8");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_8");
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
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    {
        /* modify_field(ipv4.ttl,_expression_act_8_0) */
        unsigned int pif_expression__expression_act_8_0_register_2;

        /* primitive body */
        //expression _expression_act_8_0: ((((ipv4.ttl) + (0xff))) & (0xff))
        {
        unsigned int pif_expression__expression_act_8_0_register_0;
        unsigned int pif_expression__expression_act_8_0_register_1;
        //subexpression 4: 0xff
        // constant : 0xff

        //subexpression 1: (ipv4.ttl)+(0xff)
        pif_expression__expression_act_8_0_register_1 = ipv4->ttl;
        pif_expression__expression_act_8_0_register_2 = 0xff;
        pif_expression__expression_act_8_0_register_0 = pif_expression__expression_act_8_0_register_1 + pif_expression__expression_act_8_0_register_2;
        pif_expression__expression_act_8_0_register_0 &= 0xff;
        //subexpression 2: 0xff
        // constant : 0xff

        //subexpression 0: (((ipv4.ttl)+(0xff)))&(0xff)
        pif_expression__expression_act_8_0_register_1 = 0xff;
        pif_expression__expression_act_8_0_register_2 = pif_expression__expression_act_8_0_register_0 & pif_expression__expression_act_8_0_register_1;
        }

        ipv4->ttl = pif_expression__expression_act_8_0_register_2;

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

static int pif_action_exec_ingress__act(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__scalars *ingress__scalars;
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

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    {
        /* modify_field(ingress::scalars.hasReturned_0,1) */

        /* primitive body */
        ingress__scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__populate_tun_egress_s3_uplink(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__populate_tun_egress_s3_uplink *_pif_act_data = (__xread struct pif_action_actiondata_ingress__populate_tun_egress_s3_uplink *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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
        __debug_label("pif_table_hit_ingress__populate_tun_egress_s3_uplink");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__populate_tun_egress_s3_uplink");
#endif

    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);

    {
        /* modify_field(ingress::tmpreg.port_index,egress_port_s3) */

        /* primitive body */
        ingress__tmpreg->port_index = _pif_act_data->egress_port_s3;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_9(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_9 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_9 *)_pif_actdatabuf;
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
        __debug_label("pif_table_hit_ingress__act_9");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_9");
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
        /* modify_field(standard_metadata.egress_spec,0x0300) */

        /* primitive body */
        standard_metadata->egress_spec = 0x300;

    }
    {
        /* modify_field(ipv4.ttl,_expression_act_9_0) */
        unsigned int pif_expression__expression_act_9_0_register_2;

        /* primitive body */
        //expression _expression_act_9_0: ((((ipv4.ttl) + (0xff))) & (0xff))
        {
        unsigned int pif_expression__expression_act_9_0_register_0;
        unsigned int pif_expression__expression_act_9_0_register_1;
        //subexpression 4: 0xff
        // constant : 0xff

        //subexpression 1: (ipv4.ttl)+(0xff)
        pif_expression__expression_act_9_0_register_1 = ipv4->ttl;
        pif_expression__expression_act_9_0_register_2 = 0xff;
        pif_expression__expression_act_9_0_register_0 = pif_expression__expression_act_9_0_register_1 + pif_expression__expression_act_9_0_register_2;
        pif_expression__expression_act_9_0_register_0 &= 0xff;
        //subexpression 2: 0xff
        // constant : 0xff

        //subexpression 0: (((ipv4.ttl)+(0xff)))&(0xff)
        pif_expression__expression_act_9_0_register_1 = 0xff;
        pif_expression__expression_act_9_0_register_2 = pif_expression__expression_act_9_0_register_0 & pif_expression__expression_act_9_0_register_1;
        }

        ipv4->ttl = pif_expression__expression_act_9_0_register_2;

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

static int pif_action_exec_ingress__act_0(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_0 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_0 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__scalars *ingress__scalars;
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
        __debug_label("pif_table_hit_ingress__act_0");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_0");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);

    {
        /* modify_field(standard_metadata.egress_spec,0x0001) */

        /* primitive body */
        standard_metadata->egress_spec = 0x1;

    }
    {
        /* modify_field(ingress::scalars.hasReturned_0,1) */

        /* primitive body */
        ingress__scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_1(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_1 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_1 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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
        __debug_label("pif_table_hit_ingress__act_1");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_1");
#endif

    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);
    ue_context_rel_req = (__lmem struct pif_header_ue_context_rel_req *) (_pif_parrep + PIF_PARREP_ue_context_rel_req_OFF_LW);

    {
        /* modify_field(ingress::tmpreg.ue_key,ue_context_rel_req.ue_num) */

        /* primitive body */
        ingress__tmpreg->ue_key = (ue_context_rel_req->ue_num << 16) | ue_context_rel_req->__ue_num_1;

    }
    {
        /* modify_field(ingress::tmpreg.srcAddr,ue_context_rel_req.ue_ip) */

        /* primitive body */
        ingress__tmpreg->srcAddr = ue_context_rel_req->ue_ip;

    }
    {
        /* modify_field(ingress::tmpreg.dstAddr,0xc0a80304) */

        /* primitive body */
        ingress__tmpreg->dstAddr = 0xc0a80304;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_10(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_10 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_10 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__scalars *ingress__scalars;
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

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    {
        /* modify_field(ingress::scalars.hasReturned_0,0) */

        /* primitive body */
        ingress__scalars->hasReturned_0 = 0x0;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_11(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_11 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_11 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__scalars *ingress__scalars;
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

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    {
        /* modify_field(ingress::scalars.hasReturned_0,1) */

        /* primitive body */
        ingress__scalars->hasReturned_0 = 0x1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_4(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_4 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_4 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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

    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);

    {
        /* register_write(s3_uplink_egress_port.value,ingress::tmpreg.port_index,0xffff) */

        /* primitive body */
        {
            unsigned int _pif_index;
            _pif_index = ingress__tmpreg->port_index;

            if (_pif_index < 65000) {
                __xwrite uint32_t _pif_xreg[1];
                __mem __addr40 struct pif_header_s3_uplink_egress_port *_pif_hdrptr = (__mem __addr40 struct pif_header_s3_uplink_egress_port *) &pif_register_s3_uplink_egress_port[_pif_index];

                _pif_xreg[0] = 0xffff;

                mem_write_atomic(_pif_xreg, ((__mem __addr40 uint8_t *)_pif_hdrptr) + 2, 4);
            }
        }
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_5(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_5 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_5 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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

    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);

    {
        /* register_write(s3_uplink_egress_port.value,ingress::tmpreg.port_index,0x0001) */

        /* primitive body */
        {
            unsigned int _pif_index;
            _pif_index = ingress__tmpreg->port_index;

            if (_pif_index < 65000) {
                __xwrite uint32_t _pif_xreg[1];
                __mem __addr40 struct pif_header_s3_uplink_egress_port *_pif_hdrptr = (__mem __addr40 struct pif_header_s3_uplink_egress_port *) &pif_register_s3_uplink_egress_port[_pif_index];

                _pif_xreg[0] = 0x1;

                mem_write_atomic(_pif_xreg, ((__mem __addr40 uint8_t *)_pif_hdrptr) + 2, 4);
            }
        }
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_6(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_6 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_6 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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

    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);

    {
        /* register_write(tun_s1_uplink_egress_port.value,ingress::tmpreg.port_index,0xffff) */

        /* primitive body */
        {
            unsigned int _pif_index;
            _pif_index = ingress__tmpreg->port_index;

            if (_pif_index < 65000) {
                __xwrite uint32_t _pif_xreg[1];
                __mem __addr40 struct pif_header_tun_s1_uplink_egress_port *_pif_hdrptr = (__mem __addr40 struct pif_header_tun_s1_uplink_egress_port *) &pif_register_tun_s1_uplink_egress_port[_pif_index];

                _pif_xreg[0] = 0xffff;

                mem_write_atomic(_pif_xreg, ((__mem __addr40 uint8_t *)_pif_hdrptr) + 2, 4);
            }
        }
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_7(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_7 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_7 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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

    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);

    {
        /* register_write(tun_s1_uplink_egress_port.value,ingress::tmpreg.port_index,0x0001) */

        /* primitive body */
        {
            unsigned int _pif_index;
            _pif_index = ingress__tmpreg->port_index;

            if (_pif_index < 65000) {
                __xwrite uint32_t _pif_xreg[1];
                __mem __addr40 struct pif_header_tun_s1_uplink_egress_port *_pif_hdrptr = (__mem __addr40 struct pif_header_tun_s1_uplink_egress_port *) &pif_register_tun_s1_uplink_egress_port[_pif_index];

                _pif_xreg[0] = 0x1;

                mem_write_atomic(_pif_xreg, ((__mem __addr40 uint8_t *)_pif_hdrptr) + 2, 4);
            }
        }
    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_3(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_3 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_3 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_initial_ctxt_setup_resp *initial_ctxt_setup_resp;
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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

    initial_ctxt_setup_resp = (__lmem struct pif_header_initial_ctxt_setup_resp *) (_pif_parrep + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW);
    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);

    {
        /* modify_field(ingress::tmpreg.srcAddr,initial_ctxt_setup_resp.ue_ip) */

        /* primitive body */
        ingress__tmpreg->srcAddr = initial_ctxt_setup_resp->ue_ip;

    }
    {
        /* modify_field(ingress::tmpreg.dstAddr,0xc0a80304) */

        /* primitive body */
        ingress__tmpreg->dstAddr = 0xc0a80304;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__populate_ip_op_tun_s1_uplink(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__populate_ip_op_tun_s1_uplink *_pif_act_data = (__xread struct pif_action_actiondata_ingress__populate_ip_op_tun_s1_uplink *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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
        __debug_label("pif_table_hit_ingress__populate_ip_op_tun_s1_uplink");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__populate_ip_op_tun_s1_uplink");
#endif

    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);

    {
        /* modify_field(ingress::tmpreg.port_index,egress_port_s1) */

        /* primitive body */
        ingress__tmpreg->port_index = _pif_act_data->egress_port_s1;

    }
    return _pif_return;
}

static int pif_action_exec_ingress__act_2(__lmem uint32_t *_pif_parrep, __xread uint32_t *_pif_actdatabuf, unsigned _pif_debug)
{
    int _pif_return = PIF_RETURN_FORWARD;
    __xread struct pif_action_actiondata_ingress__act_2 *_pif_act_data = (__xread struct pif_action_actiondata_ingress__act_2 *)_pif_actdatabuf;
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    __lmem struct pif_header_ingress__tmpreg *ingress__tmpreg;
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
        __debug_label("pif_table_hit_ingress__act_2");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_ingress__act_2");
#endif

    ingress__tmpreg = (__lmem struct pif_header_ingress__tmpreg *) (_pif_parrep + PIF_PARREP_ingress__tmpreg_OFF_LW);
    ue_service_req = (__lmem struct pif_header_ue_service_req *) (_pif_parrep + PIF_PARREP_ue_service_req_OFF_LW);

    {
        /* modify_field(ingress::tmpreg.ue_key,ue_service_req.ue_key) */

        /* primitive body */
        ingress__tmpreg->ue_key = ue_service_req->ue_key;

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
    case PIF_ACTION_ID_ingress__drop_act:
        ret = pif_action_exec_ingress__drop_act(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act:
        ret = pif_action_exec_ingress__act(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__populate_tun_egress_s3_uplink:
        ret = pif_action_exec_ingress__populate_tun_egress_s3_uplink(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
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
    case PIF_ACTION_ID_ingress__act_10:
        ret = pif_action_exec_ingress__act_10(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_11:
        ret = pif_action_exec_ingress__act_11(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
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
    case PIF_ACTION_ID_ingress__act_3:
        ret = pif_action_exec_ingress__act_3(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__populate_ip_op_tun_s1_uplink:
        ret = pif_action_exec_ingress__populate_ip_op_tun_s1_uplink(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_ingress__act_2:
        ret = pif_action_exec_ingress__act_2(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    }
#ifdef PIF_DEBUG
        mem_incr64((__mem __addr40 uint64_t *)(pif_act_stats + opdata->action_id));
#endif

    return ret;
}
