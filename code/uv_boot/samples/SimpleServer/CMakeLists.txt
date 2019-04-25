cmake_minimum_required(VERSION 3.14)
project(uv_boot_simple_server C)

set(CMAKE_C_STANDARD 11)

link_libraries(uv_boot)

add_executable(
        simple_server
        simple_server.c
)