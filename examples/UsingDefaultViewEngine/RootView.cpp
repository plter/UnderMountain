//
// Created by plter on 2019/9/21.
//

#include "RootView.h"
#include <boost/format.hpp>
#include <sstream>

RootView::RootView() {}

std::string RootView::render(um::ViewData data) {

    return (std::stringstream() << R"(
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Hello World</title>
    </head>
    <body>
        Hello )" << data.getString("name") << R"(
    </body>
</html>
)").str();
}


