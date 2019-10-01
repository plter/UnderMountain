//
// Created by plter on 2019/10/1.
//

#ifndef UNDERMOUNTAIN_LOGGER_H
#define UNDERMOUNTAIN_LOGGER_H

#include <string>
#include <boost/log/trivial.hpp>

namespace um {
    class Logger {
    public:
        static std::string getFilename(std::string pathString);
    };
}


#define UM_LOG(level) BOOST_LOG_TRIVIAL(level) << um::Logger::getFilename(__FILE__) << "(" << __LINE__ << ") "

#endif //UNDERMOUNTAIN_LOGGER_H
