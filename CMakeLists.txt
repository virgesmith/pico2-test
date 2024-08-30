
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_SDK_PATH ../../pico-sdk) # release 2.0.0 doesnt work (with TinyUSB 0.16)

# ensure we have the correct pico_sdk_import.cmake
execute_process (COMMAND
  bash -c "cp ${PICO_SDK_PATH}/external/pico_sdk_import.cmake .."
)

if (${PICO_PLATFORM} STREQUAL "rp2350-arm-s")
  # set(PICO_TOOLCHAIN_PATH /usr)
  set(PICO_TOOLCHAIN_PATH /opt/arm-gcc-13.2)
elseif (${PICO_PLATFORM} STREQUAL "rp2350-riscv")
  set(PICO_TOOLCHAIN_PATH /opt/riscv32-embecosm-ubuntu2204-gcc13.2.0)
else()
  message(FATAL_ERROR "Specify PICO_PLATFORM: either rp2350-arm-s or rp2350-riscv")
endif()

set(PICO_BOARD pico2 CACHE STRING "Board type")

# set(PICO_PLATFORM rp2350-arm-s)
# set(PICO_PLATFORM rp2350-riscv)

# this must come before project
include(pico_sdk_import.cmake)

project(pico2_test C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


add_executable(pico2_test
  main.cpp
  flash.cpp
)
pico_set_program_name(pico2_test "pico2_test")
pico_set_program_version(pico2_test "0.1.0")

pico_enable_stdio_uart(pico2_test 0)
pico_enable_stdio_usb(pico2_test 1)

target_link_libraries(pico2_test
  pico_stdlib
  pico_sha256
)

# Add the standard include files to the build
target_include_directories(pico2_test PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(pico2_test)

