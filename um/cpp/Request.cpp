//
// Created by plter on 2019/9/18.
//

#include "../include/Request.h"
#include <boost/beast.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <utility>
#include <iostream>
#include "../include/Server.h"

namespace beast = boost::beast;
namespace http = beast::http;

um::Request::Request(um::Server *server, um::TcpStreamSPtr stream) :
        _stream(std::move(stream)), _method(http::verb::get) {
    _server = server;
}

boost::asio::awaitable<void> um::Request::asyncInit() {
    beast::flat_buffer buffer;
    _beastRequest = BeastHttpStringBodyRequest();
    co_await http::async_read(*_stream, buffer, _beastRequest, boost::asio::use_awaitable);

    _target = _beastRequest.target().to_string();
    _method = _beastRequest.method();

    auto questionMarkPosition = _target.find('?');
    if (questionMarkPosition != std::string::npos) {
        _requestPath = _target.substr(0, questionMarkPosition);
        _query = _target.substr(questionMarkPosition + 1);
    } else {
        _requestPath = _target;
    }
    _body = _beastRequest.body();
    _contentType = _beastRequest[boost::beast::http::field::content_type].to_string();

    if (_contentType == "application/x-www-form-urlencoded") {
        _getVars = um::URLParameters::decode(_query);
        if (_method == boost::beast::http::verb::post) {
            _postVars = um::URLParameters::decode(_body);
        }
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

const std::string &um::Request::getRequestPath() const {
    return _requestPath;
}

const std::string &um::Request::getQuery() const {
    return _query;
}

http::verb um::Request::getMethod() const {
    return _method;
}

const std::string &um::Request::getBody() const {
    return _body;
}

const um::URLParameterPairs &um::Request::getPostVars() const {
    return _postVars;
}

const um::URLParameterPairs &um::Request::getGetVars() const {
    return _getVars;
}

const std::map<std::string, std::string> &um::Request::getCookie() const {
    return _cookie;
}

void um::Request::setCookie(const std::map<std::string, std::string> &cookie) {
    _cookie = cookie;
}

um::Server *um::Request::getServer() const {
    return _server;
}

const std::string &um::Request::getSessionId() const {
    return _sessionId;
}

void um::Request::setSessionId(const std::string &sessionId) {
    _sessionId = sessionId;
}

std::map<std::string, std::string> &um::Request::getSession() {
    return getServer()->getSessionStorage()->getSession(getSessionId());
}

std::string um::Request::getSessionValue(const std::string &key) {
    return getSessionStorage()->getSessionValue(getSessionId(), key);
}

void um::Request::setSessionValue(const std::string &key, std::string value) {
    getSessionStorage()->setSessionValue(getSessionId(), key, std::move(value));
}

void um::Request::setSessionValue(const std::string &key, int value) {
    setSessionValue(key, std::to_string(value));
}

std::string um::Request::getSessionValue(const std::string &key, std::string defaultValue) {
    auto v = getSessionValue(key);
    if (!v.empty()) {
        return v;
    } else {
        return defaultValue;
    }
}

int um::Request::getSessionValueAsInt(const std::string &key) {
    return std::stoi(getSessionValue(key));
}

int um::Request::getSessionValueAsInt(const std::string &key, int defaultValue) {
    auto v = getSessionValue(key);
    if (!v.empty()) {
        return std::stoi(v);
    } else {
        return defaultValue;
    }
}

um::AbstractSessionStorageSPtr um::Request::getSessionStorage() const {
    return getServer()->getSessionStorage();
}

const std::string &um::Request::getControllerName() const {
    return _controllerName;
}

void um::Request::setControllerName(const std::string &controllerName) {
    _controllerName = controllerName;
}

const std::string &um::Request::getActionName() const {
    return _actionName;
}

void um::Request::setActionName(const std::string &actionName) {
    _actionName = actionName;
}

void um::Request::addArg(std::string arg) {
    _args.emplace_back(arg);
}

std::string um::Request::arg(int index) {
    return _args[index];
}

const std::vector<std::string> &um::Request::getArgs() const {
    return _args;
}
