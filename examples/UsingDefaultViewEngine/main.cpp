//
// Created by plter on 2019/9/21.
//

#include <um.h>
#include <map>
#include <string>
#include <any>
#include "RootView.h"

int main() {
    um::Server server(9000, [](auto req, um::ResponseSPtr res) -> boost::asio::awaitable<void> {
        um::ViewData data(
                {
                        {"name", "YUNP"},
                }
        );

        co_await
        res->render("root", data);
    });

    auto ve = std::dynamic_pointer_cast<um::DefaultViewEngine>(server.getViewEngine());
    ve->setView("root", std::make_shared<RootView>());
    server.start();
    return 0;
}