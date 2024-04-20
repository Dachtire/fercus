/*
 * Copyright (c) 2022 Nanjing Qinheng Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SUBSYS_MODE_MODE_H
#define SUBSYS_MODE_MODE_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* EVENTS */
#define CONNCETION_MODE_SELECT_EVENT (1<<0)

void tmos_connection_mode_init(void);
void tmos_connection_mode_select(uint8_t mod);

#define CONN_BLE                         0x11
#define CONN_USB                         0x6b
#define CONN_TMOS_USB                    0x6c
#define CONN_TMOS_USBFS                    0x6d
#define CONN_RF                          0x24
#define CONN_TSET                        0x84

static uint8_t connection_mode;
void connection_mode_init(uint8_t connection);

#ifdef __cplusplus
}
#endif

#endif /* SUBSYS_MODE_MODE_H */