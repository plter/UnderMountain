//
// Created by plter on 2019/9/23.
//

#ifndef UNDERMOUNTAIN_URLPARAMETERDECODER_H
#define UNDERMOUNTAIN_URLPARAMETERDECODER_H

#include <map>
#include <string>
#include "URLParameterValue.h"

namespace um {

    typedef std::map<std::string, um::URLParameterValue> URLParameterPairs;

    class URLParameterDecoder {

    public:
        static URLParameterPairs decode(std::string parametersString);
    };
}


#endif //UNDERMOUNTAIN_URLPARAMETERDECODER_H
