//
// Created by plter on 2019/9/30.
//

#ifndef UNDERMOUNTAIN_CONTROLLER_H
#define UNDERMOUNTAIN_CONTROLLER_H

#include <memory>
#include <string>
#include <map>
#include <functional>
#include "Response.h"
#include "Request.h"
#include <boost/asio/awaitable.hpp>
#include <unordered_map>


namespace um {
    typedef std::function<boost::asio::awaitable<void>(RequestSPtr, ResponseSPtr)> ControllerAction;

    class Controller {
    public:
        explicit Controller(std::string name);

        [[nodiscard]] const std::string &getName() const;

        void addAction(const std::string &name, ControllerAction action);

        boost::asio::awaitable<void> doAction(const RequestSPtr &req, ResponseSPtr res);

    private:
        std::string _name;
        std::unordered_map<std::string, ControllerAction> _actions;
    };

    typedef std::shared_ptr<Controller> ControllerSPtr;
}

#endif //UNDERMOUNTAIN_CONTROLLER_H
