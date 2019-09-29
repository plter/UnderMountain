//
// Created by plter on 2019/9/29.
//

#include "../include/Cookie.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include "../include/Dumper.h"
#include "../include/um_types.h"

std::map<std::string, std::string> um::Cookie::decode(std::string cookie) {
    std::vector<std::string> tokens;
    boost::split(tokens, cookie, boost::is_any_of("; "));
    std::map<std::string, std::string> result;

    if (!tokens.empty()) {
        for (auto &token:tokens) {
            auto eqMarkerPosition = token.find('=');
            if (eqMarkerPosition != std::string::npos) {
                std::string key = token.substr(0, eqMarkerPosition);
                std::string value = token.substr(eqMarkerPosition + 1);
                result[key] = value;
            }
        }
    }
    return result;
}
