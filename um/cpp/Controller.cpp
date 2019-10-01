//
// Created by plter on 2019/10/1.
//


#include "../include/Controller.h"
#include "../include/um_types.h"
#include <boost/regex.hpp>

#include <utility>

const std::string &um::Controller::getName() const {
    return _name;
}

um::Controller::Controller(std::string name) : _name(std::move(name)) {}

void um::Controller::addAction(const std::string &name, um::ControllerAction action) {
    _actions[name] = std::move(action);
}

boost::asio::awaitable<void> um::Controller::doAction(const um::RequestSPtr &req, um::ResponseSPtr res) {
    boost::regex r("^/([^/]*)/([^/]*).*$");
    boost::smatch matcher;
    std::string actionName;
    um::ControllerAction action;
    if (boost::regex_match(req->getRequestPath(), matcher, r)) {
        actionName = matcher[2];
    }
    if (actionName.empty()) {
        actionName = "index";
    }
    action = _actions[actionName];
    if (action) {
        req->setActionName(actionName);
        co_await action(req, res);
    }
}

