
link_libraries(
        pthread
        boost_coroutine
        boost_log-mt
)

add_library(
        UMServer
        cpp/Server.cpp
        cpp/Request.cpp
        cpp/Response.cpp
)