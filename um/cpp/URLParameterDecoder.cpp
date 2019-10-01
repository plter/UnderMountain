//
// Created by plter on 2019/9/23.
//

#include "../include/URLParameterDecoder.h"
#include <boost/algorithm/string.hpp>
#include <vector>

std::map<std::string, um::URLParameterValue> um::URLParameterDecoder::decode(std::string parametersString) {
    std::vector<std::string> tokens;
    boost::split(tokens, parametersString, boost::is_any_of("&"));
    std::map<std::string, um::URLParameterValue> result;

    if (!tokens.empty()) {
        for (auto &token:tokens) {
            auto eqMarkerPosition = token.find('=');
            if (eqMarkerPosition != std::string::npos) {
                std::string key = token.substr(0, eqMarkerPosition);
                std::string value = token.substr(eqMarkerPosition + 1);
                result[key].add(value);
            }
        }
    }
    return result;
}
