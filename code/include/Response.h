//
// Created by plter on 2019/9/19.
//

#ifndef UNDERMOUNTAIN_RESPONSE_H
#define UNDERMOUNTAIN_RESPONSE_H

#include "um_types.h"
#include <string>
#include <boost/asio/awaitable.hpp>
#include "Request.h"
#include <boost/beast.hpp>

namespace um {
    class Response {
    public:
        Response(TcpStreamSPtr stream, RequestSPtr request);

        boost::asio::awaitable<void> end(std::string data);

    public:
        const TcpStreamSPtr &getStream() const;

        bool isHeaderSent() const;

        const BeastHttpStringBodyResponseSPtr &getBeastResponseSPtr() const;

        boost::beast::http::status getHttpState() const;

        void setHttpState(boost::beast::http::status status);

        const std::map<boost::beast::http::field, std::string> &getHeaders() const;

        void set(boost::beast::http::field key, const std::string &value);

    private:
        TcpStreamSPtr _stream;
        RequestSPtr _request;
        bool _headDataSent;// 第一批数据是否已发送
        BeastHttpStringBodyResponseSPtr _beastResponseSPtr;
        boost::beast::http::status _httpState;
        std::map<boost::beast::http::field, std::string> _responseHeaders;
    };

    typedef std::shared_ptr<Response> ResponseSPtr;
}


#endif //UNDERMOUNTAIN_RESPONSE_H
