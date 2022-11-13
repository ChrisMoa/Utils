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
        void writeToLog(const LogEntry &logEntry) override;

    private:
    };

} /* namespace Log */
#endif /* end LoggerConsole */
