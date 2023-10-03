cmake_minimum_required(VERSION 3.9)

project("rt-thread")

set(RT_THREAD "${CMAKE_CURRENT_SOURCE_DIR}/../rt-thread")

set(INCLUDES
    ${RT_THREAD}/include
    ${RT_THREAD}/libcpu/arm/common
    ${RT_THREAD}/libcpu/arm/cortex-a
    ${RT_THREAD}/components/libc/posix/io/termios
    ${RT_THREAD}/components/libc/posix/io/aio
    ${RT_THREAD}/components/libc/posix/io/stdio
    ${RT_THREAD}/components/libc/posix/io/poll
    ${RT_THREAD}/components/libc/posix/pthreads
    ${RT_THREAD}/components/libc/posix/ipc
    ${RT_THREAD}/components/libc/posix/delay
    ${RT_THREAD}/components/libc/posix/signal
    ${RT_THREAD}/components/libc/cplusplus
    ${RT_THREAD}/components/libc/compilers/newlib
    ${RT_THREAD}/components/libc/compilers/common
    ${RT_THREAD}/components/libc/compilers/common/include
    ${RT_THREAD}/components/net/sal/include
    ${RT_THREAD}/components/net/sal/include/socket
    ${RT_THREAD}/components/net/sal/include/dfs_net
    ${RT_THREAD}/components/net/sal/include/socket/sys_socket
    ${RT_THREAD}/components/net/netdev/include
    ${RT_THREAD}/components/drivers/include
    ${RT_THREAD}/components/dfs/include
    ${RT_THREAD}/components/dfs/filesystems/devfs
    ${RT_THREAD}/components/finsh
)

include_directories(
    ${INCLUDES}
)

file(GLOB_RECURSE SOURCES
    ${RT_THREAD}/components/dfs/filesystems/devfs/devfs.c
    ${RT_THREAD}/components/dfs/src/dfs.c
    ${RT_THREAD}/components/dfs/src/dfs_file.c
    ${RT_THREAD}/components/dfs/src/dfs_fs.c
    ${RT_THREAD}/components/dfs/src/dfs_posix.c
    ${RT_THREAD}/components/drivers/ipc/completion.c
    ${RT_THREAD}/components/drivers/ipc/dataqueue.c
    ${RT_THREAD}/components/drivers/ipc/pipe.c
    ${RT_THREAD}/components/drivers/ipc/ringblk_buf.c
    ${RT_THREAD}/components/drivers/ipc/ringbuffer.c
    ${RT_THREAD}/components/drivers/ipc/waitqueue.c
    ${RT_THREAD}/components/drivers/ipc/workqueue.c
    ${RT_THREAD}/components/drivers/rtc/rtc.c
    ${RT_THREAD}/components/drivers/rtc/soft_rtc.c
    ${RT_THREAD}/components/drivers/serial/serial.c
    ${RT_THREAD}/components/finsh/cmd.c
    ${RT_THREAD}/components/finsh/msh.c
    ${RT_THREAD}/components/finsh/msh_file.c
    ${RT_THREAD}/components/finsh/shell.c
    ${RT_THREAD}/components/libc/compilers/common/stdlib.c
    ${RT_THREAD}/components/libc/compilers/common/cstdlib.c
    ${RT_THREAD}/components/libc/compilers/common/time.c
    ${RT_THREAD}/components/libc/compilers/newlib/syscalls.c
    ${RT_THREAD}/components/libc/cplusplus/cxx_Mutex.cpp
    ${RT_THREAD}/components/libc/cplusplus/cxx_Semaphore.cpp
    ${RT_THREAD}/components/libc/cplusplus/cxx_Thread.cpp
    ${RT_THREAD}/components/libc/cplusplus/cxx_crt.cpp
    ${RT_THREAD}/components/libc/cplusplus/cxx_crt_init.c
    ${RT_THREAD}/components/libc/posix/delay/delay.c

    # ${RT_THREAD}/components/libc/posix/io/aio/aio.c
    ${RT_THREAD}/components/libc/posix/io/poll/poll.c
    ${RT_THREAD}/components/libc/posix/io/poll/select.c
    ${RT_THREAD}/components/libc/posix/io/stdio/libc.c
    ${RT_THREAD}/components/libc/posix/io/termios/termios.c
    ${RT_THREAD}/components/libc/posix/ipc/mqueue.c
    ${RT_THREAD}/components/libc/posix/ipc/semaphore.c
    ${RT_THREAD}/components/libc/posix/pthreads/pthread.c
    ${RT_THREAD}/components/libc/posix/pthreads/pthread_attr.c
    ${RT_THREAD}/components/libc/posix/pthreads/pthread_barrier.c
    ${RT_THREAD}/components/libc/posix/pthreads/pthread_cond.c
    ${RT_THREAD}/components/libc/posix/pthreads/pthread_mutex.c
    ${RT_THREAD}/components/libc/posix/pthreads/pthread_rwlock.c
    ${RT_THREAD}/components/libc/posix/pthreads/pthread_spin.c
    ${RT_THREAD}/components/libc/posix/pthreads/pthread_tls.c
    ${RT_THREAD}/components/libc/posix/pthreads/sched.c
    ${RT_THREAD}/components/libc/posix/signal/posix_signal.c
    ${RT_THREAD}/components/net/netdev/src/netdev.c
    ${RT_THREAD}/components/net/netdev/src/netdev_ipaddr.c
    ${RT_THREAD}/components/net/sal/dfs_net/dfs_net.c
    ${RT_THREAD}/components/net/sal/socket/net_netdb.c
    ${RT_THREAD}/components/net/sal/socket/net_sockets.c
    ${RT_THREAD}/components/net/sal/src/sal_socket.c
    ${RT_THREAD}/libcpu/arm/common/backtrace.c
    ${RT_THREAD}/libcpu/arm/common/div0.c
    ${RT_THREAD}/libcpu/arm/common/showmem.c
    ${RT_THREAD}/libcpu/arm/cortex-a/cache.c
    ${RT_THREAD}/libcpu/arm/cortex-a/context_gcc.S
    ${RT_THREAD}/libcpu/arm/cortex-a/cp15_gcc.S
    ${RT_THREAD}/libcpu/arm/cortex-a/cpu.c
    ${RT_THREAD}/libcpu/arm/cortex-a/gic.c
    ${RT_THREAD}/libcpu/arm/cortex-a/interrupt.c
    ${RT_THREAD}/libcpu/arm/cortex-a/mmu.c
    ${RT_THREAD}/libcpu/arm/cortex-a/stack.c
    ${RT_THREAD}/libcpu/arm/cortex-a/start_gcc.S
    ${RT_THREAD}/libcpu/arm/cortex-a/trap.c
    ${RT_THREAD}/libcpu/arm/cortex-a/vector_gcc.S
    ${RT_THREAD}/src/clock.c
    ${RT_THREAD}/src/components.c
    ${RT_THREAD}/src/cpu.c
    ${RT_THREAD}/src/device.c
    ${RT_THREAD}/src/idle.c
    ${RT_THREAD}/src/ipc.c
    ${RT_THREAD}/src/irq.c
    ${RT_THREAD}/src/kservice.c
    ${RT_THREAD}/src/mem.c
    ${RT_THREAD}/src/memheap.c
    ${RT_THREAD}/src/mempool.c
    ${RT_THREAD}/src/object.c
    ${RT_THREAD}/src/scheduler.c
    ${RT_THREAD}/src/signal.c
    ${RT_THREAD}/src/thread.c
    ${RT_THREAD}/src/timer.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${INCLUDES}
)