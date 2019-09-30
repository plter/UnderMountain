include_directories(
        ../../um/include
)

link_libraries(
        pthread
        boost_coroutine
        boost_log-mt
        um_server
)

add_executable(Controllers main.cpp)