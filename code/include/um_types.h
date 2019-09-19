//
// Created by plter on 2019/9/18.
//

#ifndef UNDERMOUNTAIN_UM_TYPES_H
#define UNDERMOUNTAIN_UM_TYPES_H

#include <boost/beast.hpp>
#include <boost/asio/awaitable.hpp>
#include <functional>
#include <boost/log/trivial.hpp>

#define UM_LOG(level) BOOST_LOG_TRIVIAL(level) << __FILE__ << "(" << __LINE__ << ") "

namespace um {
    typedef boost::beast::tcp_stream TcpStream;
    typedef std::shared_ptr<TcpStream> TcpStreamSPtr;
    typedef boost::beast::http::request<boost::beast::http::string_body> BeastHttpStringBodyRequest;
    typedef std::shared_ptr<BeastHttpStringBodyRequest> BeastHttpStringBodyRequestSPtr;
    typedef boost::beast::http::response<boost::beast::http::string_body> BeastHttpStringBodyResponse;
    typedef std::shared_ptr<BeastHttpStringBodyResponse> BeastHttpStringBodyResponseSPtr;
}

#endif //UNDERMOUNTAIN_UM_TYPES_H
