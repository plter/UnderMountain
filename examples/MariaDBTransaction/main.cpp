//
// Created by plter on 2019/9/17.
//

#include <um.h>
#include <boost/asio/use_awaitable.hpp>
#include <MariaDBConnection.h>
#include <memory>

int main() {

    auto conn = std::make_shared<um::MariaDBConnection>();
    conn->connect("127.0.0.1", "mydb", "root", "example", "utf8", 3306);

    conn->autocommit(false);
    auto count = conn->executeSQL("INSERT INTO user (name) VALUES('Peter')");
    std::cout << "Affected rows: " << count << std::endl;
    conn->rollback();
//    conn->commit();
    conn->close();
    return 0;
}