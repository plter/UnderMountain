//
// Created by plter on 2019/9/24.
//

#ifndef UNDERMOUNTAIN_VIEWDATA_H
#define UNDERMOUNTAIN_VIEWDATA_H

#include <map>
#include <string>
#include <any>
#include <cstdint>
#include <iostream>
#include <vector>

namespace um {
    typedef std::map<std::string, std::any> DataContainer;

    class ViewData {

    private:
        DataContainer _dataMap;

    public:
        explicit ViewData(DataContainer kvs);

        ViewData();

        void set(const std::string &key, std::any value);

        std::any get(const std::string &key);

        std::string getString(const std::string &key);

        int32_t getInt(const std::string &key);
    };
}


#endif //UNDERMOUNTAIN_VIEWDATA_H
