cmake_minimum_required(VERSION 3.14)
project(ConsoleApplication_SerialPort)

set(CMAKE_CXX_STANDARD 17)

include_directories(Inc)

add_executable(
        ConsoleApplication_SerialPort
        main.cpp
        Src/SerialPort.cpp
        Inc/SerialPort.h
        Inc/msgpack.h
        Src/msgpack.cpp
        Src/actions.cpp Inc/actions.h)
