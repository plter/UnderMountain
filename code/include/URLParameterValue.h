//
// Created by plter on 2019/9/24.
//

#ifndef UNDERMOUNTAIN_URLPARAMETERVALUE_H
#define UNDERMOUNTAIN_URLPARAMETERVALUE_H

#include <vector>
#include <string>

namespace um {
    class URLParameterValue {

    public:
        void add(const std::string &value);

        std::string get(size_t position = 0);

        std::string operator*();

        std::string toString();

    private:
        std::vector<std::string> _values;
    };
}


#endif //UNDERMOUNTAIN_URLPARAMETERVALUE_H
