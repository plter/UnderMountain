//
// Created by plter on 2019/9/19.
//

#include "../include/Response.h"
#include <boost/asio/use_awaitable.hpp>
#include "../include/Server.h"

#include <utility>

um::Response::Response(Server *server, um::TcpStreamSPtr stream, RequestSPtr request) :
        _server(server),
        _stream(std::move(stream)),
        _headDataSent(false),
        _request(std::move(request)),
        _httpState(boost::beast::http::status::ok) {

    set(boost::beast::http::field::content_type, "text/html");
    set(boost::beast::http::field::server, UM_SERVER_INFO);
}

const um::TcpStreamSPtr &um::Response::getStream() const {
    return _stream;
}

bool um::Response::isHeaderSent() const {
    return _headDataSent;
}

boost::asio::awaitable<void> um::Response::end(std::string data) {
    if (!_headDataSent) {
        auto response = BeastHttpStringBodyResponse(
                _httpState,
                _request->getBeastRequest().version()
        );

        _beastResponse = response;

        for (auto const&[key, val]:_responseHeaders) {
            response.set(key, val);
        }
        response.keep_alive(_request->getBeastRequest().keep_alive());
        response.body() = data;
        response.prepare_payload();
        co_await boost::beast::http::async_write(*_stream, response, boost::asio::use_awaitable);
        _stream->close();
        _headDataSent = true;
    }
}

boost::beast::http::status um::Response::getHttpState() const {
    return _httpState;
}

void um::Response::setHttpState(boost::beast::http::status status) {
    _httpState = status;
}

const std::map<boost::beast::http::field, std::string> &um::Response::getHeaders() const {
    return _responseHeaders;
}

void um::Response::set(boost::beast::http::field key, const std::string &value) {
    _responseHeaders[key] = value;
}

boost::asio::awaitable<void> um::Response::render(std::string viewName, std::map<std::string, std::any> data) {
    co_await end(_server->getViewEngine()->render(std::move(viewName), std::move(data)));
}

const std::any &um::Response::getBeastResponse() const {
    return _beastResponse;
}
