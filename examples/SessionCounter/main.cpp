//
// Created by plter on 2019/9/17.
//

#include <um.h>
#include <boost/asio/use_awaitable.hpp>
#include <sstream>

int main() {
    um::Server server(9000, [](um::RequestSPtr req, auto res) -> boost::asio::awaitable<void> {

        if (req->getRequestPath() == "/") {
            req->setSessionValue("count", req->getSessionValueAsInt("count", 0) + 1);

            co_await res->end((std::stringstream() << "Count: " << req->getSessionValue("count")).str());
        }
    });
    server.start();
    return 0;
}