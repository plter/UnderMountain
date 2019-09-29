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
#include "FilterChain.h"
#include "AbstractSessionStorage.h"

namespace um {
    class Server {
    public:
        typedef std::function<boost::asio::awaitable<void>(RequestSPtr, ResponseSPtr)> UMServerHandler;

    public:
        Server(int port, UMServerHandler handler = nullptr);

    public:
        [[nodiscard]] unsigned short inline getPort() const {
            return _port;
        }

        [[nodiscard]] const AbstractViewEngineSPtr &getViewEngine() const;

        void setViewEngine(const AbstractViewEngineSPtr &viewEngine);

        void start();

        [[nodiscard]] const FilterChainSPtr &getFilterChain() const;

        const AbstractSessionStorageSPtr getSessionStorage() const;

        void setSessionStorage(const AbstractSessionStorageSPtr &sessionStorage);

    private:
        unsigned short _port;
        boost::asio::io_context _io;
        UMServerHandler _handler;
        AbstractViewEngineSPtr _viewEngine;
        FilterChainSPtr _filterChain;
        um::AbstractSessionStorageSPtr _sessionStorage;

    private:
        boost::asio::awaitable<void> umServerListener();

        boost::asio::awaitable<void> asyncSessionHandler(TcpStreamSPtr stream);
    };

    typedef std::shared_ptr<Server> ServerSPtr;
}

#endif //UNDERMOUNTAIN_SERVER_H
