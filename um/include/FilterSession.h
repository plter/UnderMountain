//
// Created by plter on 2019/9/29.
//

#ifndef UNDERMOUNTAIN_FILTERSESSION_H
#define UNDERMOUNTAIN_FILTERSESSION_H

#include "Filter.h"

namespace um {
class FilterSession: public um::Filter {
public:
    boost::asio::awaitable<void> run(RequestSPtr req, ResponseSPtr res) override;
};
}


#endif //UNDERMOUNTAIN_FILTERSESSION_H
