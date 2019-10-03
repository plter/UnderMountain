cmake_minimum_required(VERSION 3.14)
project(UnderMountain)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-D_GNU_SOURCE -DBOOST_ASIO_HAS_CO_AWAIT -DBOOST_ALL_DYN_LINK -fcoroutines-ts -stdlib=libc++")

include_directories(
        /usr/local/include
)

link_directories(
        /usr/local/lib
)

add_subdirectory(um)
add_subdirectory(examples/BeastHttpServer)
add_subdirectory(examples/HelloWorld)
add_subdirectory(examples/UsingDefaultViewEngine)
add_subdirectory(examples/StaticWebRoot)
add_subdirectory(examples/PostData)
add_subdirectory(examples/ConnectMariaDB)
add_subdirectory(examples/SessionCounter)
add_subdirectory(examples/MariaDBTransaction)
add_subdirectory(examples/Controllers)
add_subdirectory(examples/UploadFile)
add_subdirectory(examples/Redirect)