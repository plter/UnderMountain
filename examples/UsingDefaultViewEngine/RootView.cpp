//
// Created by plter on 2019/9/21.
//

#include "RootView.h"

RootView::RootView() {}

std::string RootView::render(std::map<std::string, std::any> data) {
    return R"(
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Hello World</title>
    </head>
    <body>
        Default view engine is ok.
    </body>
</html>)";
}


