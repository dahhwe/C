cmake_minimum_required(VERSION 3.24)
project(sys5 C)

set(CMAKE_C_STANDARD 99)

add_executable(sys5 server.c client.c client.h server.h)
