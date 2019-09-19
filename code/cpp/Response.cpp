//
// Created by plter on 2019/9/19.
//

#include "../include/Response.h"
#include <boost/asio/use_awaitable.hpp>

#include <utility>

um::Response::Response(um::TcpStreamSPtr stream, RequestSPtr request) :
        _stream(std::move(stream)),
        _headerSent(false),
        _request(request),
        _httpState(boost::beast::http::status::ok) {

    set(boost::beast::http::field::content_type, "text/html");
}

const um::TcpStreamSPtr &um::Response::getStream() const {
    return _stream;
}

bool um::Response::isHeaderSent() const {
    return _headerSent;
}

boost::asio::awaitable<void> um::Response::end(std::string data) {
    if (!_headerSent) {
        _beastResponseSPtr = std::make_shared<BeastHttpStringBodyResponse>(
                _httpState,
                _request->getBeastRequestSPtr()->version()
        );
        for (auto const&[key, val]:_headers) {
            _beastResponseSPtr->set(key, val);
        }
        _beastResponseSPtr->body() = data;
        _beastResponseSPtr->prepare_payload();
        co_await boost::beast::http::async_write(*_stream, *_beastResponseSPtr, boost::asio::use_awaitable);
        _stream->close();
        _headerSent = true;
    }
}

const um::BeastHttpStringBodyResponseSPtr &um::Response::getBeastResponseSPtr() const {
    return _beastResponseSPtr;
}

boost::beast::http::status um::Response::getHttpState() const {
    return _httpState;
}

void um::Response::setHttpState(boost::beast::http::status status) {
    _httpState = status;
}

const std::map<boost::beast::http::field, std::string> &um::Response::getHeaders() const {
    return _headers;
}

void um::Response::set(boost::beast::http::field key, const std::string &value) {
    _headers[key] = std::move(value);
}


