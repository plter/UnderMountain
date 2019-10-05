//
// Created by plter on 2019/9/17.
//

#include <um.h>
#include <boost/asio/use_awaitable.hpp>
#include <mysql.h>
#include <memory>

int main() {

    MYSQL *mysql;
    mysql = mysql_init(nullptr);
    mysql_real_connect(mysql, "127.0.0.1", "root", "example", "mydb", 3306, nullptr, 0);
//    mysql_real_query_start()
    mysql_close(mysql);
    return 0;
}