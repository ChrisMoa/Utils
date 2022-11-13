#include <Log/LogEntry.hpp>

namespace Log
{

    LogEntry::LogEntry(const Level &level, const string &time, const string &location, const string &message)
        : level(level), time(time), location(location), message(message)
    {
        ;
    }

    LogEntry::~LogEntry()
    {
        ;
    }

}
