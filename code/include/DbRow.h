//
// Created by plter on 2019/9/28.
//

#ifndef UNDERMOUNTAIN_DBROW_H
#define UNDERMOUNTAIN_DBROW_H


#include <map>
#include <string>

namespace um {
    class DbRow {
    public:
        DbRow(const std::map<std::string, std::string> &rowData);

        [[nodiscard]] const std::map<std::string, std::string> &getRowData() const;
        std::string get(const std::string& key);

    private:
        std::map<std::string, std::string> _rowData;
    };
}


#endif //UNDERMOUNTAIN_DBROW_H
