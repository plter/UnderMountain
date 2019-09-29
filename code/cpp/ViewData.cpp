//
// Created by plter on 2019/9/24.
//

#include "../include/ViewData.h"
#include "../include/um_types.h"

#include <utility>

void um::ViewData::set(const std::string &key, std::any value) {
    _dataMap[key] = std::move(value);
}

std::any um::ViewData::get(const std::string &key) {
    return _dataMap[key];
}

std::string um::ViewData::getString(const std::string &key) {
    auto v = get(key);
    if (v.has_value()) {
        try {
            return std::any_cast<std::string>(get(key));
        } catch (std::exception &e) {
        }
        try {
            return std::any_cast<const char *>(get(key));
        } catch (std::exception &e) {
        }
        try {
            return std::any_cast<char *>(get(key));
        } catch (std::exception &e) {
            UM_LOG(error) << "Failed to convert value by key[" << key << "] to a string";
        }
    }
    return "";
}

int32_t um::ViewData::getInt(const std::string &key) {
    auto v = get(key);
    if (v.has_value()) {
        return std::any_cast<int32_t>(get(key));
    }
    return 0;
}

um::ViewData::ViewData() = default;

um::ViewData::ViewData(um::DataContainer kvs) {
    _dataMap = std::move(kvs);
}
