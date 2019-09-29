//
// Created by plter on 2019/9/29.
//

#include "../include/DefaultSessionStorage.h"

void um::DefaultSessionStorage::setSession(std::string sessionId, std::map<std::string, std::string> session) {
    _sessions[sessionId] = session;
}

std::map<std::string, std::string> &um::DefaultSessionStorage::getSession(std::string sessionId) {
    return _sessions[sessionId];
}
