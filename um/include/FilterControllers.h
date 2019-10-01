//
// Created by plter on 2019/9/30.
//

#ifndef UNDERMOUNTAIN_FILTERCONTROLLERS_H
#define UNDERMOUNTAIN_FILTERCONTROLLERS_H

#include "AbstractFilter.h"
#include "Controller.h"
#include <map>
#include <unordered_map>

namespace um {
    class FilterControllers : public um::AbstractFilter {
    public:
        boost::asio::awaitable<void> run(RequestSPtr req, ResponseSPtr res) override;

        void addController(const um::ControllerSPtr& controller);

    private:
        std::unordered_map<std::string, um::ControllerSPtr> _controllers;
    };

    typedef std::shared_ptr<FilterControllers> FilterControllersSPtr;
}


#endif //UNDERMOUNTAIN_FILTERCONTROLLERS_H
