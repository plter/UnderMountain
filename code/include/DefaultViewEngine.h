//
// Created by plter on 2019/9/21.
//

#ifndef UNDERMOUNTAIN_DEFAULTVIEWENGINE_H
#define UNDERMOUNTAIN_DEFAULTVIEWENGINE_H

#include "AbstractViewEngine.h"
#include "AbstractDefaultView.h"
#include <memory>

namespace um {
    class DefaultViewEngine : public AbstractViewEngine {

    public:
        DefaultViewEngine();

        std::string render(std::string name, std::map<std::string, std::any> data) override;

        void setView(const std::string& name, AbstractDefaultViewSPtr viewSPtr);

        const std::map<std::string, AbstractDefaultViewSPtr> &getViewMap() const;

    private:
        std::map<std::string, AbstractDefaultViewSPtr> _viewMap;
    };
}


#endif //UNDERMOUNTAIN_DEFAULTVIEWENGINE_H
