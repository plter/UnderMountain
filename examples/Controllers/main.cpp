//
// Created by plter on 2019/9/17.
//

#include <um.h>
#include <boost/asio/use_awaitable.hpp>

int main() {
    um::Server server(9000);
    server.start();
    return 0;
}