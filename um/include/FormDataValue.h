//
// Created by plter on 2019/10/1.
//

#ifndef UNDERMOUNTAIN_FORMDATAVALUE_H
#define UNDERMOUNTAIN_FORMDATAVALUE_H

#include "FormDataValueItem.h"
#include <map>
#include <vector>
#include <string>

namespace um {
    class FormDataValue {

    public:
        void addItem(const um::FormDataValueItem &item);

        FormDataValueItem get(size_t position = 0);

        std::string operator*();

        [[nodiscard]] const std::vector<um::FormDataValueItem> &getItems() const;

    private:
        std::vector<um::FormDataValueItem> _items;
    };
}


#endif //UNDERMOUNTAIN_FORMDATAVALUE_H
