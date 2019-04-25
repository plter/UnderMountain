cmake_minimum_required(VERSION 3.14)
project(uv_boot C)

set(CMAKE_C_STANDARD 11)

include_directories(
        /usr/local/Cellar/libuv/1.28.0/include
        include
)

link_directories(
        /usr/local/Cellar/libuv/1.28.0/lib
)

link_libraries(
        uv
)


add_library(
        uv_boot
        include/uv_boot.h
        source/http_parser.c
        source/http_server.c
)


add_subdirectory(samples/SimpleServer/)
