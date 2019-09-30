//
// Created by plter on 2019/9/22.
//

#include "../include/FilterChain.h"

const std::deque<um::FilterSPtr> &um::FilterChain::getFilters() const {
    return _filters;
}

void um::FilterChain::addFilter(const um::FilterSPtr &filter) {
    _filters.push_back(filter);
}

boost::asio::awaitable<void> um::FilterChain::run(um::RequestSPtr req, um::ResponseSPtr res) {
    for (auto &f:_filters) {
        co_await
        f->run(req, res);

        if (res->isHeaderSent()) {
            break;
        }
    }
}
