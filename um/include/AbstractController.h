//
// Created by plter on 2019/9/30.
//

#ifndef UNDERMOUNTAIN_ABSTRACTCONTROLLER_H
#define UNDERMOUNTAIN_ABSTRACTCONTROLLER_H

#include <memory>
#include <string>

namespace um {
    class AbstractController {
        virtual std::string getPath() = 0;
    };

    typedef std::shared_ptr<AbstractController> AbstractControllerSPtr;
}

#endif //UNDERMOUNTAIN_ABSTRACTCONTROLLER_H
