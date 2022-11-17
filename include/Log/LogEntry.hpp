/**
 * @file LogEntry.hpp
 * @author chrismint
 * @brief contains the base information about a entry which will be written to the log output
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LogEntryH
#define LogEntryH

#include <string>

using namespace std;

namespace Log
{

    /**
     * @brief contains the base information about a entry which will be written to the log output
     *
     */
    class LogEntry
    {
    public:
        enum Level
        {
            CRITICAL = -2,
            ERROR = -1,
            WARNING = 0,
            INFO = 1,
            DEBUG = 2,
            TRACE = 3,
            OFF = 4,
        };

    public:
        LogEntry(const Level &level, const string &time, const string &location, const string &message);
        LogEntry();
        LogEntry(LogEntry &a);
        LogEntry &operator=(const LogEntry &a);
        virtual ~LogEntry();

    public:
        Level level;     //! the information importance on which the entry will be shown to user
        string time;     //! the time information
        string location; //! the information which function called the log entry
        string message;  //! the message which the user was intended to write to the log
    private:
    };

} /* namespace LOG */
#endif /* end LogEntry */
