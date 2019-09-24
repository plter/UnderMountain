//
// Created by plter on 2019/9/21.
//

#include "RootView.h"
#include <boost/format.hpp>
#include <sstream>

RootView::RootView() {}

std::string RootView::render(std::map<std::string, std::any> data) {
    return (std::stringstream() << R"(
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Hello World</title>
    </head>
    <body>
        <div>
            Name: )" << std::any_cast<std::string>(data["name"]) << R"(
        </div>
        <div>
            age: )" << std::any_cast<std::string>(data["age"]) << R"(
        </div>
    </body>
</html>
)").str();
}


