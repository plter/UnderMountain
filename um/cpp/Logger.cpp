//
// Created by plter on 2019/10/1.
//

#include "../include/Logger.h"
#include <boost/filesystem.hpp>

std::string um::Logger::getFilename(std::string pathString) {
    boost::filesystem::path p(pathString);
    return p.filename().string();
}
