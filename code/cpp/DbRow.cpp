//
// Created by plter on 2019/9/28.
//

#include "../include/DbRow.h"

const std::map<std::string, std::string> &um::DbRow::getRowData() const {
    return _rowData;
}

std::string um::DbRow::get(const std::string &key) {
    return _rowData[key];
}

um::DbRow::DbRow(const std::map<std::string, std::string> &rowData) : _rowData(rowData) {}

