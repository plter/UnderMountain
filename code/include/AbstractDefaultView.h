//
// Created by plter on 2019/9/21.
//

#ifndef UNDERMOUNTAIN_ABSTRACTDEFAULTVIEW_H
#define UNDERMOUNTAIN_ABSTRACTDEFAULTVIEW_H

#include <string>
#include <map>
#include <any>
#include <memory>

namespace um {
    class AbstractDefaultView {
    public:
        virtual std::string render(std::map<std::string, std::any> data) = 0;
    };

    typedef std::shared_ptr<AbstractDefaultView> AbstractDefaultViewSPtr;
}


#endif //UNDERMOUNTAIN_ABSTRACTDEFAULTVIEW_H
