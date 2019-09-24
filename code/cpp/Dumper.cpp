//
// Created by plter on 2019/9/24.
//

#include "../include/Dumper.h"
#include <iostream>

void um::Dumper::dumpURLParameters(std::map<std::string, um::URLParameterValue> params) {
    std::cout << "URL parameters(" << std::endl;
    if (params.size()) {
        for (auto &[key, value] :params) {
            std::cout << "    " << key << ":" << value.toString() << std::endl;
        }
    }
    std::cout << ")" << std::endl;
}
