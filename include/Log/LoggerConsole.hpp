/**
 * @file LoggerConsole.hpp
 * @author chrismint
 * @brief short description
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LoggerConsoleH
#define LoggerConsoleH

#include <string>
#include <Log/ILogger.hpp>
#include <Log/LogEntry.hpp>

namespace Log
{

    /**
     * @brief short description
     *
     */
    class LoggerConsole : public ILogger
    {
    public:
        LoggerConsole();
        virtual ~LoggerConsole();

    public: /* ILogger */
        /**
         * @brief write the message to the log
         * @param entry the entry pattern
         * @return void
         */
        void writeToLog(const LogEntry &entry) override;

        /**
         * @brief get the level on which the logger writes to his output
         * @return the log level
         */
        LogEntry::Level getLogLevel() override;

        /**
         * @brief set the level on which the logger writes to his output
         * @param level the log level
         * @return void
         */
        void setLogLevel(LogEntry::Level level) override;

    private:
        LogEntry::Level _level;
    };

} /* namespace Log */
#endif /* end LoggerConsole */
