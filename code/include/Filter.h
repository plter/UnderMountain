//
// Created by plter on 2019/9/22.
//

#ifndef UNDERMOUNTAIN_FILTER_H
#define UNDERMOUNTAIN_FILTER_H

#include "memory"
#include "Request.h"
#include "Response.h"
#include <boost/asio/awaitable.hpp>

namespace um {
    class Filter {

    public:
        virtual boost::asio::awaitable<void> run(RequestSPtr req, ResponseSPtr res);
    };

    typedef std::shared_ptr<Filter> FilterSPtr;
}


#endif //UNDERMOUNTAIN_FILTER_H
