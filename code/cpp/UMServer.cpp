//
// Created by plter on 2019/9/17.
//

#include "../include/UMServer.h"
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <utility>

using namespace boost;
using namespace boost::asio::ip;
using namespace boost::asio;
using namespace boost::asio::this_coro;
using namespace boost::beast;

UMServer::UMServer(int port, UMServerHandler handler) :
        _port(port), _handler(std::move(handler)), _io() {

    boost::asio::signal_set signals(_io, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto) { _io.stop(); });
    co_spawn(_io, std::bind(&UMServer::umServerListener, this), detached);
    _io.run();
}


awaitable<void> UMServer::umServerListener() {
    auto executor = co_await
    this_coro::executor;

    tcp::acceptor acceptor(executor, {tcp::v4(), _port});

    std::cout << "Server started at port " << _port << std::endl;

    while (true) {
        tcp::socket socket = co_await
        acceptor.async_accept(use_awaitable);

        co_spawn(
                executor,
                [socket = std::move(socket), this]() mutable {
                    return this->asyncSessionHandler(std::move(beast::tcp_stream(std::move(socket))));
                },
                detached
        );
    }
}

unsigned short UMServer::getPort() const {
    return _port;
}

boost::asio::awaitable<void> UMServer::asyncSessionHandler(boost::beast::tcp_stream stream) {
    try {
        co_await
        this->_handler(std::move(stream));

//        beast::flat_buffer buffer;
//        http::request<http::string_body> req;
//        std::size_t n = co_await
//        http::async_read(stream, buffer, req, use_awaitable);
//
//        http::response<http::string_body> res{http::status::ok, req.version()};
//        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//        res.set(http::field::content_type, "text/html");
//        res.keep_alive(req.keep_alive());
//        res.body() = "Hello World";
//
//        res.prepare_payload();
//        co_await http::async_write(stream, res, use_awaitable);
//        stream.close();
    }
    catch (std::exception &e) {
        std::printf("async_session Exception: %s\n", e.what());
    }
}

