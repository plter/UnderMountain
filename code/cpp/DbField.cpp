//
// Created by plter on 2019/9/28.
//

#include "../include/DbField.h"

#include <utility>

um::DbField::DbField(std::string name, um::DbField::Type type, std::string table, std::string db)
        : _name(std::move(name)), _type(type), _table(std::move(table)), _db(std::move(db)) {}

const std::string &um::DbField::getName() const {
    return _name;
}

um::DbField::Type um::DbField::getType() const {
    return _type;
}

const std::string &um::DbField::getTable() const {
    return _table;
}

const std::string &um::DbField::getDb() const {
    return _db;
}
