//
// Created by plter on 2019/9/21.
//

#include <um.h>
#include <map>
#include <string>
#include <any>

int main() {
    um::Server server(9000, [](auto req, um::ResponseSPtr res) -> boost::asio::awaitable<void> {
        co_return;
    });

    server.getFilterChain()->addFilter(std::make_shared<um::FilterStaticFiles>());
    server.start();
    return 0;
}