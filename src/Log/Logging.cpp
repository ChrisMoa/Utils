/**
 * @file Logging.cpp
 * @author chrismint
 * @brief short description
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Log/Logging.hpp>

namespace Log
{
    using namespace std;

    static vector<shared_ptr<ILogger>> _loggers;
    static int _level = 2;

    vector<shared_ptr<ILogger>> &getLoggers()
    {
        return _loggers;
    }

    void addLogger(shared_ptr<ILogger> logger)
    {
        _loggers.push_back(logger);
    }

    int &getLogLevel()
    {
        return _level;
    }

    void setLogLevel(int level)
    {
        _level = level;
    }

    void trace(const string &msg, const string &location)
    {
        CHECK_LEVEL(LogEntry::Level::TRACE);
        string timeStamp = __TIME__;
        for (auto logger : getLoggers())
        {
            logger->writeToLog(LogEntry(LogEntry::Level::TRACE, timeStamp, location, msg));
        }
    }

    void debug(const string &msg, const string &location)
    {
        // CHECK_LEVEL(LogEntry::Level::DEBUG);
        string timeStamp = __TIME__;
        for (auto &logger : getLoggers())
        {
            logger->writeToLog(LogEntry(LogEntry::Level::DEBUG, timeStamp, location, msg));
        }
    }

    void info(const string &msg, const string &location)
    {
        CHECK_LEVEL(LogEntry::Level::INFO);
        string timeStamp = __TIME__;
        for (auto logger : getLoggers())
        {
            logger->writeToLog(LogEntry(LogEntry::Level::INFO, timeStamp, location, msg));
        }
    }

    void warning(const string &msg, const string &location)
    {
        CHECK_LEVEL(LogEntry::Level::WARNING);
        string timeStamp = __TIME__;
        for (auto logger : getLoggers())
        {
            logger->writeToLog(LogEntry(LogEntry::Level::WARNING, timeStamp, location, msg));
        }
    }

    void error(const string &msg, const string &location)
    {
        CHECK_LEVEL(LogEntry::Level::ERROR);
        string timeStamp = __TIME__;
        for (auto logger : getLoggers())
        {
            logger->writeToLog(LogEntry(LogEntry::Level::ERROR, timeStamp, location, msg));
        }
    }

    void critical(const string &msg, const string &location)
    {
        CHECK_LEVEL(LogEntry::Level::CRITICAL);
        string timeStamp = __TIME__;
        for (auto logger : getLoggers())
        {
            logger->writeToLog(LogEntry(LogEntry::Level::CRITICAL, timeStamp, location, msg));
        }
        throw msg;
    }

} /* namespace Log end */
