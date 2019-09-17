//
// Created by plter on 2019/9/17.
//

#include <iostream>
#include <UMServer.h>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;

int main() {
    UMServer server(9000, [](auto stream) -> boost::asio::awaitable<void> {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        co_await http::async_read(stream, buffer, req, boost::asio::use_awaitable);

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::content_type, "text/html");
        res.body() = "Hello World";

        res.prepare_payload();
        co_await http::async_write(stream, res, boost::asio::use_awaitable);
        stream.close();
    });
}