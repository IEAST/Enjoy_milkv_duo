/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/25     flyingcys    first version
 */

#include <rtthread.h>
#include <stdio.h>
#include "led.h"

int main(void)
{
    rt_kprintf("Hello RT-Smart!\n");
    led_init();
	rt_thread_mdelay(5000);
	rt_kprintf("led on\n");
	led_on();
	rt_thread_mdelay(5000);
	rt_kprintf("led off\n");
	led_off();
	rt_thread_mdelay(5000);
	led_on();
    return 0;
}