//
// Created by Severin on 02.02.2023.
//

#ifndef SLIB_SLOG_HPP
#define SLIB_SLOG_HPP

#include <string>
#include <iostream>

namespace slib {

    class SLog {
    public:
        enum LogLevel{
            FATAL = 0,
            ERROR = 1,
            WARNING = 2,
            INFO =  3,
            TRACE = 4
        };

        explicit SLog(LogLevel logLevel) noexcept : logLevel(logLevel) {};
        explicit SLog() noexcept : logLevel(WARNING) {};

        template<typename T>
        void Log(SLog::LogLevel level, const T& msg) const {

            const char * levelStrings[5] = {"[FATAL]: ", "[ERROR]: ", "[WARNING]: ", "[INFO]: ", "[TRACE]: "};

            if(level > logLevel)
                return;

            if (level == LogLevel::FATAL || level == LogLevel::ERROR)
                std::cerr << levelStrings[level] << msg << std::endl;
            else
                std::cout << levelStrings[level] << msg << std::endl;
        }

        LogLevel logLevel;
    };

    inline SLog slog;
} // slib

#define S_FATAL(msg) slib::slog.Log(slib::SLog::FATAL, msg)
#define S_ERROR(msg) slib::slog.Log(slib::SLog::ERROR, msg)
#define S_WARNING(msg) slib::slog.Log(slib::SLog::WARNING, msg)
#define S_INFO(msg) slib::slog.Log(slib::SLog::INFO, msg)
#define S_TRACE(msg) slib::slog.Log(slib::SLog::TRACE, msg)

#define S_LOG_LEVEL_FATAL slib::slog.logLevel = slib::SLog::FATAL
#define S_LOG_LEVEL_ERROR slib::slog.logLevel = slib::SLog::ERROR
#define S_LOG_LEVEL_WARNING slib::slog.logLevel = slib::SLog::WARNING
#define S_LOG_LEVEL_INFO slib::slog.logLevel = slib::SLog::INFO
#define S_LOG_LEVEL_TRACE slib::slog.logLevel = slib::SLog::TRACE


#endif //SLIB_SLOG_HPP
