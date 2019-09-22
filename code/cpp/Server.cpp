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

using namespace boost;
using namespace boost::asio::ip;
using namespace boost::asio;
using namespace boost::asio::this_coro;
using namespace boost::beast;

namespace um {

    Server::Server(int port, UMServerHandler handler) :
            _port(port), _handler(std::move(handler)),
            _io() {

        _viewEngine = std::dynamic_pointer_cast<AbstractViewEngine>(std::make_shared<DefaultViewEngine>());
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
            auto request = std::make_shared<Request>(stream);
            co_await
            request->asyncInit();

            auto response = std::make_shared<Response>(this, stream, request);

            co_await this->_handler(request, response);
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

        boost::asio::signal_set signals(_io, SIGINT, SIGTERM);
        signals.async_wait([&](auto, auto) { _io.stop(); });
        co_spawn(_io, std::bind(&Server::umServerListener, this), detached);
        _io.run();
    }

}
