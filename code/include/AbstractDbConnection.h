//
// Created by plter on 2019/9/28.
//

#ifndef UNDERMOUNTAIN_ABSTRACTDBCONNECTION_H
#define UNDERMOUNTAIN_ABSTRACTDBCONNECTION_H

#include <string>
#include <tuple>
#include "DbGrid.h"

namespace um {
    class AbstractDbConnection {

    public:
        virtual void connect(std::string host,
                             std::string dbName,
                             std::string user,
                             std::string password,
                             std::string charset,
                             unsigned int port) = 0;

        /**
         * @param sql
         * @return Affected rows count
         */
        virtual unsigned long executeSQL(std::string sql, DbGridSPtr &result) = 0;

        /**
         * @param sql
         * @return Affected rows count
         */
        virtual unsigned long executeSQL(std::string sql) = 0;

        virtual void close() = 0;

        virtual void autocommit(bool mode) = 0;

        virtual void commit() = 0;

        virtual void rollback() = 0;
    };
}

#endif //UNDERMOUNTAIN_ABSTRACTDBCONNECTION_H
