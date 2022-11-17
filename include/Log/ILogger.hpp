/**
 * @file ILogger.hpp
 * @author chrismint
 * @brief contains the Interface where Logger can be based on
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ILoggerH
#define ILoggerH

#include <string>

#include <Log/LogEntry.hpp>

using namespace std;

namespace Log
{

    class ILogger
    {
    public:
        /**
         * @brief write the message to the log
         * @param entry the entry pattern
         * @return void
         */
        virtual void writeToLog(const LogEntry &entry) = 0;

        /**
         * @brief get the level on which the logger writes to his output
         * @return the log level
         */
        virtual LogEntry::Level getLogLevel() = 0;

        /**
         * @brief set the level on which the logger writes to his output
         * @param level the log level
         * @return void
         */
        virtual void setLogLevel(LogEntry::Level level) = 0;
    };

} /* namespace LOG */
#endif /* end ILoggerH */