//
// Created by plter on 2019/9/29.
//

#ifndef UNDERMOUNTAIN_ABSTRACTSESSIONSTORAGE_H
#define UNDERMOUNTAIN_ABSTRACTSESSIONSTORAGE_H

#include <map>
#include <string>
#include <memory>

namespace um {
    class AbstractSessionStorage {
    public:
        virtual void setSession(std::string sessionId, std::map<std::string, std::string> session) = 0;

        virtual std::map<std::string, std::string> &getSession(std::string) = 0;
    };

    typedef std::shared_ptr<AbstractSessionStorage> AbstractSessionStorageSPtr;
}

#endif //UNDERMOUNTAIN_ABSTRACTSESSIONSTORAGE_H
