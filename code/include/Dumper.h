//
// Created by plter on 2019/9/24.
//

#ifndef UNDERMOUNTAIN_DUMPER_H
#define UNDERMOUNTAIN_DUMPER_H

#include <map>
#include "URLParameterValue.h"
#include <string>

namespace um {
    class Dumper {
    public:
        static void dumpURLParameters(std::map<std::string, um::URLParameterValue> params);

        static void dumpStringMap(const std::map<std::string, std::string>& map);
    };
}

#endif //UNDERMOUNTAIN_DUMPER_H
