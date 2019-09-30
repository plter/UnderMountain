//
// Created by plter on 2019/9/22.
//

#include "../include/FilterBadRequest.h"
#include <boost/beast.hpp>

boost::asio::awaitable<void> um::FilterBadRequest::run(um::RequestSPtr req, um::ResponseSPtr res) {
    if (req->getMethod() != boost::beast::http::verb::get && req->getMethod() != boost::beast::http::verb::post) {
        res->setHttpState(boost::beast::http::status::bad_request);
        co_await
        res->end("Unsupported method.");
        co_return;
    }

    auto target = req->getBeastRequest().target();

    if (target.empty() || target[0] != '/' || target.find("..") != boost::beast::string_view::npos) {
        res->setHttpState(boost::beast::http::status::bad_request);
        co_await
        res->end("Illegal request-target");
        co_return;
    }
}
