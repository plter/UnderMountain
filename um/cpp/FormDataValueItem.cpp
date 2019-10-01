//
// Created by plter on 2019/10/1.
//

#include "../include/FormDataValueItem.h"

#include <utility>

const std::string &um::FormDataValueItem::getName() const {
    return _name;
}

const std::string &um::FormDataValueItem::getFilename() const {
    return _filename;
}

const std::string &um::FormDataValueItem::getBody() const {
    return _body;
}

um::FormDataValueItem::FormDataValueItem(
        std::string name, std::string body, std::string filename
) : _name(std::move(name)),
    _body(std::move(body)),
    _filename(std::move(filename)) {}

