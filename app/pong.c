#include <rtthread.h>

int pong(void) {
    rt_kprintf("Ping\n");
    rt_thread_delay(100);
    rt_kprintf("Pong\n");
    rt_thread_delay(100);

    return 0;
}
MSH_CMD_EXPORT(pong, "test pong");