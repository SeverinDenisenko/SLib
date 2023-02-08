//
// Created by Severin on 02.02.2023.
//

#ifndef SLIB_SLOG_H
#define SLIB_SLOG_H

#include <string>

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

        explicit SLog(LogLevel logLevel) : logLevel(logLevel) {};
        explicit SLog() : logLevel(WARNING) {};

        void Log(LogLevel level, const std::string& msg) const;

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


#endif //SLIB_SLOG_H
