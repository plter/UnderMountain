//
// Created by plter on 2019/9/17.
//

#include <um.h>
#include <boost/asio/use_awaitable.hpp>

int main() {
    um::Server server(9000, [](um::RequestSPtr req, um::ResponseSPtr res) -> boost::asio::awaitable<void> {
        if (req->getRequestPath() == "/") {
            co_await
            res->redirect("/page");
        } else if (req->getRequestPath() == "/page") {
            co_await
            res->end("The real page.");
        }
    });
    server.start();
    return 0;
}