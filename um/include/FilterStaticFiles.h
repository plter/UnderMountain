//
// Created by plter on 2019/9/22.
//

#ifndef UNDERMOUNTAIN_FILTERSTATICFILES_H
#define UNDERMOUNTAIN_FILTERSTATICFILES_H

#include "Filter.h"
#include <memory>

namespace um {
    class FilterStaticFiles : public Filter {
    public:
        FilterStaticFiles(std::string staticRoot = "public");

        boost::asio::awaitable<void> run(RequestSPtr req, ResponseSPtr res) override;

    private:
        std::string _staticRoot;
    };

    typedef std::shared_ptr<FilterStaticFiles> FilterStaticFilesSPtr;
}


#endif //UNDERMOUNTAIN_FILTERSTATICFILES_H
