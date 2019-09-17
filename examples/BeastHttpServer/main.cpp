//
// Created by plter on 2019/9/17.
//

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <cstdio>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>

#define SERVER_PORT 9999

using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;
namespace this_coro = boost::asio::this_coro;
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


awaitable<void> async_session(beast::tcp_stream stream) {
    try {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        std::size_t n = co_await
        http::async_read(stream, buffer, req, use_awaitable);

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "Hello World";
        res.prepare_payload();

        co_await http::async_write(stream, res, use_awaitable);
        stream.close();
    }
    catch (std::exception &e) {
        std::printf("async_session Exception: %s\n", e.what());
    }
}

awaitable<void> listener() {
    auto executor = co_await
    this_coro::executor;

    tcp::acceptor acceptor(executor, {tcp::v4(), SERVER_PORT});

    std::cout << "Server started at port " << SERVER_PORT << std::endl;

    while (true) {
        tcp::socket socket = co_await
        acceptor.async_accept(use_awaitable);

        co_spawn(
                executor,
                [socket = std::move(socket)]() mutable {
                    return async_session(std::move(beast::tcp_stream(std::move(socket))));
                },
                detached
        );
    }
}

int main() {
    try {
        boost::asio::io_context io_context(1);

        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&](auto, auto) { io_context.stop(); });

        co_spawn(io_context, listener, detached);
        io_context.run();
    }
    catch (std::exception &e) {
        std::printf("Exception: %s\n", e.what());
    }
}