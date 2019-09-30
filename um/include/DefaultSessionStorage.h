//
// Created by plter on 2019/9/29.
//

#ifndef UNDERMOUNTAIN_DEFAULTSESSIONSTORAGE_H
#define UNDERMOUNTAIN_DEFAULTSESSIONSTORAGE_H

#include <map>
#include <string>
#include "AbstractSessionStorage.h"

namespace um {
    class DefaultSessionStorage : public um::AbstractSessionStorage {
    public:
        void setSession(std::string sessionId, std::map<std::string, std::string> session) override;

        std::map<std::string, std::string> &getSession(const std::string &sessionId) override;

        std::string &getSessionValue(const std::string &sessionId, const std::string &key) override;

        void setSessionValue(std::string sessionId, std::string key, std::string value) override;

    private:
        std::map<std::string, std::map<std::string, std::string>> _sessions;
    };
}


#endif //UNDERMOUNTAIN_DEFAULTSESSIONSTORAGE_H
