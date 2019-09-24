//
// Created by plter on 2019/9/21.
//

#include <um.h>
#include <map>
#include <string>
#include <any>
#include "RootView.h"
#include <tuple>

int main() {
    um::Server server(9000, [](um::RequestSPtr req, um::ResponseSPtr res) -> boost::asio::awaitable<void> {

        if (req->getRequestPath() == "/result") {

            auto params = req->getPostVars();
            um::ViewData data(
                    {
                            {"name", *params["name"]},
                            {"age",  *params["age"]}
                    }
            );

            co_await
            res->render("root", data);
        }
    });

    server.getFilterChain()->addFilter(std::make_shared<um::FilterStaticFiles>());

    auto ve = std::dynamic_pointer_cast<um::DefaultViewEngine>(server.getViewEngine());
    ve->setView("root", std::make_shared<RootView>());
    server.start();
    return 0;
}