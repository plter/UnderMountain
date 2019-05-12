//
// Created by yunp on 2019-05-12.
//

#ifndef UNDERMOUNTAIN_MIME_TYPES_H
#define UNDERMOUNTAIN_MIME_TYPES_H

#include <boost/beast/core.hpp>

namespace beast = boost::beast;

// Return a reasonable mime type based on the extension of a file.
beast::string_view
mime_type(beast::string_view path);

#endif //UNDERMOUNTAIN_MIME_TYPES_H
