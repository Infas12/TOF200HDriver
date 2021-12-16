cmake_minimum_required(VERSION 2.8.3)
project(serial)


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

list(APPEND serial_SRCS src/impl/unix.cc)
list(APPEND serial_SRCS src/impl/list_ports/list_ports_linux.cc)

## Build Serial library
add_library(${PROJECT_NAME} ${serial_SRCS})

## Include linux API
target_link_libraries(${PROJECT_NAME} rt pthread)

## Source
set(SRCS
        src/Packet/Packet.cpp
        src/Packet/HostPacket.cpp
        src/Packet/MemoryStream.cpp
        src/Crc.cpp
        src/TOF200H.cpp
        src/crc16.c)

add_executable(Test main.cpp ${SRCS})

add_dependencies(Test ${PROJECT_NAME})
target_link_libraries(Test ${PROJECT_NAME})
