//
// Created by plter on 2019/9/22.
//

#ifndef UNDERMOUNTAIN_ABSTRACTFILTER_H
#define UNDERMOUNTAIN_ABSTRACTFILTER_H

#include "memory"
#include "Request.h"
#include "Response.h"
#include <boost/asio/awaitable.hpp>

namespace um {
    class AbstractFilter {

    public:
        virtual boost::asio::awaitable<void> run(RequestSPtr req, ResponseSPtr res) = 0;
    };

    typedef std::shared_ptr<AbstractFilter> FilterSPtr;
}


#endif //UNDERMOUNTAIN_ABSTRACTFILTER_H
