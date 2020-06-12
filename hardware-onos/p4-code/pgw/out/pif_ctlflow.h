/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_CTLFLOW_H__
#define __PIF_CTLFLOW_H__

/* Defines for checking flow presence */
#define PIF_CTLFLOW_HAS_ingress_flow

#define PIF_CTLFLOW_STATE_ingress 0
#define PIF_CTLFLOW_STATE_accept 0
/* Control state nodes for ingress_flow */
#define PIF_CTLFLOW_STATE_ingress_flow_DONE -1
#define PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow -1
#define PIF_CTLFLOW_STATE_ingress_flow 0

#define PIF_CTLFLOW_STATE_ingress_flow__condition_8 0
#define PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s1_uplink 1
#define PIF_CTLFLOW_STATE_ingress_flow__condition_4 2
#define PIF_CTLFLOW_STATE_ingress_flow__condition_5 3
#define PIF_CTLFLOW_STATE_ingress_flow__condition_7 4
#define PIF_CTLFLOW_STATE_ingress_flow__condition_6 5
#define PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_1 6
#define PIF_CTLFLOW_STATE_ingress_flow__condition_1 7
#define PIF_CTLFLOW_STATE_ingress_flow__condition_2 8
#define PIF_CTLFLOW_STATE_ingress_flow__condition_0 9
#define PIF_CTLFLOW_STATE_ingress_flow_ingress__arp_tbl 10
#define PIF_CTLFLOW_STATE_ingress_flow_ingress__tun_egress_s3_uplink 11
#define PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_2 12
#define PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_0 13
#define PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act 14
#define PIF_CTLFLOW_STATE_ingress_flow__condition_3 15

/* Unified control state numbers */
#define PIF_CTLFLOW_STATE__condition_8 0
#define PIF_CTLFLOW_STATE_ingress__ip_op_tun_s1_uplink 1
#define PIF_CTLFLOW_STATE__condition_4 2
#define PIF_CTLFLOW_STATE__condition_5 3
#define PIF_CTLFLOW_STATE__condition_7 4
#define PIF_CTLFLOW_STATE__condition_6 5
#define PIF_CTLFLOW_STATE_ingress__tbl_act_1 6
#define PIF_CTLFLOW_STATE__condition_1 7
#define PIF_CTLFLOW_STATE__condition_2 8
#define PIF_CTLFLOW_STATE__condition_0 9
#define PIF_CTLFLOW_STATE_ingress__arp_tbl 10
#define PIF_CTLFLOW_STATE_ingress__tun_egress_s3_uplink 11
#define PIF_CTLFLOW_STATE_ingress__tbl_act_2 12
#define PIF_CTLFLOW_STATE_ingress__tbl_act_0 13
#define PIF_CTLFLOW_STATE_ingress__tbl_act 14
#define PIF_CTLFLOW_STATE__condition_3 15

/* Control flow entry points  */
int pif_ctlflow_ingress_flow(int *start_state, __lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off);
int pif_ctlflow_egress_flow(int *start_state, __lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off);

#endif /* __PIF_CTLFLOW_H__ */
