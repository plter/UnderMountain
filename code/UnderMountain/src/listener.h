//
// Created by yunp on 2019-05-12.
//

#ifndef UNDERMOUNTAIN_LISTENER_H
#define UNDERMOUNTAIN_LISTENER_H

#include "session.h"
#include "tools.h"
#include <string>

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener> {
    net::io_context &ioc_;
    tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;

public:
    listener(net::io_context &ioc,
             tcp::endpoint endpoint,
             std::shared_ptr<std::string const> const &doc_root);

    // Start accepting incoming connections
    void run();

private:
    void do_accept();

    void on_accept(beast::error_code ec, tcp::socket socket);
};

#endif //UNDERMOUNTAIN_LISTENER_H
