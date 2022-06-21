# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/Users/altair823/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_temperature_cpp C CXX ASM)

set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pico_temperature_cpp pico_temperature_cpp.cpp )

pico_set_program_name(pico_temperature_cpp "pico_temperature_cpp")
pico_set_program_version(pico_temperature_cpp "0.1")

pico_enable_stdio_uart(pico_temperature_cpp 1)
pico_enable_stdio_usb(pico_temperature_cpp 1)

# Add the standard library to the build
target_link_libraries(pico_temperature_cpp pico_stdlib)

# Add any user requested libraries
target_link_libraries(pico_temperature_cpp
        hardware_spi
        hardware_i2c
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        hardware_adc
        )

pico_add_extra_outputs(pico_temperature_cpp)

