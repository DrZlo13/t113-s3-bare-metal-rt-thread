#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LogLevelError = 0,
    LogLevelInfo = 1,
    LogLevelDebug = 2,
} LogLevel;

void log_init(void);

void log_print_format(LogLevel level, const char* tag, const char* format, ...)
    __attribute__((__format__(__printf__, 3, 4)));

#define log_error(tag, format, ...) log_print_format(LogLevelError, tag, format, ##__VA_ARGS__)
#define log_info(tag, format, ...) log_print_format(LogLevelInfo, tag, format, ##__VA_ARGS__)
#define log_debug(tag, format, ...) log_print_format(LogLevelDebug, tag, format, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif