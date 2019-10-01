//
// Created by plter on 2019/9/30.
//

#include "../include/FilterControllers.h"
#include "../include/um_types.h"
#include <boost/regex.hpp>

boost::asio::awaitable<void> um::FilterControllers::run(um::RequestSPtr req, um::ResponseSPtr res) {
    static boost::regex r("^/([^/]*).*$");
    boost::smatch matcher;
    if (boost::regex_match(req->getRequestPath(), matcher, r)) {
        std::string controllerName = matcher[1];
        if (controllerName.empty()) {
            controllerName = "index";
        }
        auto controller = _controllers[controllerName];
        if (controller) {
            req->setControllerName(controllerName);
            co_await
            controller->doAction(req, res);
        }
    }
}

void um::FilterControllers::addController(const um::ControllerSPtr &controller) {
    _controllers[controller->getName()] = controller;
}
