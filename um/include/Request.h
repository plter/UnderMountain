//
// Created by plter on 2019/9/18.
//

#ifndef UNDERMOUNTAIN_REQUEST_H
#define UNDERMOUNTAIN_REQUEST_H

#include "um_types.h"
#include <boost/asio/awaitable.hpp>
#include <string>
#include "URLParameterDecoder.h"
#include <map>
#include "AbstractSessionStorage.h"
#include "FormDataDecoder.h"

namespace um {

    class Server;

    class Controller;

    class FilterSession;

    class FilterControllers;

    class Request {
        friend class um::Controller;

        friend class um::Server;

        friend class um::FilterSession;

        friend class um::FilterControllers;

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

        [[nodiscard]] const FormData &getFormData() const;

        [[nodiscard]] const std::map<std::string, std::string> &getCookie() const;

        [[nodiscard]] Server *getServer() const;

        [[nodiscard]] const std::string &getSessionId() const;

        std::map<std::string, std::string> &getSession();

        std::string getSessionValue(const std::string &key);

        int getSessionValueAsInt(const std::string &key);

        int getSessionValueAsInt(const std::string &key, int defaultValue);

        std::string getSessionValue(const std::string &key, std::string defaultValue);

        void setSessionValue(const std::string &key, std::string value);

        void setSessionValue(const std::string &key, int value);

        [[nodiscard]] AbstractSessionStorageSPtr getSessionStorage() const;

        [[nodiscard]] const std::string &getControllerName() const;


        [[nodiscard]] const std::string &getActionName() const;


        void addArg(const std::string &arg);

        std::string arg(int index);

        [[nodiscard]] const std::vector<std::string> &getArgs() const;

    private:
        void setActionName(const std::string &actionName);

        void setControllerName(const std::string &controllerName);

        void setCookie(const std::map<std::string, std::string> &cookie);

        void setSessionId(const std::string &sessionId);

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
        FormData _formData;
    };

    typedef std::shared_ptr<Request> RequestSPtr;
}


#endif //UNDERMOUNTAIN_REQUEST_H
