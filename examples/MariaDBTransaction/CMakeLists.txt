include_directories(
        ../../um/include
        /usr/local/include/mariadb
)

link_directories(
        /usr/local/lib/mariadb
)

link_libraries(
        pthread
        boost_coroutine
        boost_log-mt
        um_server
        mariadb
)

add_executable(MariaDBTransaction main.cpp)