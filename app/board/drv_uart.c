/*
 * COPYRIGHT (C) 2012-2020, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "drv_uart.h"
#include "interrupt.h"

#include <hal/clock.h>
#include <hal/gpio.h>
#include <hal/uart.h>
#include <hal/interrupt.h>

struct device_uart {
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
    char name[RT_NAME_MAX];
    rt_uint32_t gpio_rx_port;
    rt_uint32_t gpio_tx_port;
    rt_uint32_t gpio_rx_pin;
    rt_uint32_t gpio_tx_pin;
    rt_uint32_t gpio_rx_fun;
    rt_uint32_t gpio_tx_fun;
};

static rt_err_t uart_configure(struct rt_serial_device* serial, struct serial_configure* cfg);
static rt_err_t uart_control(struct rt_serial_device* serial, int cmd, void* arg);
static int uart_putc(struct rt_serial_device* serial, char c);
static int uart_getc(struct rt_serial_device* serial);
static rt_size_t uart_dma_transmit(
    struct rt_serial_device* serial,
    rt_uint8_t* buf,
    rt_size_t size,
    int direction);

void uart_irq_handler(int irqno, void* param);

void sys_uart_init(void) {
#define GPIO_UART_TX GPIOE, 2
#define GPIO_UART_RX GPIOE, 3

    hal_clock_enable(ClockSystemUart0);
    hal_gpio_set_config(GPIO_UART_TX, GpioConfigFunction6);
    hal_gpio_set_config(GPIO_UART_RX, GpioConfigFunction6);
    hal_gpio_pull(GPIO_UART_TX, GpioPullUp);
    hal_gpio_pull(GPIO_UART_RX, GpioPullUp);
    hal_uart_config(UART0, 115200, UartParityNone, UartStopBit1, UartDataLen8);
}

/*
 * UART interface
 */
static rt_err_t uart_configure(struct rt_serial_device* serial, struct serial_configure* cfg) {
    struct device_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    serial->config = *cfg;

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    sys_uart_init();

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device* serial, int cmd, void* arg) {
    struct device_uart* uart = serial->parent.user_data;
    UART_TypeDef* uart_base = (UART_TypeDef*)uart->hw_base;

    RT_ASSERT(uart != RT_NULL);

    switch(cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        rt_hw_interrupt_mask(uart->irqno);
        hal_uart_disable_interrupt(uart_base);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* install interrupt */
        rt_hw_interrupt_install(uart->irqno, uart_irq_handler, serial, uart->name);
        rt_hw_interrupt_umask(uart->irqno);
        /* Enable the UART Interrupt */
        hal_uart_enable_interrupt(uart_base);
        break;
    }

    return (RT_EOK);
}

static int uart_putc(struct rt_serial_device* serial, char c) {
    struct device_uart* uart = serial->parent.user_data;
    UART_TypeDef* uart_base = (UART_TypeDef*)uart->hw_base;
    hal_uart_put_byte(uart_base, c);
    return (1);
}

static int uart_getc(struct rt_serial_device* serial) {
    int ch = -1;
    struct device_uart* uart = serial->parent.user_data;
    UART_TypeDef* uart_base = (UART_TypeDef*)uart->hw_base;

    RT_ASSERT(serial != RT_NULL);

    uint8_t byte = 0;
    if(hal_uart_get_byte(uart_base, &byte)) {
        ch = byte;
    }

    return ch;
}

static rt_size_t uart_dma_transmit(
    struct rt_serial_device* serial,
    rt_uint8_t* buf,
    rt_size_t size,
    int direction) {
    return (0);
}

/* UART ISR */
void uart_irq_handler(int irqno, void* param) {
    struct rt_serial_device* serial = (struct rt_serial_device*)param;
    struct device_uart* uart = serial->parent.user_data;
    UART_TypeDef* uart_base = (UART_TypeDef*)uart->hw_base;

    uint8_t intr = hal_uart_read_and_clear_int(uart_base);

    if(intr == UartInterruptReceiverDataAvailable) /* rx ind */
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if(0) /* tx done */
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }
}

static const struct rt_uart_ops _uart_ops = {
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
    uart_dma_transmit,
};

/*
 * UART Initiation
 */
#ifdef RT_USING_UART0
rt_err_t rt_hw_uart0_init(void) {
    static struct rt_serial_device serial0;
    static struct device_uart uart0;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    serial0.ops = &_uart_ops;
    serial0.config = config;
    serial0.config.baud_rate = 115200;

    uart0.hw_base = (rt_uint32_t)UART0;
    uart0.irqno = InterruptUART0;

    return rt_hw_serial_register(
        &serial0, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &uart0);
}
#endif /* RT_USING_UART0 */

int rt_hw_uart_init(void) {
#ifdef RT_USING_UART0
    rt_hw_uart0_init();
#endif /* RT_USING_UART0 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
