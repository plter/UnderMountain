//
// Created by plter on 2019/9/19.
//

#ifndef UNDERMOUNTAIN_RESPONSE_H
#define UNDERMOUNTAIN_RESPONSE_H

#include "um_types.h"
#include <string>
#include <sstream>
#include <boost/asio/awaitable.hpp>
#include "Request.h"
#include <boost/beast.hpp>
#include <map>
#include <any>
#include "ViewData.h"

namespace um {

    class Server;


    class Response {
        friend class um::Server;

    public:
        Response(Server *server, TcpStreamSPtr stream);

        boost::asio::awaitable<void> end(std::string data);

        boost::asio::awaitable<void> end(std::stringstream data);

        boost::asio::awaitable<void> render(std::string viewName, um::ViewData data);

        [[nodiscard]] const TcpStreamSPtr &getStream() const;

        [[nodiscard]] bool isHeaderSent() const;

        [[nodiscard]] boost::beast::http::status getHttpState() const;

        void setHttpState(boost::beast::http::status status);

        [[nodiscard]] const std::map<boost::beast::http::field, std::string> &getHeaders() const;

        void set(boost::beast::http::field key, const std::string &value);

        [[nodiscard]] const std::any &getBeastResponse() const;

        [[nodiscard]] Server *getServer() const;

        boost::asio::awaitable<void> sendFile(const std::string &filePath);

        [[nodiscard]] bool keepAlive() const;

        [[nodiscard]] unsigned int getVersion() const;

        boost::asio::awaitable<void> redirect(std::string url);

    private://private methods
        void buildMimeTypeMap();

        std::string getMimeType(std::string file);

        void setVersion(unsigned int version);

        void keepAlive(bool keepAlive);

    private:
        TcpStreamSPtr _stream;
        Server *_server;
        bool _headDataSent;// 第一批数据是否已发送
        std::any _beastResponse;
        boost::beast::http::status _httpState;
        std::map<boost::beast::http::field, std::string> _responseHeaders;
        std::map<std::string, std::string> _mimeTypeMap;
        unsigned _version;
        bool _keepAlive;
    };

    typedef std::shared_ptr<Response> ResponseSPtr;
}


#endif //UNDERMOUNTAIN_RESPONSE_H
