#include "log.h"
#include <rtthread.h>
#include <rthw.h>

#define LOG_CLR(clr) "\033[0;" clr "m"
#define LOG_CLR_RESET "\033[0m"

#define LOG_CLR_RED "31"
#define LOG_CLR_GREEN "32"
#define LOG_CLR_BLUE "34"

#define LOG_CLR_E LOG_CLR(LOG_CLR_RED)
#define LOG_CLR_I LOG_CLR(LOG_CLR_GREEN)
#define LOG_CLR_D LOG_CLR(LOG_CLR_BLUE)

static struct rt_mutex mutex;

void log_init() {
    rt_mutex_init(&mutex, "mutex", RT_IPC_FLAG_FIFO);
}

static int rt_kvprintf(const char* fmt, va_list args) {
    rt_size_t length;
    static char rt_log_buf[RT_CONSOLEBUF_SIZE];

    length = rt_vsnprintf(rt_log_buf, sizeof(rt_log_buf) - 1, fmt, args);
    if(length > RT_CONSOLEBUF_SIZE - 1) length = RT_CONSOLEBUF_SIZE - 1;
    rt_log_buf[length] = '\0';
    rt_kprintf("%s", rt_log_buf);

    return length;
}

void log_print_format(LogLevel level, const char* tag, const char* format, ...) {
    rt_mutex_take(&mutex, RT_WAITING_FOREVER);
    const char* color = LOG_CLR_RESET;
    const char* log_letter = " ";

    switch(level) {
    case LogLevelError:
        color = LOG_CLR_E;
        log_letter = "E";
        break;
    case LogLevelInfo:
        color = LOG_CLR_I;
        log_letter = "I";
        break;
    case LogLevelDebug:
        color = LOG_CLR_D;
        log_letter = "D";
        break;
    }

    uint32_t timestamp = rt_tick_get();
    uint32_t cpu_id = rt_hw_cpu_id();
    rt_kprintf("%lu %lu %s[%s][%s]" LOG_CLR_RESET " ", timestamp, cpu_id, color, log_letter, tag);

    va_list args;
    va_start(args, format);
    rt_kvprintf(format, args);
    va_end(args);

    rt_kprintf("\r\n");

    rt_mutex_release(&mutex);
}
