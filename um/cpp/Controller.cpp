//
// Created by plter on 2019/10/1.
//


#include "../include/Controller.h"
#include "../include/um_types.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <utility>
#include "../include/Logger.h"

const std::string &um::Controller::getName() const {
    return _name;
}

um::Controller::Controller(std::string name) : _name(std::move(name)) {}

void um::Controller::addAction(const std::string &name, um::ControllerAction action) {
    _actions[name] = std::move(action);
    UM_LOG(info) << "Add action: /" << getName() << "/" << name;
}

boost::asio::awaitable<void> um::Controller::doAction(const um::RequestSPtr &req, um::ResponseSPtr res) {
    static const boost::regex r("^/([^/]*)/([^/]*)(.*$)");
    boost::smatch matcher;
    std::string actionName;
    um::ControllerAction action;

    if (boost::regex_match(req->getRequestPath(), matcher, r)) {
        actionName = matcher[2];

        std::string argsString = matcher[3];
        std::vector<std::string> tokens;
        boost::split(tokens, argsString, boost::is_any_of("/"));
        for (auto &t:tokens) {
            if (!t.empty()) {
                req->addArg(t);
            }
        }
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

