//
// Created by plter on 2019/9/30.
//

#ifndef UNDERMOUNTAIN_FILTERCONTROLLERS_H
#define UNDERMOUNTAIN_FILTERCONTROLLERS_H

#include "AbstractFilter.h"
#include "AbstractController.h"
#include <map>

namespace um {
    class FilterControllers : public um::AbstractFilter {
    public:
        boost::asio::awaitable<void> run(RequestSPtr req, ResponseSPtr res) override;

        void addController(um::AbstractControllerSPtr controller);

    private:
        std::map<std::string, um::AbstractControllerSPtr> _controllers;
    };

    typedef std::shared_ptr<FilterControllers> FilterControllersSPtr;
}


#endif //UNDERMOUNTAIN_FILTERCONTROLLERS_H
