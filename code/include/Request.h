//
// Created by plter on 2019/9/18.
//

#ifndef UNDERMOUNTAIN_REQUEST_H
#define UNDERMOUNTAIN_REQUEST_H

#include "um_types.h"
#include <boost/asio/awaitable.hpp>
#include <string>

namespace um {
    class Request {
    public:
        Request(TcpStreamSPtr stream);

        boost::asio::awaitable<void> asyncInit();

    public:
        [[nodiscard]] const TcpStreamSPtr &getStream() const;

        [[nodiscard]] const BeastHttpStringBodyRequest &getBeastRequest() const;

        [[nodiscard]] const std::string &getTarget() const;

        [[nodiscard]] const std::string &getMethod() const;

        const std::string &getRequestPath() const;

        const std::string &getQuery() const;

    private:
        TcpStreamSPtr _stream;
        BeastHttpStringBodyRequest _beastRequest;
        std::string _target;
        std::string _method;
        std::string _requestPath;
        std::string _query;
    };

    typedef std::shared_ptr<Request> RequestSPtr;
}


#endif //UNDERMOUNTAIN_REQUEST_H
