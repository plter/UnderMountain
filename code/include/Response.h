//
// Created by plter on 2019/9/19.
//

#ifndef UNDERMOUNTAIN_RESPONSE_H
#define UNDERMOUNTAIN_RESPONSE_H

#include "um_types.h"
#include <string>
#include <boost/asio/awaitable.hpp>
#include "Request.h"
#include <boost/beast.hpp>
#include <map>
#include <any>

namespace um {

    class Server;

    class Response {
    public:
        Response(Server *server, TcpStreamSPtr stream, RequestSPtr request);

        boost::asio::awaitable<void> end(std::string data);

        boost::asio::awaitable<void> render(std::string viewName, std::map<std::string, std::any> data);


    public:
        [[nodiscard]] const TcpStreamSPtr &getStream() const;

        [[nodiscard]] bool isHeaderSent() const;

        [[nodiscard]] boost::beast::http::status getHttpState() const;

        void setHttpState(boost::beast::http::status status);

        [[nodiscard]] const std::map<boost::beast::http::field, std::string> &getHeaders() const;

        void set(boost::beast::http::field key, const std::string &value);

        [[nodiscard]] const std::any &getBeastResponse() const;

        [[nodiscard]] Server *getServer() const;

        boost::asio::awaitable<void> sendFile(const std::string &filePath);

    private://private methods
        void buildMimeTypeMap();
        std::string getMimeType(std::string file);

    private:
        TcpStreamSPtr _stream;
        RequestSPtr _request;
        Server *_server;
        bool _headDataSent;// 第一批数据是否已发送
        std::any _beastResponse;
        boost::beast::http::status _httpState;
        std::map<boost::beast::http::field, std::string> _responseHeaders;
        std::map<std::string, std::string> _mimeTypeMap;
    };

    typedef std::shared_ptr<Response> ResponseSPtr;
}


#endif //UNDERMOUNTAIN_RESPONSE_H
