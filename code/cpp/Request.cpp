//
// Created by plter on 2019/9/18.
//

#include "../include/Request.h"
#include <boost/beast.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <utility>

namespace beast = boost::beast;
namespace http = beast::http;

um::Request::Request(um::TcpStreamSPtr stream) :
        _stream(std::move(stream)) {

}

boost::asio::awaitable<void> um::Request::asyncInit() {
    beast::flat_buffer buffer;
    _beastRequest = BeastHttpStringBodyRequest();
    co_await http::async_read(*_stream, buffer, _beastRequest, boost::asio::use_awaitable);
}

const um::TcpStreamSPtr &um::Request::getStream() const {
    return _stream;
}

const um::BeastHttpStringBodyRequest &um::Request::getBeastRequest() const {
    return _beastRequest;
}
