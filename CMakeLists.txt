cmake_minimum_required(VERSION 2.8.3)
project(serial)

# Find catkin
add_compile_options(-std=c++11)
add_compile_options(-o2)
add_compile_options(-march=native)
add_compile_options(-lpthread)

## Include headers
include_directories(include)

## Library Files
set(serial_SRCS
    src/serial.cc
    include/serial/serial.h
    include/serial/v8stdint.h)

list(APPEND serial_SRCS src/impl/win.cc)
list(APPEND serial_SRCS src/impl/list_ports/list_ports_win.cc)

## Build Serial library
add_library(${PROJECT_NAME} ${serial_SRCS})

## Include windows API
target_link_libraries(${PROJECT_NAME} setupapi)

## Source
set(SRCS )

add_executable(Test main.cpp ${SRCS})

add_dependencies(Test ${PROJECT_NAME})
target_link_libraries(Test ${PROJECT_NAME})
