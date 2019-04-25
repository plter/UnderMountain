cmake_minimum_required(VERSION 3.14)
project(libuv_SimpleWebserver C)

set(CMAKE_C_STANDARD 11)

include_directories(
        /Work/gitroot/github/plter/UnderMountain/code/http_parser
        /usr/local/Cellar/libuv/1.28.0/include
)

link_directories(
        /usr/local/Cellar/libuv/1.28.0/lib
        /Work/gitroot/github/plter/UnderMountain/code/http_parser/out
)

link_libraries(
        uv
        http_parser
)

add_executable(libuv_SimpleWebserver main.c)