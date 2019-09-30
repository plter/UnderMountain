//
// Created by plter on 2019/9/21.
//

#ifndef UNDERMOUNTAIN_DEFAULTVIEWENGINE_H
#define UNDERMOUNTAIN_DEFAULTVIEWENGINE_H

#include "AbstractViewEngine.h"
#include "AbstractDefaultView.h"
#include <memory>
#include "ViewData.h"

namespace um {
    class DefaultViewEngine : public AbstractViewEngine {

    public:
        DefaultViewEngine();

        std::string render(std::string name, ViewData data) override;

        void setView(const std::string &name, AbstractDefaultViewSPtr viewSPtr);

        [[nodiscard]] const std::map<std::string, AbstractDefaultViewSPtr> &getViewMap() const;

    private:
        std::map<std::string, AbstractDefaultViewSPtr> _viewMap;
    };
}


#endif //UNDERMOUNTAIN_DEFAULTVIEWENGINE_H
