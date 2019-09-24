//
// Created by plter on 2019/9/21.
//

#include "RootView.h"
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
        <div>
            Name: )" << data.getString("name") << R"(
        </div>
        <div>
            age: )" << data.getString("age") << R"(
        </div>
    </body>
</html>
)").str();
}


