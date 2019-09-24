//
// Created by plter on 2019/9/23.
//

#ifndef UNDERMOUNTAIN_URLPARAMETERS_H
#define UNDERMOUNTAIN_URLPARAMETERS_H

#include <map>
#include <string>
#include "URLParameterValue.h"

namespace um {

    typedef std::map<std::string, um::URLParameterValue> URLParameterPairs;

    class URLParameters {

    public:
        static URLParameterPairs decode(std::string parametersString);
    };
}


#endif //UNDERMOUNTAIN_URLPARAMETERS_H
