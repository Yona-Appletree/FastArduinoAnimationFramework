cmake_minimum_required(VERSION 3.2)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME FastArduinoAnimationFramework)
set(ARDUINO_EXTRA_LIBRARIES_PATH "/Users/yona/Documents/Arduino/libraries")
project(${PROJECT_NAME})

# register_hardware_platform("/Applications/Arduino 1.6.5.app/Contents/Java/hardware/arduino/avr")

set(${CMAKE_PROJECT_NAME}_BOARD nano)
set(${CMAKE_PROJECT_NAME}_SKETCH FastArduinoAnimationFramework.ino)

message(INFO "Platform libs ${${ARDUINO_PLATFORM}_LIBRARIES_PATH}")

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
