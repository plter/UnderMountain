//
// Created by plter on 2019/9/29.
//

#include "../include/FilterSession.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
#include "../include/Cookie.h"
#include "../include/Dumper.h"
#include <map>
#include "../include/Server.h"
#include "../include/um_types.h"

boost::asio::awaitable<void> um::FilterSession::run(um::RequestSPtr req, um::ResponseSPtr res) {
    auto beastReq = req->getBeastRequest();
    auto cookieString = beastReq[boost::beast::http::field::cookie];
    std::map<std::string, std::string> cookie = um::Cookie::decode(cookieString.to_string());
    req->setCookie(cookie);

    auto sessionId = cookie["um_session_id"];
    auto sessionStorage = req->getServer()->getSessionStorage();
    std::map<std::string, std::string> session;
    if (!sessionId.empty()) {
        session = sessionStorage->getSession(sessionId);
    }
    if (session.empty()) {
        static boost::uuids::random_generator generator;
        sessionId = (std::stringstream() << generator()).str();

        res->set(
                boost::beast::http::field::set_cookie,
                (std::stringstream() << "um_session_id=" << sessionId << "; Path=/; ").str()
        );

        session["_sid"] = sessionId;
        sessionStorage->setSession(sessionId, session);
    }

    req->setSessionId(sessionId);
    return Filter::run(req, res);
}
