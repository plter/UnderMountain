//
// Created by plter on 2019/10/1.
//

#ifndef UNDERMOUNTAIN_FORMDATADECODER_H
#define UNDERMOUNTAIN_FORMDATADECODER_H

#include "FormDataValue.h"
#include <map>
#include <string>
#include <boost/regex.hpp>

namespace um {
    typedef std::map<std::string, um::FormDataValue> FormData;

    class FormDataDecoder {
    public:
        static FormData decode(const std::string &content, const std::string &boundary);

        static std::string getMatchedChild(const std::string &content, const boost::regex& regex);
    };
}


#endif //UNDERMOUNTAIN_FORMDATADECODER_H
