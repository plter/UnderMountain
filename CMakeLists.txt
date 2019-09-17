cmake_minimum_required(VERSION 3.14)
project(UnderMountain)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-DBOOST_ASIO_HAS_CO_AWAIT -fcoroutines-ts -stdlib=libc++")

include_directories(
        /usr/local/include
)

link_directories(
        /usr/local/lib
)

link_libraries(
        pthread
        boost_coroutine
)

add_subdirectory(code)
add_subdirectory(examples/BeastHttpServer)
add_subdirectory(examples/HelloWorld)