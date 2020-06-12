/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_ACTIONS_H__
#define __PIF_ACTIONS_H__

/* Warning: generated file - your edits to this file may be lost */

/* Action operation IDs */

#define PIF_ACTION_ID_ingress__act_8 0
#define PIF_ACTION_ID_ingress__fwd_act 1
#define PIF_ACTION_ID_ingress__drop_act 2
#define PIF_ACTION_ID_ingress__act 3
#define PIF_ACTION_ID_ingress__populate_tun_egress_s3_uplink 4
#define PIF_ACTION_ID_ingress__act_9 5
#define PIF_ACTION_ID_ingress__act_0 6
#define PIF_ACTION_ID_ingress__act_1 7
#define PIF_ACTION_ID_ingress__act_10 8
#define PIF_ACTION_ID_ingress__act_11 9
#define PIF_ACTION_ID_ingress__act_4 10
#define PIF_ACTION_ID_ingress__act_5 11
#define PIF_ACTION_ID_ingress__act_6 12
#define PIF_ACTION_ID_ingress__act_7 13
#define PIF_ACTION_ID_ingress__act_3 14
#define PIF_ACTION_ID_ingress__populate_ip_op_tun_s1_uplink 15
#define PIF_ACTION_ID_ingress__act_2 16
#define PIF_ACTION_ID_MAX 16

/* Match action data structure */

__packed struct pif_action_actiondata_ingress__act_8 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__fwd_act {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint8_t __pif_padding[2]; /* padding */
    uint16_t prt;
};

__packed struct pif_action_actiondata_ingress__drop_act {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__populate_tun_egress_s3_uplink {
    uint32_t egress_port_s3;
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_9 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_0 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_1 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_10 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_11 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_4 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_5 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_6 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_7 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_3 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__populate_ip_op_tun_s1_uplink {
    uint32_t egress_port_s1;
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_2 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

#endif /* __PIF_ACTIONS_H__ */
