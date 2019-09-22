//
// Created by plter on 2019/9/18.
//

#ifndef UNDERMOUNTAIN_REQUEST_H
#define UNDERMOUNTAIN_REQUEST_H

#include "um_types.h"
#include <boost/asio/awaitable.hpp>

namespace um {
    class Request {
    public:
        Request(TcpStreamSPtr stream);

        boost::asio::awaitable<void> asyncInit();

    public:
        const TcpStreamSPtr &getStream() const;

        const BeastHttpStringBodyRequest &getBeastRequest() const;

    private:
        TcpStreamSPtr _stream;
        BeastHttpStringBodyRequest _beastRequest;
    };

    typedef std::shared_ptr<Request> RequestSPtr;
}


#endif //UNDERMOUNTAIN_REQUEST_H
