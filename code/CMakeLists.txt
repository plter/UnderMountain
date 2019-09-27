
link_libraries(
        pthread
        boost_coroutine
        boost_log-mt
        boost_filesystem
)

add_library(
        um_server SHARED
        cpp/Server.cpp
        cpp/Request.cpp
        cpp/Response.cpp
        cpp/DefaultViewEngine.cpp
        cpp/FilterChain.cpp
        cpp/Filter.cpp
        cpp/FilterStaticFiles.cpp
        cpp/FilterBadRequest.cpp
        cpp/URLParameters.cpp
        cpp/URLParameterValue.cpp
        cpp/Dumper.cpp
        cpp/ViewData.cpp
)