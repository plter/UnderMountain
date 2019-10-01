//
// Created by plter on 2019/9/18.
//

#ifndef UNDERMOUNTAIN_REQUEST_H
#define UNDERMOUNTAIN_REQUEST_H

#include "um_types.h"
#include <boost/asio/awaitable.hpp>
#include <string>
#include "URLParameters.h"
#include <map>
#include "AbstractSessionStorage.h"

namespace um {

    class Server;

    class Request {
    public:
        Request(um::Server *server, TcpStreamSPtr stream);

        boost::asio::awaitable<void> asyncInit();

    public:
        [[nodiscard]] const TcpStreamSPtr &getStream() const;

        [[nodiscard]] const BeastHttpStringBodyRequest &getBeastRequest() const;

        [[nodiscard]] const std::string &getTarget() const;

        [[nodiscard]] boost::beast::http::verb getMethod() const;

        [[nodiscard]] const std::string &getRequestPath() const;

        [[nodiscard]] const std::string &getQuery() const;

        [[nodiscard]] const std::string &getBody() const;

        [[nodiscard]] const URLParameterPairs &getPostVars() const;

        [[nodiscard]] const URLParameterPairs &getGetVars() const;

        [[nodiscard]] const std::map<std::string, std::string> &getCookie() const;

        void setCookie(const std::map<std::string, std::string> &cookie);

        [[nodiscard]] Server *getServer() const;

        [[nodiscard]] const std::string &getSessionId() const;

        void setSessionId(const std::string &sessionId);

        std::map<std::string, std::string> &getSession();

        std::string getSessionValue(const std::string &key);

        int getSessionValueAsInt(const std::string &key);

        int getSessionValueAsInt(const std::string &key, int defaultValue);

        std::string getSessionValue(const std::string &key, std::string defaultValue);

        void setSessionValue(const std::string &key, std::string value);

        void setSessionValue(const std::string &key, int value);

        AbstractSessionStorageSPtr getSessionStorage() const;

        const std::string &getControllerName() const;

        void setControllerName(const std::string &controllerName);

        [[nodiscard]] const std::string &getActionName() const;

        void setActionName(const std::string &actionName);

        void addArg(std::string arg);

        std::string arg(int index);

        const std::vector<std::string> &getArgs() const;

    private:
        TcpStreamSPtr _stream;
        BeastHttpStringBodyRequest _beastRequest;
        std::string _target;
        std::string _requestPath;
        std::string _query;
        boost::beast::http::verb _method;
        std::string _body;
        std::string _contentType;
        URLParameterPairs _postVars;
        URLParameterPairs _getVars;
        std::map<std::string, std::string> _cookie;
        um::Server *_server;
        std::string _sessionId;
        std::string _controllerName;
        std::string _actionName;
        std::vector<std::string> _args;
    };

    typedef std::shared_ptr<Request> RequestSPtr;
}


#endif //UNDERMOUNTAIN_REQUEST_H
