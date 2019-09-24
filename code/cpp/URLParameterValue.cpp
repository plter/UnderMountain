//
// Created by plter on 2019/9/24.
//

#include "../include/URLParameterValue.h"

void um::URLParameterValue::add(const std::string &value) {
    _values.push_back(value);
}

std::string um::URLParameterValue::get(size_t position) {
    return _values[position];
}

std::string um::URLParameterValue::operator*() {
    return get(0);
}

std::string um::URLParameterValue::toString() {
    std::string result = "[";
    for (auto &v:_values) {
        result += v;
        result += ",";
    }
    result = result.substr(0, result.size() - 1);
    result += "]";
    return result;
}
