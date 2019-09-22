//
// Created by plter on 2019/9/18.
//

#include "../include/Request.h"
#include <boost/beast.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <utility>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;

um::Request::Request(um::TcpStreamSPtr stream) :
        _stream(std::move(stream)) {

}

boost::asio::awaitable<void> um::Request::asyncInit() {
    beast::flat_buffer buffer;
    _beastRequest = BeastHttpStringBodyRequest();
    co_await http::async_read(*_stream, buffer, _beastRequest, boost::asio::use_awaitable);

    _target = _beastRequest.target().to_string();
    _method = _beastRequest.method_string().to_string();
    auto questionMarkPosition = _target.find('?');
    if (questionMarkPosition != std::string::npos) {
        _requestPath = _target.substr(0, questionMarkPosition);
        _query = _target.substr(questionMarkPosition + 1);
    } else {
        _requestPath = _target;
    }
}

const um::TcpStreamSPtr &um::Request::getStream() const {
    return _stream;
}

const um::BeastHttpStringBodyRequest &um::Request::getBeastRequest() const {
    return _beastRequest;
}

const std::string &um::Request::getTarget() const {
    return _target;
}

const std::string &um::Request::getMethod() const {
    return _method;
}

const std::string &um::Request::getRequestPath() const {
    return _requestPath;
}

const std::string &um::Request::getQuery() const {
    return _query;
}
