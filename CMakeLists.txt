cmake_minimum_required(VERSION 2.8.10)

project(roboime-intel-tx)
include_directories("src")

find_library(USB_LIB usb-1.0)
if(${USB_LIB} STREQUAL "USB_LIB-NOTFOUND")
  message(STATUS "The USB libs appear to not be installed.")
  message(FATAL_ERROR "On Ubuntu, do: sudo apt-get install libusb-1.0-0 libusb-1.0-0-dev")
endif()

add_executable(simple src/main.cpp src/joystick.cc)

target_link_libraries(simple ${USB_LIB})
