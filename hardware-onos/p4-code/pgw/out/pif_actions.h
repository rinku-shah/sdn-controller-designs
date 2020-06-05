/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_ACTIONS_H__
#define __PIF_ACTIONS_H__

/* Warning: generated file - your edits to this file may be lost */

/* Action operation IDs */

#define PIF_ACTION_ID_ingress__fwd_act 0
#define PIF_ACTION_ID_ingress__drop_act 1
#define PIF_ACTION_ID_ingress__act 2
#define PIF_ACTION_ID_ingress__populate_tun_egress_s3_uplink 3
#define PIF_ACTION_ID_ingress__act_0 4
#define PIF_ACTION_ID_ingress__act_1 5
#define PIF_ACTION_ID_ingress__act_2 6
#define PIF_ACTION_ID_ingress__populate_ip_op_tun_s1_uplink 7
#define PIF_ACTION_ID_MAX 7

/* Match action data structure */

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
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint8_t __pif_padding[2]; /* padding */
    uint16_t egress_port_s3;
};

__packed struct pif_action_actiondata_ingress__act_0 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_1 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_2 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__populate_ip_op_tun_s1_uplink {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint8_t __pif_padding[2]; /* padding */
    uint16_t egress_port_s1;
};

#endif /* __PIF_ACTIONS_H__ */
