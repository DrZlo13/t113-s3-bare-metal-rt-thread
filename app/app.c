/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/31     Bernard      Add license info
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <rtthread.h>
#include <rthw.h>

static rt_mutex_t mutex;

void thread(void* arg) {
    int count = 0;
    int thread_num = (int)arg;

    while(1) {
        int cpu_id = rt_hw_cpu_id();
        rt_mutex_take(mutex, RT_WAITING_FOREVER);
        rt_kprintf("Thread %d #%d %d\n", thread_num, count++, cpu_id);
        rt_mutex_release(mutex);
        rt_thread_delay(1);
    }
}

int main(void) {
    rt_kprintf("Hello RT-Thread! [%s %s]\n", __DATE__, __TIME__);

    mutex = rt_mutex_create("mutex", RT_IPC_FLAG_FIFO);

    const size_t thread_num = 10;
    rt_thread_t threads[thread_num];

    for(size_t i = 0; i < thread_num; i++) {
        threads[i] = rt_thread_create("remote", thread, (void*)(i), 512, 20, 20);
        rt_thread_startup(threads[i]);
    }

    return 0;
}
