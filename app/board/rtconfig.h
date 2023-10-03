#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Project Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_USING_SMP
#define RT_CPUS_NR 2
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 1024
#define SYSTEM_THREAD_STACK_SIZE 1024
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 1024

/* kservice optimization */

#define RT_DEBUG
#define RT_DEBUG_COLOR

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
#define RT_USING_SIGNALS

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_MEMHEAP
#define RT_MEMHEAP_FAST_MODE
#define RT_USING_MEMHEAP_AS_HEAP
#define RT_USING_MEMHEAP_AUTO_BINDING
#define RT_USING_MEMTRACE
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_DEVICE_OPS
#define RT_USING_INTERRUPT_INFO
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 256
#define RT_CONSOLE_DEVICE_NAME "uart0"
#define RT_VER_NUM 0x40100
#define ARCH_ARM
#define RT_USING_CPU_FFS
#define ARCH_ARM_CORTEX_A
#define RT_USING_GIC_V2
#define ARCH_ARM_CORTEX_A7

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 80
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10
#define RT_USING_DFS
#define DFS_USING_POSIX
#define DFS_USING_WORKDIR
#define DFS_FILESYSTEMS_MAX 4
#define DFS_FILESYSTEM_TYPES_MAX 8
#define DFS_FD_MAX 32
#define RT_USING_DFS_DEVFS

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 2048
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V1
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_RTC
#define RT_USING_SOFT_RTC

/* Using USB */

/* C/C++ and POSIX layer */

#define RT_LIBC_DEFAULT_TIMEZONE 8

/* POSIX (Portable Operating System Interface) layer */

// #define RT_USING_POSIX_FS
// #define RT_USING_POSIX_DEVIO
// #define RT_USING_POSIX_STDIO
// #define RT_USING_POSIX_POLL
// #define RT_USING_POSIX_SELECT
// #define RT_USING_POSIX_SOCKET
// #define RT_USING_POSIX_TERMIOS
// #define RT_USING_POSIX_AIO
// #define RT_USING_POSIX_DELAY
// #define RT_USING_POSIX_CLOCK
// #define RT_USING_PTHREADS
#define PTHREAD_NUM_MAX 8

/* Interprocess Communication (IPC) */

#define RT_USING_POSIX_MESSAGE_QUEUE
#define RT_USING_POSIX_MESSAGE_SEMAPHORE

/* Socket is in the 'Network' category */

#define RT_USING_CPLUSPLUS

/* Network */

#define RT_USING_SAL
#define SAL_INTERNET_CHECK
#define SAL_USING_POSIX
#define RT_USING_NETDEV
#define NETDEV_USING_IFCONFIG
#define NETDEV_USING_PING
#define NETDEV_USING_NETSTAT
#define NETDEV_USING_AUTO_DEFAULT
#define NETDEV_IPV4 1
#define NETDEV_IPV6 0

/* Utilities */

/* RT-Thread Utestcases */

/* RT-Thread online packages */

/* IoT - internet of things */

/* Wi-Fi */

/* Marvell WiFi */

/* Wiced WiFi */

/* IoT Cloud */

/* security packages */

/* language packages */

/* multimedia packages */

/* LVGL: powerful and easy-to-use embedded GUI library */

/* u8g2: a monochrome graphic library */

/* tools packages */

/* system packages */

/* acceleration: Assembly language or algorithmic acceleration packages */

/* Micrium: Micrium software products porting for RT-Thread */

/* peripheral libraries and drivers */

/* AI packages */

/* miscellaneous packages */

/* samples: kernel and components samples */

/* entertainment: terminal games and other interesting software packages */

/* Hardware Drivers Config */

#define SOC_ALLWINNER_T113

/* Onboard Peripheral Drivers */

#define RT_USING_UART0

#endif
