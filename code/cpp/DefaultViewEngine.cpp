//
// Created by plter on 2019/9/21.
//

#include "../include/DefaultViewEngine.h"
#include "../include/um_types.h"

#include <utility>

um::DefaultViewEngine::DefaultViewEngine() {}

std::string um::DefaultViewEngine::render(std::string name, std::map<std::string, std::any> data) {
    auto view = _viewMap[name];
    if (view) {
        return view->render(data);
    } else {
        UM_LOG(warning) << "No view named " << name;
    }
    return std::string();
}

void um::DefaultViewEngine::setView(const std::string &name, um::AbstractDefaultViewSPtr viewSPtr) {
    _viewMap[name] = std::move(viewSPtr);
}

const std::map<std::string, um::AbstractDefaultViewSPtr> &um::DefaultViewEngine::getViewMap() const {
    return _viewMap;
}

