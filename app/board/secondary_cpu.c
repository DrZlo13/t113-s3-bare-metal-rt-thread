#include <rtthread.h>

#ifdef RT_USING_SMP

#include <stdint.h>
#include <rthw.h>
#include "board.h"
#include <gic.h>
#include <interrupt.h>
#include "../lib/log.h"

#define readl(addr) (*(volatile unsigned int*)(addr))
#define writel(value, addr) (*(volatile unsigned int*)(addr) = (value))

extern void sys_uart_putc(char c);
extern void secondary_cpu_start(void);

/*
The Soft Entry Address Register of CPU0 is 0x070005C4.
The Soft Entry Address Register of CPU1 is 0x070005C8.
*/
void rt_hw_secondary_cpu_up(void) {
    uint32_t cpuboot_membase = 0x070005c4;
    uint32_t cpuxcfg_membase = 0x09010000;
    uint32_t cpu, reg;

    cpu = 1;
    /* Set CPU boot address */
    writel((uint32_t)(secondary_cpu_start), cpuboot_membase + 4 * cpu);

    /* Deassert the CPU core in reset */
    reg = readl(cpuxcfg_membase);
    writel(reg | (1 << cpu), cpuxcfg_membase);

    __asm__ volatile("isb" ::: "memory");
}

void secondary_cpu_c_start(void) {
    rt_hw_vector_init();
    rt_hw_spin_lock(&_cpus_lock);
    arm_gic_cpu_init(0, platform_get_gic_cpu_base());
    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void) {
    asm volatile("wfe" ::: "memory", "cc");
}

#endif /* RT_USING_SMP*/
