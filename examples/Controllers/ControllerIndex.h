//
// Created by plter on 2019/10/1.
//

#ifndef UNDERMOUNTAIN_CONTROLLERINDEX_H
#define UNDERMOUNTAIN_CONTROLLERINDEX_H

#include <um.h>

#define ACTION [](um::RequestSPtr req,um::ResponseSPtr res)->boost::asio::awaitable<void>

class ControllerIndex : public um::Controller {
public:
    ControllerIndex() : Controller("index") {
        addAction("index", ACTION {
            um::Dumper::dumpStringVector(req->getArgs());

            co_await
            res->end("Controller index");
        });
    };
};


#endif //UNDERMOUNTAIN_CONTROLLERINDEX_H
