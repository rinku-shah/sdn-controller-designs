/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include "pif_common.h"

/****************************************
 * ingress_flow                         *
 ****************************************/

/* State transition functions */

static int handle_ingress_flow__condition_16(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_16_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_16");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_16: ((data.epc_traffic_code) == (19))
    {
    unsigned int pif_expression__condition_16_register_1;
    unsigned int pif_expression__condition_16_register_2;
    unsigned int pif_expression__condition_16_register_3;
    //subexpression 2: 19
    // constant : 0x13

    //subexpression 0: (data.epc_traffic_code)==(19)
    pif_expression__condition_16_register_1 = data->epc_traffic_code;
    pif_expression__condition_16_register_2 = 0x13;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_16_register_3 = pif_expression__condition_16_register_2 & 0x1f;
    pif_expression__condition_16_register_0 = (pif_expression__condition_16_register_1 == pif_expression__condition_16_register_3);
    }

    if (pif_expression__condition_16_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_9;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_17;
}

static int handle_ingress_flow_ingress__tbl_act_9(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_9");
#endif

    {
        struct pif_action_actiondata_ingress__act_9 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_9 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_9 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_17; /* always */

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

static int handle_ingress_flow__condition_2(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_2_register_7;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_2");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_2: ((((ethernet.etherType) == (2054))) and (((ethernet.dstAddr) == (219902325555))))
    {
    unsigned int pif_expression__condition_2_register_0;
    unsigned int pif_expression__condition_2_register_1;
    unsigned int pif_expression__condition_2_register_2;
    unsigned int pif_expression__condition_2_register_3;
    unsigned int pif_expression__condition_2_register_4;
    unsigned int pif_expression__condition_2_register_5;
    unsigned int pif_expression__condition_2_register_6;
    //subexpression 6: 2054
    // constant : 0x806

    //subexpression 1: (ethernet.etherType)==(2054)
    pif_expression__condition_2_register_1 = ethernet->etherType;
    pif_expression__condition_2_register_2 = 0x806;
    /* implicit cast 12 -> 16 */
    pif_expression__condition_2_register_3 = pif_expression__condition_2_register_2 & 0xfff;
    pif_expression__condition_2_register_0 = (pif_expression__condition_2_register_1 == pif_expression__condition_2_register_3);
    //subexpression 4: 219902325555
    // constant : 0x3333333333

    //subexpression 2: (ethernet.dstAddr)==(219902325555)
    pif_expression__condition_2_register_1 = ((ethernet->dstAddr & 0xffff) << 16) | ethernet->__dstAddr_1;
    pif_expression__condition_2_register_2 = ((ethernet->dstAddr >> 16) & 0xffff);
    pif_expression__condition_2_register_4 = 0x33333333;
    pif_expression__condition_2_register_5 = 0x33;
    /* implicit cast 38 -> 48 */
    pif_expression__condition_2_register_6 = pif_expression__condition_2_register_4;
    pif_expression__condition_2_register_7 = pif_expression__condition_2_register_5 & 0x3f;
    pif_expression__condition_2_register_3 = (pif_expression__condition_2_register_1 == pif_expression__condition_2_register_6) && (pif_expression__condition_2_register_2 == pif_expression__condition_2_register_7);
    //subexpression 0: (((ethernet.etherType)==(2054)))and(((ethernet.dstAddr)==(219902325555)))
    pif_expression__condition_2_register_7 = (pif_expression__condition_2_register_0) && (pif_expression__condition_2_register_3);
    }

    if (pif_expression__condition_2_register_7)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_1;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_3;
}

static int handle_ingress_flow_ingress__tbl_act_1(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_1");
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

static int handle_ingress_flow__condition_17(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_17_register_4;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_17");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_17: ((((data.epc_traffic_code) == (14))) or (((data.epc_traffic_code) == (19))))
    {
    unsigned int pif_expression__condition_17_register_0;
    unsigned int pif_expression__condition_17_register_1;
    unsigned int pif_expression__condition_17_register_2;
    unsigned int pif_expression__condition_17_register_3;
    //subexpression 6: 14
    // constant : 0xe

    //subexpression 1: (data.epc_traffic_code)==(14)
    pif_expression__condition_17_register_1 = data->epc_traffic_code;
    pif_expression__condition_17_register_2 = 0xe;
    /* implicit cast 4 -> 8 */
    pif_expression__condition_17_register_3 = pif_expression__condition_17_register_2 & 0xf;
    pif_expression__condition_17_register_0 = (pif_expression__condition_17_register_1 == pif_expression__condition_17_register_3);
    //subexpression 4: 19
    // constant : 0x13

    //subexpression 2: (data.epc_traffic_code)==(19)
    pif_expression__condition_17_register_1 = data->epc_traffic_code;
    pif_expression__condition_17_register_2 = 0x13;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_17_register_4 = pif_expression__condition_17_register_2 & 0x1f;
    pif_expression__condition_17_register_3 = (pif_expression__condition_17_register_1 == pif_expression__condition_17_register_4);
    //subexpression 0: (((data.epc_traffic_code)==(14)))or(((data.epc_traffic_code)==(19)))
    pif_expression__condition_17_register_4 = pif_expression__condition_17_register_0 || pif_expression__condition_17_register_3;
    }

    if (pif_expression__condition_17_register_4)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s2_downlink;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_18;
}

static int handle_ingress_flow__condition_10(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_10_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_10");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_10: ((ipv4.protocol) == (17))
    {
    unsigned int pif_expression__condition_10_register_1;
    unsigned int pif_expression__condition_10_register_2;
    unsigned int pif_expression__condition_10_register_3;
    //subexpression 2: 17
    // constant : 0x11

    //subexpression 0: (ipv4.protocol)==(17)
    pif_expression__condition_10_register_1 = ipv4->protocol;
    pif_expression__condition_10_register_2 = 0x11;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_10_register_3 = pif_expression__condition_10_register_2 & 0x1f;
    pif_expression__condition_10_register_0 = (pif_expression__condition_10_register_1 == pif_expression__condition_10_register_3);
    }

    if (pif_expression__condition_10_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_11;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_26;
}

static int handle_ingress_flow__condition_11(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_11_register_4;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_11");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_11: ((((((((((((data.epc_traffic_code) == (1))) or (((data.epc_traffic_code) == (3))))) or (((data.epc_traffic_code) == (20))))) or (((data.epc_traffic_code) == (5))))) or (((data.epc_traffic_code) == (7))))) or (((data.epc_traffic_code) == (9))))
    {
    unsigned int pif_expression__condition_11_register_0;
    unsigned int pif_expression__condition_11_register_1;
    unsigned int pif_expression__condition_11_register_2;
    unsigned int pif_expression__condition_11_register_3;
    //subexpression 22: 1
    // constant : 0x1

    //subexpression 17: (data.epc_traffic_code)==(1)
    pif_expression__condition_11_register_1 = data->epc_traffic_code;
    pif_expression__condition_11_register_2 = 0x1;
    /* implicit cast 1 -> 8 */
    pif_expression__condition_11_register_3 = pif_expression__condition_11_register_2 & 0x1;
    pif_expression__condition_11_register_0 = (pif_expression__condition_11_register_1 == pif_expression__condition_11_register_3);
    //subexpression 20: 3
    // constant : 0x3

    //subexpression 18: (data.epc_traffic_code)==(3)
    pif_expression__condition_11_register_1 = data->epc_traffic_code;
    pif_expression__condition_11_register_2 = 0x3;
    /* implicit cast 2 -> 8 */
    pif_expression__condition_11_register_4 = pif_expression__condition_11_register_2 & 0x3;
    pif_expression__condition_11_register_3 = (pif_expression__condition_11_register_1 == pif_expression__condition_11_register_4);
    //subexpression 13: (((data.epc_traffic_code)==(1)))or(((data.epc_traffic_code)==(3)))
    pif_expression__condition_11_register_4 = pif_expression__condition_11_register_0 || pif_expression__condition_11_register_3;
    //subexpression 16: 20
    // constant : 0x14

    //subexpression 14: (data.epc_traffic_code)==(20)
    pif_expression__condition_11_register_0 = data->epc_traffic_code;
    pif_expression__condition_11_register_1 = 0x14;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_11_register_2 = pif_expression__condition_11_register_1 & 0x1f;
    pif_expression__condition_11_register_3 = (pif_expression__condition_11_register_0 == pif_expression__condition_11_register_2);
    //subexpression 9: (((((data.epc_traffic_code)==(1)))or(((data.epc_traffic_code)==(3)))))or(((data.epc_traffic_code)==(20)))
    pif_expression__condition_11_register_2 = pif_expression__condition_11_register_4 || pif_expression__condition_11_register_3;
    //subexpression 12: 5
    // constant : 0x5

    //subexpression 10: (data.epc_traffic_code)==(5)
    pif_expression__condition_11_register_4 = data->epc_traffic_code;
    pif_expression__condition_11_register_0 = 0x5;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_11_register_1 = pif_expression__condition_11_register_0 & 0x7;
    pif_expression__condition_11_register_3 = (pif_expression__condition_11_register_4 == pif_expression__condition_11_register_1);
    //subexpression 5: (((((((data.epc_traffic_code)==(1)))or(((data.epc_traffic_code)==(3)))))or(((data.epc_traffic_code)==(20)))))or(((data.epc_traffic_code)==(5)))
    pif_expression__condition_11_register_1 = pif_expression__condition_11_register_2 || pif_expression__condition_11_register_3;
    //subexpression 8: 7
    // constant : 0x7

    //subexpression 6: (data.epc_traffic_code)==(7)
    pif_expression__condition_11_register_2 = data->epc_traffic_code;
    pif_expression__condition_11_register_4 = 0x7;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_11_register_0 = pif_expression__condition_11_register_4 & 0x7;
    pif_expression__condition_11_register_3 = (pif_expression__condition_11_register_2 == pif_expression__condition_11_register_0);
    //subexpression 1: (((((((((data.epc_traffic_code)==(1)))or(((data.epc_traffic_code)==(3)))))or(((data.epc_traffic_code)==(20)))))or(((data.epc_traffic_code)==(5)))))or(((data.epc_traffic_code)==(7)))
    pif_expression__condition_11_register_0 = pif_expression__condition_11_register_1 || pif_expression__condition_11_register_3;
    //subexpression 4: 9
    // constant : 0x9

    //subexpression 2: (data.epc_traffic_code)==(9)
    pif_expression__condition_11_register_1 = data->epc_traffic_code;
    pif_expression__condition_11_register_2 = 0x9;
    /* implicit cast 4 -> 8 */
    pif_expression__condition_11_register_4 = pif_expression__condition_11_register_2 & 0xf;
    pif_expression__condition_11_register_3 = (pif_expression__condition_11_register_1 == pif_expression__condition_11_register_4);
    //subexpression 0: (((((((((((data.epc_traffic_code)==(1)))or(((data.epc_traffic_code)==(3)))))or(((data.epc_traffic_code)==(20)))))or(((data.epc_traffic_code)==(5)))))or(((data.epc_traffic_code)==(7)))))or(((data.epc_traffic_code)==(9)))
    pif_expression__condition_11_register_4 = pif_expression__condition_11_register_0 || pif_expression__condition_11_register_3;
    }

    if (pif_expression__condition_11_register_4)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_6;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_12;
}

static int handle_ingress_flow_ingress__tbl_act_3(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_3");
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

static int handle_ingress_flow__condition_5(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_5_register_0;
    __lmem struct pif_header_scalars *scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_5");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    //expression _condition_5: (not((scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_5_register_1;
    //subexpression 0: not((scalars.hasReturned_0))
    pif_expression__condition_5_register_1 = scalars->hasReturned_0;
    pif_expression__condition_5_register_0 = (pif_expression__condition_5_register_1 == 0);
    }

    if (pif_expression__condition_5_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_4;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_6;
}

static int handle_ingress_flow__condition_12(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_12_register_0;
    __lmem struct pif_header_scalars *scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_12");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    //expression _condition_12: (not((scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_12_register_1;
    //subexpression 0: not((scalars.hasReturned_0))
    pif_expression__condition_12_register_1 = scalars->hasReturned_0;
    pif_expression__condition_12_register_0 = (pif_expression__condition_12_register_1 == 0);
    }

    if (pif_expression__condition_12_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_13;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_15;
}

static int handle_ingress_flow__condition_13(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_13_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_13");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_13: ((data.epc_traffic_code) == (14))
    {
    unsigned int pif_expression__condition_13_register_1;
    unsigned int pif_expression__condition_13_register_2;
    unsigned int pif_expression__condition_13_register_3;
    //subexpression 2: 14
    // constant : 0xe

    //subexpression 0: (data.epc_traffic_code)==(14)
    pif_expression__condition_13_register_1 = data->epc_traffic_code;
    pif_expression__condition_13_register_2 = 0xe;
    /* implicit cast 4 -> 8 */
    pif_expression__condition_13_register_3 = pif_expression__condition_13_register_2 & 0xf;
    pif_expression__condition_13_register_0 = (pif_expression__condition_13_register_1 == pif_expression__condition_13_register_3);
    }

    if (pif_expression__condition_13_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_7;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_14;
}

static int handle_ingress_flow_ingress__tbl_act_10(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_10");
#endif

    {
        struct pif_action_actiondata_ingress__act_10 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_10 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_10 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_19; /* always */

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

static int handle_ingress_flow__condition_19(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_19_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_19");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_19: ((data.epc_traffic_code) == (19))
    {
    unsigned int pif_expression__condition_19_register_1;
    unsigned int pif_expression__condition_19_register_2;
    unsigned int pif_expression__condition_19_register_3;
    //subexpression 2: 19
    // constant : 0x13

    //subexpression 0: (data.epc_traffic_code)==(19)
    pif_expression__condition_19_register_1 = data->epc_traffic_code;
    pif_expression__condition_19_register_2 = 0x13;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_19_register_3 = pif_expression__condition_19_register_2 & 0x1f;
    pif_expression__condition_19_register_0 = (pif_expression__condition_19_register_1 == pif_expression__condition_19_register_3);
    }

    if (pif_expression__condition_19_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_11;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_20;
}

static int handle_ingress_flow__condition_14(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_14_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_14");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_14: ((data.epc_traffic_code) == (17))
    {
    unsigned int pif_expression__condition_14_register_1;
    unsigned int pif_expression__condition_14_register_2;
    unsigned int pif_expression__condition_14_register_3;
    //subexpression 2: 17
    // constant : 0x11

    //subexpression 0: (data.epc_traffic_code)==(17)
    pif_expression__condition_14_register_1 = data->epc_traffic_code;
    pif_expression__condition_14_register_2 = 0x11;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_14_register_3 = pif_expression__condition_14_register_2 & 0x1f;
    pif_expression__condition_14_register_0 = (pif_expression__condition_14_register_1 == pif_expression__condition_14_register_3);
    }

    if (pif_expression__condition_14_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__service_req_uekey_sgwteid_map;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_15;
}

static int handle_ingress_flow__condition_15(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_15_register_0;
    __lmem struct pif_header_scalars *scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_15");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    //expression _condition_15: (not((scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_15_register_1;
    //subexpression 0: not((scalars.hasReturned_0))
    pif_expression__condition_15_register_1 = scalars->hasReturned_0;
    pif_expression__condition_15_register_0 = (pif_expression__condition_15_register_1 == 0);
    }

    if (pif_expression__condition_15_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_16;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_23;
}

static int handle_ingress_flow_ingress__uekey_guti_map(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__uekey_guti_map");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__uekey_guti_map, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s2_uplink; /* always */

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

static int handle_ingress_flow_ingress__ip_op_tun_s2_uplink(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__ip_op_tun_s2_uplink");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__ip_op_tun_s2_uplink, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__ctxt_setup_uekey_sgwteid_map; /* always */

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

static int handle_ingress_flow__condition_27(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_27_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_27");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_27: ((ipv4.protocol) == (6))
    {
    unsigned int pif_expression__condition_27_register_1;
    unsigned int pif_expression__condition_27_register_2;
    unsigned int pif_expression__condition_27_register_3;
    //subexpression 2: 6
    // constant : 0x6

    //subexpression 0: (ipv4.protocol)==(6)
    pif_expression__condition_27_register_1 = ipv4->protocol;
    pif_expression__condition_27_register_2 = 0x6;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_27_register_3 = pif_expression__condition_27_register_2 & 0x7;
    pif_expression__condition_27_register_0 = (pif_expression__condition_27_register_1 == pif_expression__condition_27_register_3);
    }

    if (pif_expression__condition_27_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_28;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_32;
}

static int handle_ingress_flow__condition_28(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_28_register_2;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_28");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_28: ((((standard_metadata.ingress_port) == (1))) and (((ipv4.dstAddr) == (3232236035))))
    {
    unsigned int pif_expression__condition_28_register_0;
    unsigned int pif_expression__condition_28_register_1;
    unsigned int pif_expression__condition_28_register_3;
    //subexpression 6: 1
    // constant : 0x1

    //subexpression 1: (standard_metadata.ingress_port)==(1)
    pif_expression__condition_28_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_28_register_2 = 0x1;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_28_register_3 = pif_expression__condition_28_register_2 & 0x1;
    pif_expression__condition_28_register_0 = (pif_expression__condition_28_register_1 == pif_expression__condition_28_register_3);
    //subexpression 4: 3232236035
    // constant : 0xc0a80203

    //subexpression 2: (ipv4.dstAddr)==(3232236035)
    pif_expression__condition_28_register_1 = ipv4->dstAddr;
    pif_expression__condition_28_register_2 = 0xc0a80203;
    pif_expression__condition_28_register_3 = (pif_expression__condition_28_register_1 == pif_expression__condition_28_register_2);
    //subexpression 0: (((standard_metadata.ingress_port)==(1)))and(((ipv4.dstAddr)==(3232236035)))
    pif_expression__condition_28_register_2 = (pif_expression__condition_28_register_0) && (pif_expression__condition_28_register_3);
    }

    if (pif_expression__condition_28_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_18;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_29;
}

static int handle_ingress_flow_ingress__ip_op_tun_s2_downlink(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__ip_op_tun_s2_downlink");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__ip_op_tun_s2_downlink, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_18; /* always */

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

static int handle_ingress_flow__condition_23(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_23_register_0;
    __lmem struct pif_header_scalars *scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_23");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    //expression _condition_23: (not((scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_23_register_1;
    //subexpression 0: not((scalars.hasReturned_0))
    pif_expression__condition_23_register_1 = scalars->hasReturned_0;
    pif_expression__condition_23_register_0 = (pif_expression__condition_23_register_1 == 0);
    }

    if (pif_expression__condition_23_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_24;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_26;
}

static int handle_ingress_flow__condition_24(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_24_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_24");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_24: ((data.epc_traffic_code) == (19))
    {
    unsigned int pif_expression__condition_24_register_1;
    unsigned int pif_expression__condition_24_register_2;
    unsigned int pif_expression__condition_24_register_3;
    //subexpression 2: 19
    // constant : 0x13

    //subexpression 0: (data.epc_traffic_code)==(19)
    pif_expression__condition_24_register_1 = data->epc_traffic_code;
    pif_expression__condition_24_register_2 = 0x13;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_24_register_3 = pif_expression__condition_24_register_2 & 0x1f;
    pif_expression__condition_24_register_0 = (pif_expression__condition_24_register_1 == pif_expression__condition_24_register_3);
    }

    if (pif_expression__condition_24_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_15;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_26;
}

static int handle_ingress_flow_ingress__ctxt_setup_uekey_sgwteid_map(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__ctxt_setup_uekey_sgwteid_map");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__ctxt_setup_uekey_sgwteid_map, _pif_parrep, actbuf, actbuf_off);
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

static int handle_ingress_flow__condition_33(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_33_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_33");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_33: ((ipv4.ttl) == (250))
    {
    unsigned int pif_expression__condition_33_register_1;
    unsigned int pif_expression__condition_33_register_2;
    //subexpression 2: 250
    // constant : 0xfa

    //subexpression 0: (ipv4.ttl)==(250)
    pif_expression__condition_33_register_1 = ipv4->ttl;
    pif_expression__condition_33_register_2 = 0xfa;
    pif_expression__condition_33_register_0 = (pif_expression__condition_33_register_1 == pif_expression__condition_33_register_2);
    }

    if (pif_expression__condition_33_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__uekey_guti_map;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow;
}

static int handle_ingress_flow_ingress__tbl_act_7(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_7");
#endif

    {
        struct pif_action_actiondata_ingress__act_7 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_7 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_7 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_14; /* always */

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

static int handle_ingress_flow__condition_29(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_29_register_2;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_29");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_29: ((((standard_metadata.ingress_port) == (1))) and (((ipv4.dstAddr) == (3232236036))))
    {
    unsigned int pif_expression__condition_29_register_0;
    unsigned int pif_expression__condition_29_register_1;
    unsigned int pif_expression__condition_29_register_3;
    //subexpression 6: 1
    // constant : 0x1

    //subexpression 1: (standard_metadata.ingress_port)==(1)
    pif_expression__condition_29_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_29_register_2 = 0x1;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_29_register_3 = pif_expression__condition_29_register_2 & 0x1;
    pif_expression__condition_29_register_0 = (pif_expression__condition_29_register_1 == pif_expression__condition_29_register_3);
    //subexpression 4: 3232236036
    // constant : 0xc0a80204

    //subexpression 2: (ipv4.dstAddr)==(3232236036)
    pif_expression__condition_29_register_1 = ipv4->dstAddr;
    pif_expression__condition_29_register_2 = 0xc0a80204;
    pif_expression__condition_29_register_3 = (pif_expression__condition_29_register_1 == pif_expression__condition_29_register_2);
    //subexpression 0: (((standard_metadata.ingress_port)==(1)))and(((ipv4.dstAddr)==(3232236036)))
    pif_expression__condition_29_register_2 = (pif_expression__condition_29_register_0) && (pif_expression__condition_29_register_3);
    }

    if (pif_expression__condition_29_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_19;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_30;
}

static int handle_ingress_flow_ingress__tbl_act_19(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_19");
#endif

    {
        struct pif_action_actiondata_ingress__act_19 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_19 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_19 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_32; /* always */

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

static int handle_ingress_flow__condition_20(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_20_register_4;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_20");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_20: ((((data.epc_traffic_code) == (14))) or (((data.epc_traffic_code) == (19))))
    {
    unsigned int pif_expression__condition_20_register_0;
    unsigned int pif_expression__condition_20_register_1;
    unsigned int pif_expression__condition_20_register_2;
    unsigned int pif_expression__condition_20_register_3;
    //subexpression 6: 14
    // constant : 0xe

    //subexpression 1: (data.epc_traffic_code)==(14)
    pif_expression__condition_20_register_1 = data->epc_traffic_code;
    pif_expression__condition_20_register_2 = 0xe;
    /* implicit cast 4 -> 8 */
    pif_expression__condition_20_register_3 = pif_expression__condition_20_register_2 & 0xf;
    pif_expression__condition_20_register_0 = (pif_expression__condition_20_register_1 == pif_expression__condition_20_register_3);
    //subexpression 4: 19
    // constant : 0x13

    //subexpression 2: (data.epc_traffic_code)==(19)
    pif_expression__condition_20_register_1 = data->epc_traffic_code;
    pif_expression__condition_20_register_2 = 0x13;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_20_register_4 = pif_expression__condition_20_register_2 & 0x1f;
    pif_expression__condition_20_register_3 = (pif_expression__condition_20_register_1 == pif_expression__condition_20_register_4);
    //subexpression 0: (((data.epc_traffic_code)==(14)))or(((data.epc_traffic_code)==(19)))
    pif_expression__condition_20_register_4 = pif_expression__condition_20_register_0 || pif_expression__condition_20_register_3;
    }

    if (pif_expression__condition_20_register_4)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__uekey_uestate_map;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_21;
}

static int handle_ingress_flow_ingress__tbl_act_6(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_6");
#endif

    {
        struct pif_action_actiondata_ingress__act_6 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_6 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_6 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_12; /* always */

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

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_5; /* always */

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

static int handle_ingress_flow_ingress__tbl_act_5(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_5");
#endif

    {
        struct pif_action_actiondata_ingress__act_5 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_5 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_5 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_8; /* always */

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

static int handle_ingress_flow__condition_32(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_32_register_0;
    __lmem struct pif_header_scalars *scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_32");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    //expression _condition_32: (not((scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_32_register_1;
    //subexpression 0: not((scalars.hasReturned_0))
    pif_expression__condition_32_register_1 = scalars->hasReturned_0;
    pif_expression__condition_32_register_0 = (pif_expression__condition_32_register_1 == 0);
    }

    if (pif_expression__condition_32_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_33;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow;
}

static int handle_ingress_flow__condition_3(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_3_register_2;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_3");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_3: ((((ipv4.protocol) == (6))) and (((ipv4.dstAddr) == (3232236034))))
    {
    unsigned int pif_expression__condition_3_register_0;
    unsigned int pif_expression__condition_3_register_1;
    unsigned int pif_expression__condition_3_register_3;
    //subexpression 6: 6
    // constant : 0x6

    //subexpression 1: (ipv4.protocol)==(6)
    pif_expression__condition_3_register_1 = ipv4->protocol;
    pif_expression__condition_3_register_2 = 0x6;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_3_register_3 = pif_expression__condition_3_register_2 & 0x7;
    pif_expression__condition_3_register_0 = (pif_expression__condition_3_register_1 == pif_expression__condition_3_register_3);
    //subexpression 4: 3232236034
    // constant : 0xc0a80202

    //subexpression 2: (ipv4.dstAddr)==(3232236034)
    pif_expression__condition_3_register_1 = ipv4->dstAddr;
    pif_expression__condition_3_register_2 = 0xc0a80202;
    pif_expression__condition_3_register_3 = (pif_expression__condition_3_register_1 == pif_expression__condition_3_register_2);
    //subexpression 0: (((ipv4.protocol)==(6)))and(((ipv4.dstAddr)==(3232236034)))
    pif_expression__condition_3_register_2 = (pif_expression__condition_3_register_0) && (pif_expression__condition_3_register_3);
    }

    if (pif_expression__condition_3_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_2;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_4;
}

static int handle_ingress_flow__condition_21(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_21_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_21");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_21: ((data.epc_traffic_code) == (14))
    {
    unsigned int pif_expression__condition_21_register_1;
    unsigned int pif_expression__condition_21_register_2;
    unsigned int pif_expression__condition_21_register_3;
    //subexpression 2: 14
    // constant : 0xe

    //subexpression 0: (data.epc_traffic_code)==(14)
    pif_expression__condition_21_register_1 = data->epc_traffic_code;
    pif_expression__condition_21_register_2 = 0xe;
    /* implicit cast 4 -> 8 */
    pif_expression__condition_21_register_3 = pif_expression__condition_21_register_2 & 0xf;
    pif_expression__condition_21_register_0 = (pif_expression__condition_21_register_1 == pif_expression__condition_21_register_3);
    }

    if (pif_expression__condition_21_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_12;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_23;
}

static int handle_ingress_flow__condition_7(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_7_register_0;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_7");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_7: ((ethernet.etherType) == (2054))
    {
    unsigned int pif_expression__condition_7_register_1;
    unsigned int pif_expression__condition_7_register_2;
    unsigned int pif_expression__condition_7_register_3;
    //subexpression 2: 2054
    // constant : 0x806

    //subexpression 0: (ethernet.etherType)==(2054)
    pif_expression__condition_7_register_1 = ethernet->etherType;
    pif_expression__condition_7_register_2 = 0x806;
    /* implicit cast 12 -> 16 */
    pif_expression__condition_7_register_3 = pif_expression__condition_7_register_2 & 0xfff;
    pif_expression__condition_7_register_0 = (pif_expression__condition_7_register_1 == pif_expression__condition_7_register_3);
    }

    if (pif_expression__condition_7_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__arp_tbl;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_8;
}

static int handle_ingress_flow__condition_8(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_8_register_0;
    __lmem struct pif_header_scalars *scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_8");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    //expression _condition_8: (not((scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_8_register_1;
    //subexpression 0: not((scalars.hasReturned_0))
    pif_expression__condition_8_register_1 = scalars->hasReturned_0;
    pif_expression__condition_8_register_0 = (pif_expression__condition_8_register_1 == 0);
    }

    if (pif_expression__condition_8_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_9;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_26;
}

static int handle_ingress_flow__condition_18(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_18_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_18");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_18: ((data.epc_traffic_code) == (14))
    {
    unsigned int pif_expression__condition_18_register_1;
    unsigned int pif_expression__condition_18_register_2;
    unsigned int pif_expression__condition_18_register_3;
    //subexpression 2: 14
    // constant : 0xe

    //subexpression 0: (data.epc_traffic_code)==(14)
    pif_expression__condition_18_register_1 = data->epc_traffic_code;
    pif_expression__condition_18_register_2 = 0xe;
    /* implicit cast 4 -> 8 */
    pif_expression__condition_18_register_3 = pif_expression__condition_18_register_2 & 0xf;
    pif_expression__condition_18_register_0 = (pif_expression__condition_18_register_1 == pif_expression__condition_18_register_3);
    }

    if (pif_expression__condition_18_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_10;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_19;
}

static int handle_ingress_flow__condition_25(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_25_register_0;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_25");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_25: ((ethernet.srcAddr) == (95542485674))
    {
    unsigned int pif_expression__condition_25_register_1;
    unsigned int pif_expression__condition_25_register_2;
    unsigned int pif_expression__condition_25_register_3;
    unsigned int pif_expression__condition_25_register_4;
    unsigned int pif_expression__condition_25_register_5;
    unsigned int pif_expression__condition_25_register_6;
    //subexpression 2: 95542485674
    // constant : 0x163ec6a2aa

    //subexpression 0: (ethernet.srcAddr)==(95542485674)
    pif_expression__condition_25_register_1 = ethernet->__srcAddr_1;
    pif_expression__condition_25_register_2 = ethernet->srcAddr;
    pif_expression__condition_25_register_3 = 0x3ec6a2aa;
    pif_expression__condition_25_register_4 = 0x16;
    /* implicit cast 37 -> 48 */
    pif_expression__condition_25_register_5 = pif_expression__condition_25_register_3;
    pif_expression__condition_25_register_6 = pif_expression__condition_25_register_4 & 0x1f;
    pif_expression__condition_25_register_0 = (pif_expression__condition_25_register_1 == pif_expression__condition_25_register_5) && (pif_expression__condition_25_register_2 == pif_expression__condition_25_register_6);
    }

    if (pif_expression__condition_25_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_16;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_17;
}

static int handle_ingress_flow_ingress__tbl_act_16(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_16");
#endif

    {
        struct pif_action_actiondata_ingress__act_15 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_15 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_15 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_17; /* always */

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

static int handle_ingress_flow_ingress__service_req_uekey_sgwteid_map(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__service_req_uekey_sgwteid_map");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__service_req_uekey_sgwteid_map, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_8; /* always */

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

static int handle_ingress_flow_ingress__tbl_act_17(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_17");
#endif

    {
        struct pif_action_actiondata_ingress__act_17 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_17 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_17 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_26; /* always */

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

static int handle_ingress_flow__condition_26(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_26_register_0;
    __lmem struct pif_header_scalars *scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_26");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    //expression _condition_26: (not((scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_26_register_1;
    //subexpression 0: not((scalars.hasReturned_0))
    pif_expression__condition_26_register_1 = scalars->hasReturned_0;
    pif_expression__condition_26_register_0 = (pif_expression__condition_26_register_1 == 0);
    }

    if (pif_expression__condition_26_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_27;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_32;
}

static int handle_ingress_flow_ingress__tbl_act_8(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_8");
#endif

    {
        struct pif_action_actiondata_ingress__act_8 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_8 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_8 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_15; /* always */

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
    unsigned int pif_expression__condition_1_register_7;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_1");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_1: ((((ethernet.etherType) == (2054))) and (((ethernet.dstAddr) == (73300775185))))
    {
    unsigned int pif_expression__condition_1_register_0;
    unsigned int pif_expression__condition_1_register_1;
    unsigned int pif_expression__condition_1_register_2;
    unsigned int pif_expression__condition_1_register_3;
    unsigned int pif_expression__condition_1_register_4;
    unsigned int pif_expression__condition_1_register_5;
    unsigned int pif_expression__condition_1_register_6;
    //subexpression 6: 2054
    // constant : 0x806

    //subexpression 1: (ethernet.etherType)==(2054)
    pif_expression__condition_1_register_1 = ethernet->etherType;
    pif_expression__condition_1_register_2 = 0x806;
    /* implicit cast 12 -> 16 */
    pif_expression__condition_1_register_3 = pif_expression__condition_1_register_2 & 0xfff;
    pif_expression__condition_1_register_0 = (pif_expression__condition_1_register_1 == pif_expression__condition_1_register_3);
    //subexpression 4: 73300775185
    // constant : 0x1111111111

    //subexpression 2: (ethernet.dstAddr)==(73300775185)
    pif_expression__condition_1_register_1 = ((ethernet->dstAddr & 0xffff) << 16) | ethernet->__dstAddr_1;
    pif_expression__condition_1_register_2 = ((ethernet->dstAddr >> 16) & 0xffff);
    pif_expression__condition_1_register_4 = 0x11111111;
    pif_expression__condition_1_register_5 = 0x11;
    /* implicit cast 37 -> 48 */
    pif_expression__condition_1_register_6 = pif_expression__condition_1_register_4;
    pif_expression__condition_1_register_7 = pif_expression__condition_1_register_5 & 0x1f;
    pif_expression__condition_1_register_3 = (pif_expression__condition_1_register_1 == pif_expression__condition_1_register_6) && (pif_expression__condition_1_register_2 == pif_expression__condition_1_register_7);
    //subexpression 0: (((ethernet.etherType)==(2054)))and(((ethernet.dstAddr)==(73300775185)))
    pif_expression__condition_1_register_7 = (pif_expression__condition_1_register_0) && (pif_expression__condition_1_register_3);
    }

    if (pif_expression__condition_1_register_7)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_0;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_2;
}

static int handle_ingress_flow__condition_31(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_31_register_2;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_31");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_31: ((((standard_metadata.ingress_port) == (0))) and (((ipv4.dstAddr) == (3232236034))))
    {
    unsigned int pif_expression__condition_31_register_0;
    unsigned int pif_expression__condition_31_register_1;
    unsigned int pif_expression__condition_31_register_3;
    //subexpression 6: 0
    // constant : 0x0

    //subexpression 1: (standard_metadata.ingress_port)==(0)
    pif_expression__condition_31_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_31_register_2 = 0x0;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_31_register_3 = pif_expression__condition_31_register_2 & 0x1;
    pif_expression__condition_31_register_0 = (pif_expression__condition_31_register_1 == pif_expression__condition_31_register_3);
    //subexpression 4: 3232236034
    // constant : 0xc0a80202

    //subexpression 2: (ipv4.dstAddr)==(3232236034)
    pif_expression__condition_31_register_1 = ipv4->dstAddr;
    pif_expression__condition_31_register_2 = 0xc0a80202;
    pif_expression__condition_31_register_3 = (pif_expression__condition_31_register_1 == pif_expression__condition_31_register_2);
    //subexpression 0: (((standard_metadata.ingress_port)==(0)))and(((ipv4.dstAddr)==(3232236034)))
    pif_expression__condition_31_register_2 = (pif_expression__condition_31_register_0) && (pif_expression__condition_31_register_3);
    }

    if (pif_expression__condition_31_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_21;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_32;
}

static int handle_ingress_flow_ingress__tbl_act_12(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_12");
#endif

    {
        struct pif_action_actiondata_ingress__act_13 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_13 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_13 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_22; /* always */

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

static int handle_ingress_flow_ingress__tbl_act_11(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_11");
#endif

    {
        struct pif_action_actiondata_ingress__act_11 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_11 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_11 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_20; /* always */

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

static int handle_ingress_flow__condition_30(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_30_register_2;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_30");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_30: ((((standard_metadata.ingress_port) == (0))) and (((ipv4.dstAddr) == (3232236035))))
    {
    unsigned int pif_expression__condition_30_register_0;
    unsigned int pif_expression__condition_30_register_1;
    unsigned int pif_expression__condition_30_register_3;
    //subexpression 6: 0
    // constant : 0x0

    //subexpression 1: (standard_metadata.ingress_port)==(0)
    pif_expression__condition_30_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_30_register_2 = 0x0;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_30_register_3 = pif_expression__condition_30_register_2 & 0x1;
    pif_expression__condition_30_register_0 = (pif_expression__condition_30_register_1 == pif_expression__condition_30_register_3);
    //subexpression 4: 3232236035
    // constant : 0xc0a80203

    //subexpression 2: (ipv4.dstAddr)==(3232236035)
    pif_expression__condition_30_register_1 = ipv4->dstAddr;
    pif_expression__condition_30_register_2 = 0xc0a80203;
    pif_expression__condition_30_register_3 = (pif_expression__condition_30_register_1 == pif_expression__condition_30_register_2);
    //subexpression 0: (((standard_metadata.ingress_port)==(0)))and(((ipv4.dstAddr)==(3232236035)))
    pif_expression__condition_30_register_2 = (pif_expression__condition_30_register_0) && (pif_expression__condition_30_register_3);
    }

    if (pif_expression__condition_30_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_20;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_31;
}

static int handle_ingress_flow_ingress__tbl_act_15(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_15");
#endif

    {
        struct pif_action_actiondata_ingress__act_16 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_16 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_16 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_25; /* always */

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

static int handle_ingress_flow__condition_9(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_9_register_0;
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_9");
#endif

    //expression _condition_9: (valid(ipv4))
    {
    //subexpression 0: valid(ipv4)
    pif_expression__condition_9_register_0 = PIF_PARREP_ipv4_VALID(prdata);
    }

    if (pif_expression__condition_9_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_10;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_26;
}

static int handle_ingress_flow_ingress__tbl_act_21(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_21");
#endif

    {
        struct pif_action_actiondata_ingress__act_21 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_21 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_21 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_32; /* always */

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

static int handle_ingress_flow_ingress__tbl_act_20(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_20");
#endif

    {
        struct pif_action_actiondata_ingress__act_20 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_20 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_20 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_32; /* always */

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

static int handle_ingress_flow_ingress__tbl_act_4(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_4");
#endif

    {
        struct pif_action_actiondata_ingress__act_3 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_3 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_3 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_6; /* always */

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

static int handle_ingress_flow__condition_6(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_6_register_0;
    __lmem struct pif_header_scalars *scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_6");
#endif

    scalars = (__lmem struct pif_header_scalars *) (_pif_parrep + PIF_PARREP_scalars_OFF_LW);

    //expression _condition_6: (not((scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_6_register_1;
    //subexpression 0: not((scalars.hasReturned_0))
    pif_expression__condition_6_register_1 = scalars->hasReturned_0;
    pif_expression__condition_6_register_0 = (pif_expression__condition_6_register_1 == 0);
    }

    if (pif_expression__condition_6_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_7;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_8;
}

static int handle_ingress_flow_ingress__tbl_act(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act");
#endif

    {
        struct pif_action_actiondata_ingress__act_4 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_4 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_4 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
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

static int handle_ingress_flow__condition_0(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_0_register_0;
    __lmem struct pif_header_standard_metadata *standard_metadata;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_0");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);

    //expression _condition_0: ((standard_metadata.ingress_port) == (768))
    {
    unsigned int pif_expression__condition_0_register_1;
    unsigned int pif_expression__condition_0_register_2;
    unsigned int pif_expression__condition_0_register_3;
    //subexpression 2: 768
    // constant : 0x300

    //subexpression 0: (standard_metadata.ingress_port)==(768)
    pif_expression__condition_0_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_0_register_2 = 0x300;
    /* implicit cast 10 -> 16 */
    pif_expression__condition_0_register_3 = pif_expression__condition_0_register_2 & 0x3ff;
    pif_expression__condition_0_register_0 = (pif_expression__condition_0_register_1 == pif_expression__condition_0_register_3);
    }

    if (pif_expression__condition_0_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_1;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_6;
}

static int handle_ingress_flow_ingress__tbl_act_2(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_2");
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

static int handle_ingress_flow__condition_22(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_22_register_0;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_22");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_22: ((ethernet.srcAddr) == (95542485674))
    {
    unsigned int pif_expression__condition_22_register_1;
    unsigned int pif_expression__condition_22_register_2;
    unsigned int pif_expression__condition_22_register_3;
    unsigned int pif_expression__condition_22_register_4;
    unsigned int pif_expression__condition_22_register_5;
    unsigned int pif_expression__condition_22_register_6;
    //subexpression 2: 95542485674
    // constant : 0x163ec6a2aa

    //subexpression 0: (ethernet.srcAddr)==(95542485674)
    pif_expression__condition_22_register_1 = ethernet->__srcAddr_1;
    pif_expression__condition_22_register_2 = ethernet->srcAddr;
    pif_expression__condition_22_register_3 = 0x3ec6a2aa;
    pif_expression__condition_22_register_4 = 0x16;
    /* implicit cast 37 -> 48 */
    pif_expression__condition_22_register_5 = pif_expression__condition_22_register_3;
    pif_expression__condition_22_register_6 = pif_expression__condition_22_register_4 & 0x1f;
    pif_expression__condition_22_register_0 = (pif_expression__condition_22_register_1 == pif_expression__condition_22_register_5) && (pif_expression__condition_22_register_2 == pif_expression__condition_22_register_6);
    }

    if (pif_expression__condition_22_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_13;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_14;
}

static int handle_ingress_flow_ingress__tbl_act_13(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_13");
#endif

    {
        struct pif_action_actiondata_ingress__act_12 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_12 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_12 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_14; /* always */

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

static int handle_ingress_flow_ingress__tbl_act_18(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_18");
#endif

    {
        struct pif_action_actiondata_ingress__act_18 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_18 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_18 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_32; /* always */

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
    unsigned int pif_expression__condition_4_register_2;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_4");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_4: ((((ipv4.protocol) == (6))) and (((ipv4.dstAddr) == (3232236036))))
    {
    unsigned int pif_expression__condition_4_register_0;
    unsigned int pif_expression__condition_4_register_1;
    unsigned int pif_expression__condition_4_register_3;
    //subexpression 6: 6
    // constant : 0x6

    //subexpression 1: (ipv4.protocol)==(6)
    pif_expression__condition_4_register_1 = ipv4->protocol;
    pif_expression__condition_4_register_2 = 0x6;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_4_register_3 = pif_expression__condition_4_register_2 & 0x7;
    pif_expression__condition_4_register_0 = (pif_expression__condition_4_register_1 == pif_expression__condition_4_register_3);
    //subexpression 4: 3232236036
    // constant : 0xc0a80204

    //subexpression 2: (ipv4.dstAddr)==(3232236036)
    pif_expression__condition_4_register_1 = ipv4->dstAddr;
    pif_expression__condition_4_register_2 = 0xc0a80204;
    pif_expression__condition_4_register_3 = (pif_expression__condition_4_register_1 == pif_expression__condition_4_register_2);
    //subexpression 0: (((ipv4.protocol)==(6)))and(((ipv4.dstAddr)==(3232236036)))
    pif_expression__condition_4_register_2 = (pif_expression__condition_4_register_0) && (pif_expression__condition_4_register_3);
    }

    if (pif_expression__condition_4_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_3;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_5;
}

static int handle_ingress_flow_ingress__uekey_uestate_map(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__uekey_uestate_map");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__uekey_uestate_map, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_21; /* always */

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

static int handle_ingress_flow_ingress__tbl_act_14(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_14");
#endif

    {
        struct pif_action_actiondata_ingress__act_14 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_14 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_14 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_23; /* always */

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
        case PIF_CTLFLOW_STATE_ingress_flow__condition_16:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_16(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_9:
            ret = handle_ingress_flow_ingress__tbl_act_9(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_2:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_2(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_1:
            ret = handle_ingress_flow_ingress__tbl_act_1(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_17:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_17(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_10:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_10(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_11:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_11(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_3:
            ret = handle_ingress_flow_ingress__tbl_act_3(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_5:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_5(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_12:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_12(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_13:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_13(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_10:
            ret = handle_ingress_flow_ingress__tbl_act_10(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_19:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_19(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_14:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_14(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_15:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_15(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__uekey_guti_map:
            ret = handle_ingress_flow_ingress__uekey_guti_map(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s2_uplink:
            ret = handle_ingress_flow_ingress__ip_op_tun_s2_uplink(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_27:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_27(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_28:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_28(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s2_downlink:
            ret = handle_ingress_flow_ingress__ip_op_tun_s2_downlink(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_23:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_23(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_24:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_24(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__ctxt_setup_uekey_sgwteid_map:
            ret = handle_ingress_flow_ingress__ctxt_setup_uekey_sgwteid_map(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_33:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_33(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_7:
            ret = handle_ingress_flow_ingress__tbl_act_7(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_29:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_29(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_19:
            ret = handle_ingress_flow_ingress__tbl_act_19(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_20:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_20(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_6:
            ret = handle_ingress_flow_ingress__tbl_act_6(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__arp_tbl:
            ret = handle_ingress_flow_ingress__arp_tbl(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_5:
            ret = handle_ingress_flow_ingress__tbl_act_5(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_32:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_32(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_3:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_3(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_21:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_21(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_7:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_7(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_8:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_8(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_18:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_18(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_25:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_25(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_16:
            ret = handle_ingress_flow_ingress__tbl_act_16(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__service_req_uekey_sgwteid_map:
            ret = handle_ingress_flow_ingress__service_req_uekey_sgwteid_map(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_17:
            ret = handle_ingress_flow_ingress__tbl_act_17(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_26:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_26(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_8:
            ret = handle_ingress_flow_ingress__tbl_act_8(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_1:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_1(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_31:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_31(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_12:
            ret = handle_ingress_flow_ingress__tbl_act_12(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_11:
            ret = handle_ingress_flow_ingress__tbl_act_11(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_0:
            ret = handle_ingress_flow_ingress__tbl_act_0(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_30:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_30(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_15:
            ret = handle_ingress_flow_ingress__tbl_act_15(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_9:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_9(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_21:
            ret = handle_ingress_flow_ingress__tbl_act_21(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_20:
            ret = handle_ingress_flow_ingress__tbl_act_20(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_4:
            ret = handle_ingress_flow_ingress__tbl_act_4(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_6:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_6(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act:
            ret = handle_ingress_flow_ingress__tbl_act(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_0:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_0(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_2:
            ret = handle_ingress_flow_ingress__tbl_act_2(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_22:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_22(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_13:
            ret = handle_ingress_flow_ingress__tbl_act_13(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_18:
            ret = handle_ingress_flow_ingress__tbl_act_18(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_4:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_4(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__uekey_uestate_map:
            ret = handle_ingress_flow_ingress__uekey_uestate_map(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_14:
            ret = handle_ingress_flow_ingress__tbl_act_14(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
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

/****************************************
 * egress_flow                          *
 ****************************************/

/* State transition functions */

static int handle_egress_flow__condition_39(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_39_register_0;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow__condition_39");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_39: ((ethernet.srcAddr) == (95542485674))
    {
    unsigned int pif_expression__condition_39_register_1;
    unsigned int pif_expression__condition_39_register_2;
    unsigned int pif_expression__condition_39_register_3;
    unsigned int pif_expression__condition_39_register_4;
    unsigned int pif_expression__condition_39_register_5;
    unsigned int pif_expression__condition_39_register_6;
    //subexpression 2: 95542485674
    // constant : 0x163ec6a2aa

    //subexpression 0: (ethernet.srcAddr)==(95542485674)
    pif_expression__condition_39_register_1 = ethernet->__srcAddr_1;
    pif_expression__condition_39_register_2 = ethernet->srcAddr;
    pif_expression__condition_39_register_3 = 0x3ec6a2aa;
    pif_expression__condition_39_register_4 = 0x16;
    /* implicit cast 37 -> 48 */
    pif_expression__condition_39_register_5 = pif_expression__condition_39_register_3;
    pif_expression__condition_39_register_6 = pif_expression__condition_39_register_4 & 0x1f;
    pif_expression__condition_39_register_0 = (pif_expression__condition_39_register_1 == pif_expression__condition_39_register_5) && (pif_expression__condition_39_register_2 == pif_expression__condition_39_register_6);
    }

    if (pif_expression__condition_39_register_0)
        return PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_26;
    else
        return PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_27;
}

static int handle_egress_flow_egress__tbl_act_26(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow_egress__tbl_act_26");
#endif

    {
        struct pif_action_actiondata_egress__act_25 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_egress__act_25 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_egress__act_25 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_27; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_egress_flow__condition_37(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_37_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow__condition_37");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_37: ((data.epc_traffic_code) == (17))
    {
    unsigned int pif_expression__condition_37_register_1;
    unsigned int pif_expression__condition_37_register_2;
    unsigned int pif_expression__condition_37_register_3;
    //subexpression 2: 17
    // constant : 0x11

    //subexpression 0: (data.epc_traffic_code)==(17)
    pif_expression__condition_37_register_1 = data->epc_traffic_code;
    pif_expression__condition_37_register_2 = 0x11;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_37_register_3 = pif_expression__condition_37_register_2 & 0x1f;
    pif_expression__condition_37_register_0 = (pif_expression__condition_37_register_1 == pif_expression__condition_37_register_3);
    }

    if (pif_expression__condition_37_register_0)
        return PIF_CTLFLOW_STATE_egress_flow_egress__ctxt_release_uekey_sgwteid_map;
    else
        return PIF_CTLFLOW_STATE_egress_flow__condition_38;
}

static int handle_egress_flow_egress__ctxt_release_uekey_sgwteid_map(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow_egress__ctxt_release_uekey_sgwteid_map");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_egress__ctxt_release_uekey_sgwteid_map, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_egress_flow_exit_control_flow; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_egress_flow__condition_36(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_36_register_0;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow__condition_36");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_36: ((ethernet.srcAddr) == (95542485674))
    {
    unsigned int pif_expression__condition_36_register_1;
    unsigned int pif_expression__condition_36_register_2;
    unsigned int pif_expression__condition_36_register_3;
    unsigned int pif_expression__condition_36_register_4;
    unsigned int pif_expression__condition_36_register_5;
    unsigned int pif_expression__condition_36_register_6;
    //subexpression 2: 95542485674
    // constant : 0x163ec6a2aa

    //subexpression 0: (ethernet.srcAddr)==(95542485674)
    pif_expression__condition_36_register_1 = ethernet->__srcAddr_1;
    pif_expression__condition_36_register_2 = ethernet->srcAddr;
    pif_expression__condition_36_register_3 = 0x3ec6a2aa;
    pif_expression__condition_36_register_4 = 0x16;
    /* implicit cast 37 -> 48 */
    pif_expression__condition_36_register_5 = pif_expression__condition_36_register_3;
    pif_expression__condition_36_register_6 = pif_expression__condition_36_register_4 & 0x1f;
    pif_expression__condition_36_register_0 = (pif_expression__condition_36_register_1 == pif_expression__condition_36_register_5) && (pif_expression__condition_36_register_2 == pif_expression__condition_36_register_6);
    }

    if (pif_expression__condition_36_register_0)
        return PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_23;
    else
        return PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_24;
}

static int handle_egress_flow_egress__tbl_act_23(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow_egress__tbl_act_23");
#endif

    {
        struct pif_action_actiondata_egress__act_22 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_egress__act_22 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_egress__act_22 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_24; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_egress_flow__condition_34(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_34_register_0;
    __lmem struct pif_header_standard_metadata *standard_metadata;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow__condition_34");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);

    //expression _condition_34: ((standard_metadata.instance_type) == (8))
    {
    unsigned int pif_expression__condition_34_register_1;
    unsigned int pif_expression__condition_34_register_2;
    //subexpression 2: 8
    // constant : 0x8

    //subexpression 0: (standard_metadata.instance_type)==(8)
    pif_expression__condition_34_register_1 = standard_metadata->instance_type;
    pif_expression__condition_34_register_2 = 0x8;
    pif_expression__condition_34_register_0 = (pif_expression__condition_34_register_1 == pif_expression__condition_34_register_2);
    }

    if (pif_expression__condition_34_register_0)
        return PIF_CTLFLOW_STATE_egress_flow__condition_35;
    else
        return PIF_CTLFLOW_STATE_egress_flow_exit_control_flow;
}

static int handle_egress_flow__condition_38(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_38_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow__condition_38");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_38: ((data.epc_traffic_code) == (19))
    {
    unsigned int pif_expression__condition_38_register_1;
    unsigned int pif_expression__condition_38_register_2;
    unsigned int pif_expression__condition_38_register_3;
    //subexpression 2: 19
    // constant : 0x13

    //subexpression 0: (data.epc_traffic_code)==(19)
    pif_expression__condition_38_register_1 = data->epc_traffic_code;
    pif_expression__condition_38_register_2 = 0x13;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_38_register_3 = pif_expression__condition_38_register_2 & 0x1f;
    pif_expression__condition_38_register_0 = (pif_expression__condition_38_register_1 == pif_expression__condition_38_register_3);
    }

    if (pif_expression__condition_38_register_0)
        return PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_25;
    else
        return PIF_CTLFLOW_STATE_egress_flow_exit_control_flow;
}

static int handle_egress_flow__condition_35(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_35_register_0;
    __lmem struct pif_header_data *data;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow__condition_35");
#endif

    data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);

    //expression _condition_35: ((data.epc_traffic_code) == (14))
    {
    unsigned int pif_expression__condition_35_register_1;
    unsigned int pif_expression__condition_35_register_2;
    unsigned int pif_expression__condition_35_register_3;
    //subexpression 2: 14
    // constant : 0xe

    //subexpression 0: (data.epc_traffic_code)==(14)
    pif_expression__condition_35_register_1 = data->epc_traffic_code;
    pif_expression__condition_35_register_2 = 0xe;
    /* implicit cast 4 -> 8 */
    pif_expression__condition_35_register_3 = pif_expression__condition_35_register_2 & 0xf;
    pif_expression__condition_35_register_0 = (pif_expression__condition_35_register_1 == pif_expression__condition_35_register_3);
    }

    if (pif_expression__condition_35_register_0)
        return PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_22;
    else
        return PIF_CTLFLOW_STATE_egress_flow__condition_37;
}

static int handle_egress_flow_egress__tbl_act_22(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow_egress__tbl_act_22");
#endif

    {
        struct pif_action_actiondata_egress__act_23 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_egress__act_23 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_egress__act_23 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_egress_flow__condition_36; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_egress_flow_egress__tbl_act_27(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow_egress__tbl_act_27");
#endif

    {
        struct pif_action_actiondata_egress__act_27 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_egress__act_27 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_egress__act_27 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_egress_flow_exit_control_flow; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_egress_flow_egress__tbl_act_24(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow_egress__tbl_act_24");
#endif

    {
        struct pif_action_actiondata_egress__act_24 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_egress__act_24 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_egress__act_24 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_egress_flow_exit_control_flow; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_egress_flow_egress__tbl_act_25(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_egress_flow_egress__tbl_act_25");
#endif

    {
        struct pif_action_actiondata_egress__act_26 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_egress__act_26 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_egress__act_26 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_egress_flow__condition_39; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_egress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

/* Control flow entry point */

int pif_ctlflow_egress_flow(int *start_state, __lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off)
{
    __gpr int actlen, totlen = 0;
    __gpr int ret;
    int pif_ctlflow_state_egress_flow = PIF_CTLFLOW_STATE_egress_flow__condition_34;

    while (pif_ctlflow_state_egress_flow != PIF_CTLFLOW_STATE_egress_flow_DONE) {
        PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_CONTROL, ((1 << 16) + pif_ctlflow_state_egress_flow));
#ifdef PIF_DEBUG
        __debug_label("pif_ctlflow_state_egress_flow");
#endif
        switch (pif_ctlflow_state_egress_flow) {
        case PIF_CTLFLOW_STATE_egress_flow__condition_39:
            pif_ctlflow_state_egress_flow = handle_egress_flow__condition_39(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_26:
            ret = handle_egress_flow_egress__tbl_act_26(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_egress_flow);
            break;
        case PIF_CTLFLOW_STATE_egress_flow__condition_37:
            pif_ctlflow_state_egress_flow = handle_egress_flow__condition_37(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_egress_flow_egress__ctxt_release_uekey_sgwteid_map:
            ret = handle_egress_flow_egress__ctxt_release_uekey_sgwteid_map(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_egress_flow);
            break;
        case PIF_CTLFLOW_STATE_egress_flow__condition_36:
            pif_ctlflow_state_egress_flow = handle_egress_flow__condition_36(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_23:
            ret = handle_egress_flow_egress__tbl_act_23(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_egress_flow);
            break;
        case PIF_CTLFLOW_STATE_egress_flow__condition_34:
            pif_ctlflow_state_egress_flow = handle_egress_flow__condition_34(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_egress_flow__condition_38:
            pif_ctlflow_state_egress_flow = handle_egress_flow__condition_38(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_egress_flow__condition_35:
            pif_ctlflow_state_egress_flow = handle_egress_flow__condition_35(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_22:
            ret = handle_egress_flow_egress__tbl_act_22(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_egress_flow);
            break;
        case PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_27:
            ret = handle_egress_flow_egress__tbl_act_27(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_egress_flow);
            break;
        case PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_24:
            ret = handle_egress_flow_egress__tbl_act_24(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_egress_flow);
            break;
        case PIF_CTLFLOW_STATE_egress_flow_egress__tbl_act_25:
            ret = handle_egress_flow_egress__tbl_act_25(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_egress_flow);
            break;
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
