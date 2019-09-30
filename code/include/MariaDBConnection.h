//
// Created by plter on 2019/9/29.
//

#ifndef UNDERMOUNTAIN_MARIADBCONNECTION_H
#define UNDERMOUNTAIN_MARIADBCONNECTION_H

#include <um.h>
#include <mysql.h>
#include <sstream>
#include <exception>
#include <utility>

namespace um {
    class MariaDBConnection : public um::AbstractDbConnection {

        struct DBException : std::exception {
            explicit DBException(std::string errorMsg) {
                _errorMsg = std::move(errorMsg);
            }

            [[nodiscard]] const char *what() const noexcept override { return _errorMsg.c_str(); }

        private:
            std::string _errorMsg;
        };

    public:
        MariaDBConnection() : _connected(false) {
            _mysql = mysql_init(nullptr);
        }

        virtual ~MariaDBConnection() {
            close();
        }

        void
        connect(std::string host, std::string dbName, std::string user, std::string password, std::string charset,
                unsigned int port) override {
            if (!mysql_real_connect(_mysql, host.c_str(), user.c_str(), password.c_str(), dbName.c_str(), port, nullptr,
                                    0)) {

                std::string errorMsg = getCurrentErrorMessage();
                close();
                throw DBException(errorMsg);
            }
            mysql_set_character_set(_mysql, charset.c_str());

            _connected = true;
        }

        unsigned long executeSQL(std::string sql, DbGridSPtr &result) override {
            if (mysql_real_query(_mysql, sql.c_str(), sql.size())) {
                throw DBException(getCurrentErrorMessage());
            }
            MYSQL_RES *mysqlResult = mysql_store_result(_mysql);
            if (mysqlResult) {

                //fetch fields
                std::vector<um::DbField> dbFields;
                MYSQL_FIELD *field;
                while ((field = mysql_fetch_field(mysqlResult))) {
                    DbField::Type type;
                    switch (field->type) {
                        case MYSQL_TYPE_VAR_STRING:
                        case MYSQL_TYPE_BLOB:
                        case MYSQL_TYPE_VARCHAR:
                            type = DbField::Type::STRING;
                            break;
                        case MYSQL_TYPE_TINY:
                        case MYSQL_TYPE_SHORT:
                        case MYSQL_TYPE_LONG:
                        case MYSQL_TYPE_LONGLONG:
                        case MYSQL_TYPE_INT24:
                        case MYSQL_TYPE_BIT:
                            type = DbField::Type::INTEGER;
                            break;
                        case MYSQL_TYPE_DECIMAL:
                        case MYSQL_TYPE_FLOAT:
                        case MYSQL_TYPE_DOUBLE:
                            type = DbField::Type::NUMBER;
                            break;
                        case MYSQL_TYPE_NULL:
                            type = DbField::Type::TYPE_NULL;
                            break;
                        case MYSQL_TYPE_TIMESTAMP:
                            type = DbField::Type::TIMESTAMP;
                            break;
                        case MYSQL_TYPE_DATE:
                            type = DbField::Type::DATE;
                            break;
                        case MYSQL_TYPE_TIME:
                            type = DbField::Type::TIME;
                            break;
                        case MYSQL_TYPE_DATETIME:
                            type = DbField::Type::DATETIME;
                            break;
                        case MYSQL_TYPE_YEAR:
                            type = DbField::Type::YEAR;
                            break;
                        case MYSQL_TYPE_NEWDATE:
                            type = DbField::Type::NEWDATE;
                            break;
                        default:
                            type = DbField::Type::STRING;
                            break;
                    }
                    dbFields.emplace_back(field->name, type, field->table, field->db);
                }

                //fetch rows
                std::vector<um::DbRow> dbRows;
                MYSQL_ROW mysql_row;
                auto columns = dbFields.size();
                while ((mysql_row = mysql_fetch_row(mysqlResult))) {
                    std::map<std::string, std::string> dbRowData;
                    for (auto i = 0UL; i < columns; ++i) {
                        auto dbField = dbFields[i];
                        dbRowData[dbField.getName()] = mysql_row[i];
                    }
                    dbRows.emplace_back(um::DbRow(dbRowData));
                }
                result = std::make_shared<um::DbGrid>(dbFields, dbRows);

                mysql_free_result(mysqlResult);
                return mysql_affected_rows(_mysql);
            } else {
                throw DBException("Can not get query result");
            }
        }

        unsigned long executeSQL(std::string sql) override {
            if (mysql_real_query(_mysql, sql.c_str(), sql.size())) {
                throw DBException(getCurrentErrorMessage());
            }
            return mysql_affected_rows(_mysql);
        }

        void autocommit(bool mode) override {
            mysql_autocommit(_mysql, mode);
        }

        void commit() override {
            mysql_commit(_mysql);
        }

        void rollback() override {
            mysql_rollback(_mysql);
        }

        void close() override {
            if (!_connected) {
                mysql_close(_mysql);
            }
            _connected = false;
        }

    private:
        std::string getCurrentErrorMessage() {
            std::stringstream errorMsg;
            errorMsg << "Error(" << mysql_errno(_mysql) << ") [" << mysql_sqlstate(_mysql) << "] \""
                     << mysql_error(_mysql) << "\"";
            return errorMsg.str();
        }

    private:
        MYSQL *_mysql;
        bool _connected;
    };
}


#endif //UNDERMOUNTAIN_MARIADBCONNECTION_H
