#include <Log/LogEntry.hpp>

namespace Log
{

    LogEntry::LogEntry(const Level &level, const string &time, const string &location, const string &message)
        : level(level), time(time), location(location), message(message)
    {
        ;
    }

    LogEntry::LogEntry()
        : level(Level::OFF), time(""), location(""), message("")
    {
        ;
    }

    LogEntry::LogEntry(LogEntry &a) : level(a.level), time(a.time), location(a.location), message(a.message)
    {
    }

    LogEntry &LogEntry::operator=(const LogEntry &a)
    {
        level = a.level;
        time = a.time;
        location = a.location;
        message = a.message;
        return *this;
    }

    LogEntry::~LogEntry()
    {
        ;
    }

}
