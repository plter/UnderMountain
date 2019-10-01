
link_libraries(
        pthread
        boost_coroutine
        boost_log-mt
        boost_filesystem
        boost_regex
)

add_library(
        um_server SHARED
        cpp/Server.cpp
        cpp/Request.cpp
        cpp/Response.cpp
        cpp/DefaultViewEngine.cpp
        cpp/FilterChain.cpp
        cpp/FilterStaticFiles.cpp
        cpp/FilterBadRequest.cpp
        cpp/URLParameterDecoder.cpp
        cpp/URLParameterValue.cpp
        cpp/Dumper.cpp
        cpp/ViewData.cpp
        cpp/DbRow.cpp
        cpp/DbGrid.cpp
        cpp/DbField.cpp
        cpp/FilterSession.cpp
        cpp/Cookie.cpp
        cpp/DefaultSessionStorage.cpp
        cpp/FilterControllers.cpp
        cpp/Controller.cpp
        cpp/Logger.cpp
        cpp/FormDataDecoder.cpp
        cpp/FormDataValueItem.cpp
        cpp/FormDataValue.cpp
)