//
// Created by plter on 2019/9/22.
//

#ifndef UNDERMOUNTAIN_FILTERCHAIN_H
#define UNDERMOUNTAIN_FILTERCHAIN_H

#include <deque>
#include "AbstractFilter.h"
#include "Request.h"
#include "Response.h"
#include <boost/asio/awaitable.hpp>
#include <memory>

namespace um {
    class FilterChain {

    public:
        void addFilter(const FilterSPtr &filter);

        [[nodiscard]] const std::deque<FilterSPtr> &getFilters() const;

        boost::asio::awaitable<void> run(RequestSPtr req, ResponseSPtr res);

    private:
        std::deque<FilterSPtr> _filters;
        FilterSPtr _emptyFilter;
    };

    typedef std::shared_ptr<FilterChain> FilterChainSPtr;
}


#endif //UNDERMOUNTAIN_FILTERCHAIN_H
