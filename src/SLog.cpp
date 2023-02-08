//
// Created by Severin on 02.02.2023.
//

#include "SLib/SLog.h"

#include <iostream>

namespace slib {
    void SLog::Log(SLog::LogLevel level, const std::string& msg) const {

        const char * levelStrings[5] = {"[FATAL]: ", "[ERROR]: ", "[WARNING]: ", "[INFO]: ", "[TRACE]: "};

        if(level > logLevel)
            return;

        if (level == LogLevel::FATAL || level == LogLevel::ERROR)
            std::cerr << levelStrings[level] << msg << std::endl;
        else
            std::cout << levelStrings[level] << msg << std::endl;
    }
} // slib