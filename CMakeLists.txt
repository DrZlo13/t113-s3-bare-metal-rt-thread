set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Prevent CMake from testing the toolchain
set(CMAKE_C_COMPILER_FORCED 1)
set(CMAKE_CXX_COMPILER_FORCED 1)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# Tools definitions
set(ARM_TARGET_TRIPLET arm-none-eabi)

find_program(CMAKE_C_COMPILER NAMES "${ARM_TARGET_TRIPLET}-gcc")
find_program(CMAKE_CXX_COMPILER NAMES "${ARM_TARGET_TRIPLET}-g++")
find_program(CMAKE_ASM_COMPILER NAMES "${ARM_TARGET_TRIPLET}-gcc")
find_program(CMAKE_AR NAMES "${ARM_TARGET_TRIPLET}-ar")
find_program(CMAKE_OBJCOPY NAMES "${ARM_TARGET_TRIPLET}-objcopy")
find_program(CMAKE_OBJDUMP NAMES "${ARM_TARGET_TRIPLET}-objdump")
find_program(SIZE NAMES "${ARM_TARGET_TRIPLET}-size")
find_program(XFEL NAMES xfel PATHS "${CMAKE_SOURCE_DIR}/tools/xfel")

# Project definitions
PROJECT("T113" C CXX ASM)

file(GLOB CORE_SOURCES
    "app/*.c*"
    "app/board/*.c*"
    "app/lib/*.c*"
    "app/lib/*/*.c*"
)

include_directories(
    "app/board"
)

set(SOURCES
    ${SOURCES}
    ${CORE_SOURCES}
)

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/app/board/link.lds")
set(EXECUTABLE "${PROJECT_NAME}.elf")
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(LST_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.lst)

add_compile_options(
    -march=armv7-a
    -marm
    -msoft-float
    -Wall
)

add_link_options(
    -march=armv7-a
    -marm
    -msoft-float
    -nostartfiles
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,-cref
    -Wl,-u,system_vectors
    -Wl,-u,finsh_system_init
    -Wl,-u,rt_work_sys_workqueue_init
    -Wl,-u,rt_soft_rtc_init
    -Wl,-u,aio_system_init
    -Wl,-u,libc_system_init
    -Wl,-u,pthread_key_system_init
    -Wl,-u,posix_sem_system_init
    -Wl,-u,posix_mq_system_init
    -Wl,-u,cplusplus_system_init
    -Wl,-u,_rt_clock_time_system_init
    -Wl,-u,sal_init
    --specs=nosys.specs # ???
    -T ${LINKER_SCRIPT}
)

add_compile_definitions(
    HAVE_CCONFIG_H
    __RTTHREAD__
    RT_USING_NEWLIB
    _POSIX_C_SOURCE=1
    RT_DEBUG_INIT
    HAL_ENABLE_ASSERT
)

add_executable(${EXECUTABLE} ${SOURCES} ${LINKER_SCRIPT})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/rt-thread-cmake")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/t113-s3-hal")

target_link_libraries(${EXECUTABLE} "rt-thread")
target_link_libraries(${EXECUTABLE} "t113-s3-hal")

# target_link_libraries(${EXECUTABLE} "c")
# target_link_libraries(${EXECUTABLE} "m")
# target_link_libraries(${EXECUTABLE} "gcc")

# Print size
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD COMMAND ${SIZE} ${EXECUTABLE})

# Make binary file.
add_custom_command(
    OUTPUT ${HEX_FILE}
    DEPENDS ${EXECUTABLE}
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${EXECUTABLE}> ${HEX_FILE}
    COMMENT "Building ${HEX_FILE}"
)

add_custom_command(
    OUTPUT ${BIN_FILE}
    DEPENDS ${EXECUTABLE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${EXECUTABLE}> ${BIN_FILE}
    COMMENT "Building ${BIN_FILE}"
)

# generate assembly listing after build
add_custom_command(
    TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -S $<TARGET_FILE:${EXECUTABLE}> > ${LST_FILE}
    COMMENT "Building ${LST_FILE}"
)

add_custom_target(
    flash_xfel_to_ddr
    ${XFEL} ddr t113-s3 && sleep 0.2 && ${XFEL} write 0x40000000 ${BIN_FILE} && ${XFEL} exec 0x40000000
    DEPENDS ${BIN_FILE}
    COMMENT "Flash the target DDR mem via xfel"
)