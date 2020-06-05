/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include "pif_common.h"

/****************************************
 * ingress_flow                         *
 ****************************************/

/* State transition functions */

static int handle_ingress_flow__condition_8(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_8_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_8");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_8: ((ipv4.ttl) == (250))
    {
    unsigned int pif_expression__condition_8_register_1;
    unsigned int pif_expression__condition_8_register_2;
    //subexpression 2: 250
    // constant : 0xfa

    //subexpression 0: (ipv4.ttl)==(250)
    pif_expression__condition_8_register_1 = ipv4->ttl;
    pif_expression__condition_8_register_2 = 0xfa;
    pif_expression__condition_8_register_0 = (pif_expression__condition_8_register_1 == pif_expression__condition_8_register_2);
    }

    if (pif_expression__condition_8_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s1_uplink;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow;
}

static int handle_ingress_flow_ingress__ip_op_tun_s1_uplink(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__ip_op_tun_s1_uplink");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__ip_op_tun_s1_uplink, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__tun_egress_s3_uplink; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_4(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_4_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_4");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_4: ((ipv4.protocol) == (6))
    {
    unsigned int pif_expression__condition_4_register_1;
    unsigned int pif_expression__condition_4_register_2;
    unsigned int pif_expression__condition_4_register_3;
    //subexpression 2: 6
    // constant : 0x6

    //subexpression 0: (ipv4.protocol)==(6)
    pif_expression__condition_4_register_1 = ipv4->protocol;
    pif_expression__condition_4_register_2 = 0x6;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_4_register_3 = pif_expression__condition_4_register_2 & 0x7;
    pif_expression__condition_4_register_0 = (pif_expression__condition_4_register_1 == pif_expression__condition_4_register_3);
    }

    if (pif_expression__condition_4_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_1;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_5;
}

static int handle_ingress_flow__condition_5(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_5_register_0;
    __lmem struct pif_header_ingress__scalars *ingress__scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_5");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    //expression _condition_5: (not((ingress::scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_5_register_1;
    //subexpression 0: not((ingress::scalars.hasReturned_0))
    pif_expression__condition_5_register_1 = ingress__scalars->hasReturned_0;
    pif_expression__condition_5_register_0 = (pif_expression__condition_5_register_1 == 0);
    }

    if (pif_expression__condition_5_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_6;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_7;
}

static int handle_ingress_flow__condition_7(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_7_register_0;
    __lmem struct pif_header_ingress__scalars *ingress__scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_7");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    //expression _condition_7: (not((ingress::scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_7_register_1;
    //subexpression 0: not((ingress::scalars.hasReturned_0))
    pif_expression__condition_7_register_1 = ingress__scalars->hasReturned_0;
    pif_expression__condition_7_register_0 = (pif_expression__condition_7_register_1 == 0);
    }

    if (pif_expression__condition_7_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_8;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow;
}

static int handle_ingress_flow__condition_6(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_6_register_0;
    __lmem struct pif_header_standard_metadata *standard_metadata;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_6");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);

    //expression _condition_6: ((standard_metadata.ingress_port) == (0))
    {
    unsigned int pif_expression__condition_6_register_1;
    unsigned int pif_expression__condition_6_register_2;
    unsigned int pif_expression__condition_6_register_3;
    //subexpression 2: 0
    // constant : 0x0

    //subexpression 0: (standard_metadata.ingress_port)==(0)
    pif_expression__condition_6_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_6_register_2 = 0x0;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_6_register_3 = pif_expression__condition_6_register_2 & 0x1;
    pif_expression__condition_6_register_0 = (pif_expression__condition_6_register_1 == pif_expression__condition_6_register_3);
    }

    if (pif_expression__condition_6_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_2;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_7;
}

static int handle_ingress_flow_ingress__tbl_act_1(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_1");
#endif

    {
        struct pif_action_actiondata_ingress__act_1 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_1 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_1 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_5; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_1(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_1_register_0;
    __lmem struct pif_header_ingress__scalars *ingress__scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_1");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    //expression _condition_1: (not((ingress::scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_1_register_1;
    //subexpression 0: not((ingress::scalars.hasReturned_0))
    pif_expression__condition_1_register_1 = ingress__scalars->hasReturned_0;
    pif_expression__condition_1_register_0 = (pif_expression__condition_1_register_1 == 0);
    }

    if (pif_expression__condition_1_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_2;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_5;
}

static int handle_ingress_flow__condition_2(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_2_register_0;
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_2");
#endif

    //expression _condition_2: (valid(ipv4))
    {
    //subexpression 0: valid(ipv4)
    pif_expression__condition_2_register_0 = PIF_PARREP_ipv4_VALID(prdata);
    }

    if (pif_expression__condition_2_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_3;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_5;
}

static int handle_ingress_flow__condition_0(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_0_register_0;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_0");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_0: ((ethernet.etherType) == (2054))
    {
    unsigned int pif_expression__condition_0_register_1;
    unsigned int pif_expression__condition_0_register_2;
    unsigned int pif_expression__condition_0_register_3;
    //subexpression 2: 2054
    // constant : 0x806

    //subexpression 0: (ethernet.etherType)==(2054)
    pif_expression__condition_0_register_1 = ethernet->etherType;
    pif_expression__condition_0_register_2 = 0x806;
    /* implicit cast 12 -> 16 */
    pif_expression__condition_0_register_3 = pif_expression__condition_0_register_2 & 0xfff;
    pif_expression__condition_0_register_0 = (pif_expression__condition_0_register_1 == pif_expression__condition_0_register_3);
    }

    if (pif_expression__condition_0_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__arp_tbl;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_1;
}

static int handle_ingress_flow_ingress__arp_tbl(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__arp_tbl");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__arp_tbl, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_0; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tun_egress_s3_uplink(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tun_egress_s3_uplink");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__tun_egress_s3_uplink, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act_2(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_2");
#endif

    {
        struct pif_action_actiondata_ingress__act_2 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_2 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_2 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_7; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act_0(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_0");
#endif

    {
        struct pif_action_actiondata_ingress__act actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_1; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act");
#endif

    {
        struct pif_action_actiondata_ingress__act_0 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_0 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_0 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_0; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_3(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_3_register_0;
    __lmem struct pif_header_standard_metadata *standard_metadata;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_3");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);

    //expression _condition_3: ((standard_metadata.ingress_port) == (768))
    {
    unsigned int pif_expression__condition_3_register_1;
    unsigned int pif_expression__condition_3_register_2;
    unsigned int pif_expression__condition_3_register_3;
    //subexpression 2: 768
    // constant : 0x300

    //subexpression 0: (standard_metadata.ingress_port)==(768)
    pif_expression__condition_3_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_3_register_2 = 0x300;
    /* implicit cast 10 -> 16 */
    pif_expression__condition_3_register_3 = pif_expression__condition_3_register_2 & 0x3ff;
    pif_expression__condition_3_register_0 = (pif_expression__condition_3_register_1 == pif_expression__condition_3_register_3);
    }

    if (pif_expression__condition_3_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_4;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_5;
}

/* Control flow entry point */

int pif_ctlflow_ingress_flow(int *start_state, __lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off)
{
    __gpr int actlen, totlen = 0;
    __gpr int ret;
    int pif_ctlflow_state_ingress_flow = PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act;

    while (pif_ctlflow_state_ingress_flow != PIF_CTLFLOW_STATE_ingress_flow_DONE) {
        PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_CONTROL, ((0 << 16) + pif_ctlflow_state_ingress_flow));
#ifdef PIF_DEBUG
        __debug_label("pif_ctlflow_state_ingress_flow");
#endif
        switch (pif_ctlflow_state_ingress_flow) {
        case PIF_CTLFLOW_STATE_ingress_flow__condition_8:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_8(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s1_uplink:
            ret = handle_ingress_flow_ingress__ip_op_tun_s1_uplink(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_4:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_4(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_5:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_5(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_7:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_7(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_6:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_6(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_1:
            ret = handle_ingress_flow_ingress__tbl_act_1(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_1:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_1(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_2:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_2(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_0:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_0(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__arp_tbl:
            ret = handle_ingress_flow_ingress__arp_tbl(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tun_egress_s3_uplink:
            ret = handle_ingress_flow_ingress__tun_egress_s3_uplink(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_2:
            ret = handle_ingress_flow_ingress__tbl_act_2(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_0:
            ret = handle_ingress_flow_ingress__tbl_act_0(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act:
            ret = handle_ingress_flow_ingress__tbl_act(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_3:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_3(_pif_parrep);
            continue;
        }
        if (actlen < 0) /* error! */
            return actlen & ((~(1 << PIF_LOOKUP_ERROR_BIT)));
        __critical_path();
        totlen += actlen;
        if (ret < 0)
            return -totlen;
    }

    return totlen;
}

/* Empty control flow */
int pif_ctlflow_egress_flow(int *start_state, __lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off)
{
    return 0;
}
