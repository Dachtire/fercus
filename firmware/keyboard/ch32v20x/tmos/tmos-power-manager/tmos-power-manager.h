/*
 * Copyright (c) 2022 zerosensei
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SUBSYS_PM_PM_TASK_H
#define SUBSYS_PM_PM_TASK_H

//#include "soc.h"
#include "config.h"

enum pm_state{
  PM_STATE_ACTIVE,
  PM_STATE_SLEEP,
  PM_STATE_SHUT,

  PM_STATE_NUM
};

/* task events */
#define PM_ENTER_IDLE_EVENT           (1<<1)
#define PM_ENTER_STANDBY_EVENT        (1<<2)

#define PM_TIMEOUT_FOREVER              (-1)
#define PM_WORKING_TIMEOUT              (1000*60*5)//1min
#define PM_IDLE_TIMEOUT                 PM_TIMEOUT_FOREVER

void pm_task_init(void);
u8 pm_is_in_idle(void);
void pm_start_working(int working_timeout, int idle_timeout);
void pm_goto_standby(void);

extern uint8_t tmos_pm_id;
void tmos_power_manager_init();
void power_manager_enter_standby();
void power_manager_exit_standby();

#endif /* SUBSYS_PM_PM_TASK_H */
