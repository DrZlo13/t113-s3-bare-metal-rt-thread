/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 * 2018-11-22     Jesven     add rt_hw_spin_lock
 *                           add rt_hw_spin_unlock
 *                           add smp ipi init
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
// #include "drv_timer.h"

#include <mmu.h>
#include <gic.h>

// 0x02500000
struct mem_desc platform_mem_desc[] = {
    {0x00000000, 0xFFFFFFFF, 0x00000000, DEVICE_MEM},
    {0x00000000, 0x000FFFFF, 0x00000000, NORMAL_MEM},
    {0x40000000, 0x47FFFFFF, 0x40000000, NORMAL_MEM},
};

const rt_uint32_t platform_mem_desc_size =
    sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);

extern void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);

void idle_wfi(void) {
    asm volatile("wfi");
}

#include <hal/timer.h>
#include <hal/interrupt.h>

static void os_clock_irq_handle(int irqno, void* param) {
    hal_timer0_interrupt_clear(TIMER);
    // rt_kprintf("os_clock_irq_handle\n");
    rt_tick_increase();
}

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init(void) {
    /* initialize hardware interrupt */
    rt_hw_interrupt_init();
    /* initialize system heap */
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
#endif

    int timer_irq_number = InterruptTimer0;
    arm_gic_set_cpu(0, timer_irq_number, 0x1);

    hal_timer0_init(TIMER, 1000);
    rt_hw_interrupt_install(timer_irq_number, os_clock_irq_handle, RT_NULL, "tick1");
    rt_hw_interrupt_umask(timer_irq_number);
    hal_timer0_interrupt_enable(TIMER);
}
