//
// Created by plter on 2019/9/18.
//

#ifndef UNDERMOUNTAIN_REQUEST_H
#define UNDERMOUNTAIN_REQUEST_H

#include "um_types.h"
#include <boost/asio/awaitable.hpp>
#include <string>
#include "URLParameters.h"

namespace um {
    class Request {
    public:
        Request(TcpStreamSPtr stream);

        boost::asio::awaitable<void> asyncInit();

    public:
        [[nodiscard]] const TcpStreamSPtr &getStream() const;

        [[nodiscard]] const BeastHttpStringBodyRequest &getBeastRequest() const;

        [[nodiscard]] const std::string &getTarget() const;

        [[nodiscard]] boost::beast::http::verb getMethod() const;

        [[nodiscard]] const std::string &getRequestPath() const;

        [[nodiscard]] const std::string &getQuery() const;

        [[nodiscard]] const std::string &getBody() const;

        const URLParameterPairs &getPostVars() const;

        const URLParameterPairs &getGetVars() const;

    private:
        TcpStreamSPtr _stream;
        BeastHttpStringBodyRequest _beastRequest;
        std::string _target;
        std::string _requestPath;
        std::string _query;
        boost::beast::http::verb _method;
        std::string _body;
        std::string _contentType;
        URLParameterPairs _postVars;
        URLParameterPairs _getVars;
    };

    typedef std::shared_ptr<Request> RequestSPtr;
}


#endif //UNDERMOUNTAIN_REQUEST_H
