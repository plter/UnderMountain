//
// Created by plter on 2019/9/17.
//

#include <um.h>
#include <boost/asio/use_awaitable.hpp>
#include <memory>
#include "ControllerIndex.h"

int main() {
    um::Server server(9000);
    server.addController(std::make_shared<ControllerIndex>());
    server.start();
    return 0;
}