//
// Created by plter on 2019/10/1.
//

#include "ControllerIndex.h"

#define ACTION [](um::RequestSPtr req,um::ResponseSPtr res)->boost::asio::awaitable<void>

ControllerIndex::ControllerIndex() : Controller("index") {
    addAction("index", ACTION {
        co_await
        res->end("Controller index");
    });
}
