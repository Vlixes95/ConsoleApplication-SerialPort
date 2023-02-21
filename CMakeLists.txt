cmake_minimum_required(VERSION 3.24)
project(ConsoleApplication_SerialPort)

set(CMAKE_CXX_STANDARD 17)

include_directories( Inc )

add_executable(ConsoleApplication_SerialPort Src/main.cpp Src/SerialPort.cpp Inc/SerialPort.h)
