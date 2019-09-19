//
// Created by plter on 2019/9/17.
//

#ifndef UNDERMOUNTAIN_SERVER_H
#define UNDERMOUNTAIN_SERVER_H

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <functional>
#include "um_types.h"
#include "Request.h"
#include "Response.h"

namespace um {
    class Server {
    public:
        typedef std::function<boost::asio::awaitable<void>(RequestSPtr, ResponseSPtr)> UMServerHandler;

    public:
        Server(int port, UMServerHandler handler);

    private:
        unsigned short _port;
        boost::asio::io_context _io;
        UMServerHandler _handler;

    private:
        boost::asio::awaitable<void> umServerListener();

        boost::asio::awaitable<void> asyncSessionHandler(TcpStreamSPtr stream);

    public:
        unsigned short inline getPort() const {
            return _port;
        }
    };
}

#endif //UNDERMOUNTAIN_SERVER_H
