//
// Created by plter on 2019/9/28.
//

#include "../include/DbGrid.h"

#include <utility>

um::DbGrid::DbGrid() {}

um::DbGrid::DbGrid(std::vector<um::DbField> fields, std::vector<um::DbRow> rows) :
        _fields(std::move(fields)),
        _rows(std::move(rows)) {}

const std::vector<um::DbField> &um::DbGrid::getFields() const {
    return _fields;
}

const std::vector<um::DbRow> &um::DbGrid::getRows() const {
    return _rows;
}

size_t um::DbGrid::count() {
    return _rows.size();
}

std::string um::DbGrid::toString() {
    std::string str;
    for (auto &f:_fields) {
        str += f.getName();
        str += "\t";
    }
    str += "\n";

    for (auto &r:_rows) {
        for (auto &[k, v]:r.getRowData()) {
            str += v;
            str += "\t";
        }
        str += "\n";
    }
    return str;
}
