#include <Log/LoggerConsole.hpp>
#include <iostream>
#include <iomanip>

namespace Log
{
    using namespace std;

    LoggerConsole::LoggerConsole()
    {
    }

    LoggerConsole::~LoggerConsole()
    {
    }

    void LoggerConsole::writeToLog(const LogEntry &logEntry)
    {
        string level;
        /// colorize terminal output
        switch (logEntry.level)
        {
        case LogEntry::Level::TRACE:
            level = "\033[0;37m";
            break;
        case LogEntry::Level::DEBUG:
            level = "\033[0;32m";
            break;
        case LogEntry::Level::INFO:
            level = "\033[0;34m";
            break;
        case LogEntry::Level::WARNING:
            level = "\033[1;33m";
            break;
        case LogEntry::Level::ERROR:
            level = "\033[0;91m";
            break;
        case LogEntry::Level::CRITICAL:
            level = "\033[1;31m";
            break;
        default:
            level = "";
            break;
        }

        cout << level << logEntry.level << "\t|\t"
             << level << logEntry.time << "\t|\t"
             << level << logEntry.location << "\t|\t"
             << level << logEntry.message
             << "\033[0m" << endl;
    }

} /* namespace Log end */
