//
// Created by plter on 2019/9/29.
//

#ifndef UNDERMOUNTAIN_COOKIE_H
#define UNDERMOUNTAIN_COOKIE_H

#include <map>
#include <string>

namespace um {
    class Cookie {
    public:
        static std::map<std::string, std::string> decode(std::string cookie);
    };
}


#endif //UNDERMOUNTAIN_COOKIE_H
