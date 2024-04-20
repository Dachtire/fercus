/*
 * Copyright (c) 2022 zerosensei
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SUBSYS_KEY_TASK_KEY_TASK_H
#define SUBSYS_KEY_TASK_KEY_TASK_H

//#include "soc.h"
//#include "keyscan.h"
#include <stdint.h>

/*task event*/
#define KEYBOARD_SCAN_EVENT         (1<<0)
#define KEY_SCAN_SHORT_TO_EVENT     (1<<1)
#define KEY_SCAN_LONG_TO_EVENT      (1<<2)
#define KEYBOARD_FN_SCAN_EVENT (1<<3)
#define KEYBOARD_JS_SCAN_EVENT (1<<4)

#define KEYBOARD_SCAN_EVENT_INTERVAL MS1_TO_SYSTEM_TIME(1)

int key_deal(void);
void tmos_keyboard_init(void);
void tmos_keyboard_deinit();

extern uint8_t tmos_keyboard_task_id;

#endif /* SUBSYS_KEY_TASK_KEY_TASK_H */