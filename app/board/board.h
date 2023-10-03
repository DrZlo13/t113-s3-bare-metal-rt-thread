/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard    the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#define MAX_HANDLERS 223
#define GIC_ACK_INTID_MASK 0x000003ff
#define GIC_IRQ_START 0

/* number of interrupts on board */
#define ARM_GIC_NR_IRQS MAX_HANDLERS
/* only one GIC available */
#define ARM_GIC_MAX_NR 1

#define __REG32(x) (*((volatile unsigned int*)(x)))
#define __REG16(x) (*((volatile unsigned short*)(x)))

/* the basic constants and interfaces needed by gic */
rt_inline rt_uint32_t platform_get_gic_dist_base(void) {
    return 0x03021000;
}

rt_inline rt_uint32_t platform_get_gic_cpu_base(void) {
    return 0x03022000;
}

extern int __bss_end;
#define HEAP_BEGIN ((void*)&__bss_end)
#define HEAP_END (void*)(0x40000000 + 128 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
