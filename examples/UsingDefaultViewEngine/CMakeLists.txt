include_directories(
        ../../code/include
)

link_libraries(
        pthread
        boost_coroutine
        boost_log-mt
        um_server
)


add_executable(UsingDefaultViewEngine main.cpp RootView.cpp)