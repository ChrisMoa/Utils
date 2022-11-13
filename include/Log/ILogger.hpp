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
        virtual void writeToLog(const LogEntry &entry) = 0;
    };

} /* namespace LOG */
#endif /* end ILoggerH */