//
// Created by plter on 2019/9/28.
//

#ifndef UNDERMOUNTAIN_DBGRID_H
#define UNDERMOUNTAIN_DBGRID_H

#include <vector>
#include "DbField.h"
#include "DbRow.h"

namespace um {
    class DbGrid {
    public:
        DbGrid();

        DbGrid(std::vector<um::DbField> fields, std::vector<um::DbRow> rows);

        [[nodiscard]] const std::vector<DbField> &getFields() const;

        [[nodiscard]] const std::vector<um::DbRow> &getRows() const;

        size_t count();

        std::string toString();

    private:
        std::vector<um::DbField> _fields;
        std::vector<um::DbRow> _rows;
    };

    typedef std::shared_ptr<DbGrid> DbGridSPtr;
}


#endif //UNDERMOUNTAIN_DBGRID_H
