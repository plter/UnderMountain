//
// Created by plter on 2019/9/17.
//

#include "../include/Server.h"
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <utility>
#include "../include/DefaultViewEngine.h"
#include "../include/FilterBadRequest.h"
#include "../include/FilterSession.h"
#include "../include/DefaultSessionStorage.h"
#include "../include/FilterControllers.h"
#include "../include/Logger.h"
#include <boost/system/system_error.hpp>

using namespace boost;
using namespace boost::asio::ip;
using namespace boost::asio;
using namespace boost::asio::this_coro;
using namespace boost::beast;

namespace um {

    Server::Server(int port, UMServerHandler handler) :
            _port(port),
            _handler(std::move(handler)),
            _concurrencyHint(10),
            _requestBodyLimit(1 * 1024 * 1024),
            _filterChain(std::make_shared<um::FilterChain>()) {

        setSessionStorage(std::make_shared<um::DefaultSessionStorage>());
        setViewEngine(std::dynamic_pointer_cast<AbstractViewEngine>(std::make_shared<DefaultViewEngine>()));
        _filterChain->addFilter(std::make_shared<FilterBadRequest>());
        _filterChain->addFilter(std::make_shared<FilterSession>());

        _filterControllers = std::make_shared<FilterControllers>();
        _filterChain->addFilter(_filterControllers);
    }


    awaitable<void> Server::umServerListener() {
        auto executor = co_await
        this_coro::executor;

        tcp::acceptor acceptor(executor, {tcp::v4(), _port});

        UM_LOG(info) << "Server started at port " << _port;

        while (true) {
            tcp::socket socket = co_await
            acceptor.async_accept(use_awaitable);

            co_spawn(
                    executor,
                    [socket = std::move(socket), this]() mutable {
                        return this->asyncSessionHandler(std::make_shared<boost::beast::tcp_stream>(std::move(socket)));
                    },
                    detached
            );
        }
    }

    boost::asio::awaitable<void> Server::asyncSessionHandler(TcpStreamSPtr stream) {
        try {
            auto request = std::make_shared<Request>(this, stream);
            um::ResponseSPtr response = std::make_shared<Response>(this, stream);

            do {
                try {
                    co_await
                    request->asyncInit();
                } catch (boost::system::system_error &e) {
                    UM_LOG(warning) << "what=" << e.what() << ",code=" << e.code();

                    if (e.code() == http::error::body_limit) {
                        response->setHttpState(boost::beast::http::status::payload_too_large);
                        response->end("Payload too large");
                        break;
                    }
                }

                if (!response->isHeaderSent()) {

                    response->setVersion(request->getBeastRequest().version());
                    response->keepAlive(request->getBeastRequest().keep_alive());

                    co_await
                    _filterChain->run(request, response);
                } else {
                    break;
                }

                if (!response->isHeaderSent()) {
                    if (_handler) {
                        co_await
                        this->_handler(request, response);
                    }
                } else {
                    break;
                }

                //After all task done, if the header still not send, we response a 404 page.
                if (!response->isHeaderSent()) {
                    response->setHttpState(boost::beast::http::status::not_found);
                    co_await
                    response->end("Resource not found.");
                    break;
                }
            } while (0);

            UM_LOG(trace) << request->getMethod()
                          << " [" << (unsigned) (response->getHttpState()) << "] "
                          << request->getTarget();
        } catch (std::exception &e) {
            UM_LOG(warning) << "Exception:" << e.what();
        }
    }

    const AbstractViewEngineSPtr &Server::getViewEngine() const {
        return _viewEngine;
    }

    void Server::setViewEngine(const AbstractViewEngineSPtr &viewEngine) {
        _viewEngine = viewEngine;
    }

    void Server::start() {

        _ioContext = std::make_shared<boost::asio::io_context>(getConcurrencyHint());
        boost::asio::signal_set signals(*_ioContext, SIGINT, SIGTERM);
        signals.async_wait([&](auto, auto) { _ioContext->stop(); });
        co_spawn(*_ioContext, std::bind(&Server::umServerListener, this), detached);
        _ioContext->run();
    }

    const FilterChainSPtr &Server::getFilterChain() const {
        return _filterChain;
    }

    const AbstractSessionStorageSPtr Server::getSessionStorage() const {
        return _sessionStorage;
    }

    void Server::setSessionStorage(const AbstractSessionStorageSPtr &sessionStorage) {
        _sessionStorage = sessionStorage;
    }

    const FilterControllersSPtr &Server::getFilterControllers() const {
        return _filterControllers;
    }

    void Server::addController(ControllerSPtr controller) {
        getFilterControllers()->addController(controller);
    }

    size_t Server::getRequestBodyLimit() const {
        return _requestBodyLimit;
    }

    void Server::setRequestBodyLimit(size_t requestBodyLimit) {
        _requestBodyLimit = requestBodyLimit;
    }

    int Server::getConcurrencyHint() const {
        return _concurrencyHint;
    }

    void Server::setConcurrencyHint(int concurrencyHint) {
        _concurrencyHint = concurrencyHint;
    }

    const IOContextSPtr &Server::getIOContext() const {
        return _ioContext;
    }
}
