//
// Created by plter on 2019/9/24.
//

#include "../include/Dumper.h"
#include <iostream>

void um::Dumper::dumpURLParameters(std::map<std::string, um::URLParameterValue> params) {
    std::cout << "URL parameters(" << std::endl;
    if (!params.empty()) {
        for (auto &[key, value] :params) {
            std::cout << "    " << key << ":" << value.toString() << std::endl;
        }
    }
    std::cout << ")" << std::endl;
}

void um::Dumper::dumpStringMap(const std::map<std::string, std::string> &map) {
    std::cout << "String map(" << std::endl;
    for (auto &[key, value]:map) {
        std::cout << "    " << key << ":" << value << std::endl;
    }
    std::cout << ")" << std::endl;
}

void um::Dumper::dumpStringVector(const std::vector<std::string> &stringVector) {
    std::cout << "String vector(" << std::endl;
    for (auto &s:stringVector) {
        std::cout << "    " << s << std::endl;
    }
    std::cout << ")" << std::endl;
}
