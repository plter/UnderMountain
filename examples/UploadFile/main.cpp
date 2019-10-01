//
// Created by plter on 2019/9/17.
//

#include <um.h>
#include <boost/asio/use_awaitable.hpp>


class ResultController : public um::Controller {
public:
    explicit ResultController(const std::string &name = "result") : Controller(name) {
        addAction("index", [](um::RequestSPtr req, um::ResponseSPtr res) -> boost::asio::awaitable<void> {

            co_return;
        });
    }
};

int main() {
    um::Server server(9000);
    server.getFilterChain()->addFilter(std::make_shared<um::FilterStaticFiles>());
    server.addController(std::make_shared<ResultController>());
    server.start();
    return 0;
}