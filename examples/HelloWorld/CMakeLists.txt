include_directories(
        ../../code/include
)

link_libraries(
        pthread
        boost_coroutine
        boost_log-mt
        UMServer
)

add_executable(HelloWorld main.cpp)