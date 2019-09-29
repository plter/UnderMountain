//
// Created by plter on 2019/9/29.
//

#include "../include/DefaultSessionStorage.h"

void um::DefaultSessionStorage::setSession(std::string sessionId, std::map<std::string, std::string> session) {
    _sessions[sessionId] = session;
}

std::map<std::string, std::string> &um::DefaultSessionStorage::getSession(const std::string &sessionId) {
    return _sessions[sessionId];
}

std::string &um::DefaultSessionStorage::getSessionValue(const std::string &sessionId, const std::string &key) {
    return _sessions[sessionId][key];
}

void um::DefaultSessionStorage::setSessionValue(std::string sessionId, std::string key, std::string value) {
    _sessions[sessionId][key] = value;
}
