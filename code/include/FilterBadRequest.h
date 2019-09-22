//
// Created by plter on 2019/9/22.
//

#ifndef UNDERMOUNTAIN_FILTERBADREQUEST_H
#define UNDERMOUNTAIN_FILTERBADREQUEST_H

#include "Filter.h"

namespace um {
    class FilterBadRequest : public Filter {

    public:
        boost::asio::awaitable<void> run(RequestSPtr req, ResponseSPtr res) override;
    };
}


#endif //UNDERMOUNTAIN_FILTERBADREQUEST_H
