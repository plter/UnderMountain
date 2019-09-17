//
// Created by plter on 2019/9/17.
//

#ifndef UNDERMOUNTAIN_UMSERVER_H
#define UNDERMOUNTAIN_UMSERVER_H

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <functional>

class UMServer {

public:
    typedef std::function<boost::asio::awaitable<void>(boost::beast::tcp_stream)> UMServerHandler;

public:
    UMServer(int port, UMServerHandler handler);

private:
    unsigned short _port;
    boost::asio::io_context _io;
    UMServerHandler _handler;

private:
    boost::asio::awaitable<void> umServerListener();

    boost::asio::awaitable<void> asyncSessionHandler(boost::beast::tcp_stream stream);

public:
    unsigned short getPort() const;
};


#endif //UNDERMOUNTAIN_UMSERVER_H
