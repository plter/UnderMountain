//
// Created by plter on 2019/9/21.
//

#ifndef UNDERMOUNTAIN_ROOTVIEW_H
#define UNDERMOUNTAIN_ROOTVIEW_H

#include <um.h>

class RootView : public um::AbstractDefaultView {
public:
    RootView();

    std::string render(um::ViewData data) override;
};


#endif //UNDERMOUNTAIN_ROOTVIEW_H
