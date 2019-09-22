//
// Created by plter on 2019/9/22.
//

#include <iostream>
#include "../include/FilterStaticFiles.h"
#include "../include/um_types.h"
#include "../include/Server.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

boost::asio::awaitable<void> um::FilterStaticFiles::run(um::RequestSPtr req, um::ResponseSPtr res) {

    std::string file;
    file += res->getServer()->getStaticRoot();
    file += req->getRequestPath();
    if (file.back() == '/') {
        file += "index.html";
    }

    if (boost::filesystem::exists(file) && boost::filesystem::is_regular_file(file)) {
        co_await
        res->sendFile(file);
    }
}
