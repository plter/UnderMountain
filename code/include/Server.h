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
#include "AbstractViewEngine.h"

namespace um {
    class Server {
    public:
        typedef std::function<boost::asio::awaitable<void>(RequestSPtr, ResponseSPtr)> UMServerHandler;

    public:
        Server(int port, UMServerHandler handler);

    public:
        unsigned short inline getPort() const {
            return _port;
        }

        const AbstractViewEngineSPtr &getViewEngine() const;

        void setViewEngine(const AbstractViewEngineSPtr &viewEngine);

    private:
        unsigned short _port;
        boost::asio::io_context _io;
        UMServerHandler _handler;
        AbstractViewEngineSPtr _viewEngine;

    private:
        boost::asio::awaitable<void> umServerListener();

        boost::asio::awaitable<void> asyncSessionHandler(TcpStreamSPtr stream);
    };

    typedef std::shared_ptr<Server> ServerSPtr;
}

#endif //UNDERMOUNTAIN_SERVER_H
