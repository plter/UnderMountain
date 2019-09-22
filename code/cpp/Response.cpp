//
// Created by plter on 2019/9/19.
//

#include "../include/Response.h"
#include <boost/asio/use_awaitable.hpp>
#include "../include/Server.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <utility>

um::Response::Response(Server *server, um::TcpStreamSPtr stream, RequestSPtr request) :
        _server(server),
        _stream(std::move(stream)),
        _headDataSent(false),
        _request(std::move(request)),
        _httpState(boost::beast::http::status::ok) {

    set(boost::beast::http::field::content_type, "text/html");
    set(boost::beast::http::field::server, UM_SERVER_INFO);

    buildMimeTypeMap();
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

um::Server *um::Response::getServer() const {
    return _server;
}

boost::asio::awaitable<void> um::Response::sendFile(const std::string &filePath) {
    if (!_headDataSent) {
        boost::beast::error_code ec;
        boost::beast::http::file_body::value_type body;
        body.open(filePath.c_str(), boost::beast::file_mode::scan, ec);
        if (ec) {
            setHttpState(boost::beast::http::status::internal_server_error);
            co_await end(ec.message());
            co_return;
        }
        auto const size = body.size();
        boost::beast::http::response<boost::beast::http::file_body> response(
                std::piecewise_construct,
                std::make_tuple(std::move(body)),
                std::make_tuple(boost::beast::http::status::ok, _request->getBeastRequest().version())
        );
        response.set(boost::beast::http::field::server, UM_SERVER_INFO);
        response.set(boost::beast::http::field::content_type, getMimeType(filePath));
        response.set(boost::beast::http::field::content_length, size);
        response.keep_alive(_request->getBeastRequest().keep_alive());
        co_await boost::beast::http::async_write(*_stream, response, boost::asio::use_awaitable);
        _headDataSent = true;
    }
}

void um::Response::buildMimeTypeMap() {
    _mimeTypeMap[".htm"] = "text/html";
    _mimeTypeMap[".html"] = "text/html";
    _mimeTypeMap[".css"] = "text/css";
    _mimeTypeMap[".txt"] = "text/plain";
    _mimeTypeMap[".js"] = "application/javascript";
    _mimeTypeMap[".json"] = "application/json";
    _mimeTypeMap[".xml"] = "application/xml";
    _mimeTypeMap[".swf"] = "application/x-shockwave-flash";
    _mimeTypeMap[".flv"] = "video/x-flv";
    _mimeTypeMap[".png"] = "image/png";
    _mimeTypeMap[".jpg"] = "image/jpeg";
    _mimeTypeMap[".jpeg"] = "image/jpeg";
    _mimeTypeMap[".jpe"] = "image/jpeg";
    _mimeTypeMap[".gif"] = "image/gif";
    _mimeTypeMap[".bmp"] = "image/bmp";
    _mimeTypeMap[".ico"] = "image/vnd.microsoft.icon";
    _mimeTypeMap[".tiff"] = "image/tiff";
    _mimeTypeMap[".tif"] = "image/tiff";
    _mimeTypeMap[".svg"] = "image/svg+xml";
    _mimeTypeMap[".svgz"] = "image/svg+xml";
}

std::string um::Response::getMimeType(std::string file) {
    boost::filesystem::path filePath(file);
    auto ext = boost::to_lower_copy(filePath.extension().string());
    auto mimeType = _mimeTypeMap[ext];
    if (!mimeType.empty()) {
        return mimeType;
    }
    return "application/text";
}
