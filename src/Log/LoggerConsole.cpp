#include <Log/LoggerConsole.hpp>
#include <iostream>
#include <iomanip>

namespace Log
{
    using namespace std;

    LoggerConsole::LoggerConsole()
    {
        _level = LogEntry::Level::OFF;
    }

    LoggerConsole::~LoggerConsole()
    {
    }

    void LoggerConsole::writeToLog(const LogEntry &logEntry)
    {
        if (logEntry.level > _level) // dont write unneccessary messages to log
        {
            return;
        }

        string levelColor;
        // colorize terminal output
        switch (logEntry.level)
        {
        case LogEntry::Level::TRACE:
            levelColor = "\033[0;37m";
            break;
        case LogEntry::Level::DEBUG:
            levelColor = "\033[0;32m";
            break;
        case LogEntry::Level::INFO:
            levelColor = "\033[0;34m";
            break;
        case LogEntry::Level::WARNING:
            levelColor = "\033[1;33m";
            break;
        case LogEntry::Level::ERROR:
            levelColor = "\033[0;91m";
            break;
        case LogEntry::Level::CRITICAL:
            levelColor = "\033[1;31m";
            break;
        default:
            levelColor = "";
            break;
        }

        cout << levelColor << logEntry.level << "\t|\t"
             << levelColor << logEntry.time << "\t|\t"
             << levelColor << logEntry.location << "\t|\t"
             << levelColor << logEntry.message
             << "\033[0m" << endl;
    }
    LogEntry::Level LoggerConsole::getLogLevel()
    {
        return _level;
    }

    void LoggerConsole::setLogLevel(LogEntry::Level level)
    {
        this->_level = level;
    }

} /* namespace Log end */
