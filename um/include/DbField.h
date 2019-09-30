//
// Created by plter on 2019/9/28.
//

#ifndef UNDERMOUNTAIN_DBFIELD_H
#define UNDERMOUNTAIN_DBFIELD_H

#include <string>

namespace um {
    class DbField {

    public:
        enum Type {
            STRING,
            DATE, TIME, YEAR, NEWDATE, TIMESTAMP, DATETIME,
            NUMBER,
            TYPE_NULL,
            INTEGER
        };

    public:
        DbField(std::string name, Type type, std::string table, std::string db);

        [[nodiscard]] const std::string &getName() const;

        [[nodiscard]] Type getType() const;

        [[nodiscard]] const std::string &getTable() const;

        [[nodiscard]] const std::string &getDb() const;

    private:
        std::string _name;
        Type _type;
        std::string _table;
        std::string _db;
    };
}


#endif //UNDERMOUNTAIN_DBFIELD_H
