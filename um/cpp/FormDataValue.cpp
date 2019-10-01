//
// Created by plter on 2019/10/1.
//

#include "../include/FormDataValue.h"

const std::vector<um::FormDataValueItem> &um::FormDataValue::getItems() const {
    return _items;
}

void um::FormDataValue::addItem(const um::FormDataValueItem &item) {
    _items.emplace_back(item);
}

um::FormDataValueItem um::FormDataValue::get(size_t position) {
    return _items[position];
}

std::string um::FormDataValue::operator*() {
    return get(0).getBody();
}
