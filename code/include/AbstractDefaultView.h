//
// Created by plter on 2019/9/21.
//

#ifndef UNDERMOUNTAIN_ABSTRACTDEFAULTVIEW_H
#define UNDERMOUNTAIN_ABSTRACTDEFAULTVIEW_H

#include <string>
#include <map>
#include <any>
#include <memory>
#include "ViewData.h"

namespace um {
    class AbstractDefaultView {
    public:
        virtual std::string render(ViewData data) = 0;
    };

    typedef std::shared_ptr<AbstractDefaultView> AbstractDefaultViewSPtr;
}


#endif //UNDERMOUNTAIN_ABSTRACTDEFAULTVIEW_H
