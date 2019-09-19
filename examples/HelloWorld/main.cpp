//
// Created by plter on 2019/9/17.
//

#include <um.h>
#include <boost/asio/use_awaitable.hpp>

int main() {
    um::Server server(9000, [](auto req, auto res) -> boost::asio::awaitable<void> {
        co_await res->end("Hello World");
    });
}