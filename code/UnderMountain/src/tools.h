//
// Created by yunp on 2019-05-12.
//

#ifndef UNDERMOUNTAIN_TOOLS_H
#define UNDERMOUNTAIN_TOOLS_H


#include <boost/beast/core.hpp>

namespace beast = boost::beast;

// Report a failure
void
fail(beast::error_code ec, char const *what);

std::string
path_cat(beast::string_view base,
         beast::string_view path);

#endif //UNDERMOUNTAIN_TOOLS_H
