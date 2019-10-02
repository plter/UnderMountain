//
// Created by plter on 2019/10/1.
//

#include "../include/FormDataDecoder.h"
#include "../include/Logger.h"
#include <vector>
#include <string>
#include "../include/Dumper.h"
#include <iostream>
#include "../include/FormDataValueItem.h"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

um::FormData um::FormDataDecoder::decode(const std::string &content, const std::string &boundary) {
    std::string boundaryStartMarker = "--";
    boundaryStartMarker += boundary;

    std::cout << content << std::endl;

    size_t boundaryStartMarkerLength = boundaryStartMarker.size();
    size_t position = 0, headerEnd, bodyStart = 0;
    std::string header, body;

    FormData formData;

    while ((position = content.find(boundaryStartMarker, position)) != std::string::npos) {
        if (bodyStart > 0 && position > bodyStart) {
            body = content.substr(bodyStart, position - bodyStart);

            std::string name = getMatchedChild(header, ".* name=\"([^\"]+)\".*");
            std::string filename = getMatchedChild(header, ".* filename=\"([^\"]+)\".*");
            std::string contentType = getMatchedChild(header, ".*Content-Type: ([\\w]+/[\\w-]+).*");
            formData[name].addItem(um::FormDataValueItem(name, body, filename, contentType));
        }

        position += boundaryStartMarkerLength;
        if (content[position] == '\r' && content[position + 1] == '\n') {
            position += 2;//Skip line ending "\r\n"
            headerEnd = content.find("\r\n\r\n", position);//"\r\n\r\n" is the header ending
            if (headerEnd != std::string::npos) {
                header = content.substr(position, headerEnd - position);

                position = headerEnd;
                position += 4;//Skip the header ending "\r\n\r\n"
                bodyStart = position;
            } else {
                UM_LOG(warning) << "FormData with bad format";
            }
        } else {
            break;
        }
    }

    return formData;
}

std::string um::FormDataDecoder::getMatchedChild(const std::string &content, std::string regex) {
    boost::regex r(regex);
    boost::smatch m;
    std::string result;
    if (boost::regex_match(content, m, r)) {
        result = m[1];
    }
    return result;
}
