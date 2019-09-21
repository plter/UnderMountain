//
// Created by plter on 2019/9/21.
//

#ifndef UNDERMOUNTAIN_ABSTRACTVIEWENGINE_H
#define UNDERMOUNTAIN_ABSTRACTVIEWENGINE_H

#include <string>
#include <map>
#include <any>
#include <memory>

namespace um {
    class AbstractViewEngine {
    public:
        AbstractViewEngine() {}

        virtual std::string render(std::string name, std::map<std::string, std::any> data) = 0;
    };

    typedef std::shared_ptr<AbstractViewEngine> AbstractViewEngineSPtr;
}


#endif //UNDERMOUNTAIN_ABSTRACTVIEWENGINE_H
