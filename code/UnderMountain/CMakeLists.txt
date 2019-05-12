cmake_minimum_required(VERSION 3.5)
project(UnderMountain)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        /Work/lib/boost_1_70_0
)

link_libraries(
        pthread
)

add_executable(
        UnderMountain
        src/main.cpp
        src/tools.cpp
        src/listener.cpp
        src/mime_types.cpp
)