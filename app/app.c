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
#include "lib/log.h"

#include <hal/clock.h>
#include <hal/gpio.h>
#include <hal/pwm.h>

void app_init() {
    log_init();
}

static void thread(void* arg) {
    int count = 0;
    int thread_num = (int)arg;

    while(1) {
        log_info("thread", "Thread %d #%d", thread_num, count++);
        rt_thread_mdelay(10000);
    }
}

#define GPIO_PWM GPIOD, 22
#define PWM_CHANNEL 7

static void pwm_set(uint16_t duty) {
    hal_pwm_duty(PWM_CHANNEL, duty);
    rt_thread_mdelay(10);
}

static void pwm_thread(void* arg) {
    hal_gpio_set_config(GPIO_PWM, GpioConfigFunction5);
    hal_clock_enable(ClockSystemPWM);
    hal_pwm_clock(PWM_CHANNEL, PWMClockDiv256, PWMClockSourceHOSC, 0);
    hal_pwm_mode(PWM_CHANNEL, PWMModeCycle, PWMActiveLow);
    hal_pwm_period(PWM_CHANNEL, 1000);
    hal_pwm_duty(PWM_CHANNEL, 0);
    hal_pwm_enable(PWM_CHANNEL);

    while(1) {
        for(uint16_t i = 0; i < 1000; i += 10) {
            pwm_set(i);
        }
        for(uint16_t i = 1000; i > 0; i -= 10) {
            pwm_set(i);
        }
    }
}

void hal_assert_handler(const char* expr, const char* func, size_t line) {
    log_error(
        "hal", "Assertion failed: %s, function %s, file %s, line %d.", expr, func, __FILE__, line);
    while(1) {
        asm volatile("bkpt 0");
    }
}

int main(void) {
    log_info("main", "Hello RT-Thread! [%s %s]", __DATE__, __TIME__);

    const size_t thread_num = 10;
    rt_thread_t threads[thread_num];
    UNUSED(threads);

    for(size_t i = 0; i < thread_num; i++) {
        threads[i] = rt_thread_create("remote", thread, (void*)(i), 512, 20, 20);
        // rt_thread_startup(threads[i]);
    }

    rt_thread_t pwm_thread_handle = rt_thread_create("pwm", pwm_thread, NULL, 512, 20, 20);
    rt_thread_startup(pwm_thread_handle);

    return 0;
}
