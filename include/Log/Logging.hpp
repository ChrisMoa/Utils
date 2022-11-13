/**
 * @file Logging.hpp
 * @author chrismint
 * @brief short description
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LoggingH
#define LoggingH

#include <mutex>
#include <vector>

#include <Log/LogEntry.hpp>
#include <Log/ILogger.hpp>
#include <memory>
#include <exception>

#define CHECK_LEVEL(LEVEL)                                        \
    if (!Log::getLoggers().size() || Log::getLogLevel() <= LEVEL) \
    {                                                             \
        return;                                                   \
    }

#if defined(__BORLANDC__) && !defined(__clang__)
#if (__BORLANDC__ > 0x564)
#define __PRETTY_FUNCTION__ __FUNCTION__
#else
#define __PRETTY_FUNCTION__ __FUNC__
#endif
#endif

#define ENTER() Log::trace("", __PRETTY_FUNCTION__);           //< just for finding out function name -> at beginning of function
#define LEAVE() Log::trace("", __PRETTY_FUNCTION__);           //< just for finding out function name -> at end of function
#define TRACE(MSG) Log::trace(MSG, __PRETTY_FUNCTION__);       //< lowest log level -> write entry as trace level
#define DEBUG(MSG) Log::debug(MSG, __PRETTY_FUNCTION__);       //< write entry as debug level
#define INFO(MSG) Log::info(MSG, __PRETTY_FUNCTION__);         //< write entry as info level
#define WARNING(MSG) Log::warning(MSG, __PRETTY_FUNCTION__);   //< write entry as warning level
#define ERROR(MSG) Log::error(MSG, __PRETTY_FUNCTION__);       //< write entry as error level
#define CRITICAL(MSG) Log::critical(MSG, __PRETTY_FUNCTION__); //< write entry as critical level and throw exception with <msg>

namespace Log
{

    /**
     * @brief Get the Loggers object
     *
     * @return vector<shared_ptr<ILogger>>&
     */
    extern vector<shared_ptr<ILogger>> &getLoggers();

    /**
     * @brief appends the logger object to the output list
     *
     * @param logger the logger object
     */
    extern void addLogger(shared_ptr<ILogger> logger);

    /**
     * @brief Get the Log Level object
     *
     * @return int&
     */
    extern int &getLogLevel();

    /**
     * @brief set the level on which the ouput will be written to the log
     * @note the lower the level, the less information will be written to the output. E.g. TRACE have all levels, CRITICAL only itself
     *
     * @param level the new level on which will be written
     */
    extern void setLogLevel(int level);

    extern void trace(const string &msg, const string &location);

    extern void debug(const string &msg, const string &location);

    extern void info(const string &msg, const string &location);

    extern void warning(const string &msg, const string &location);

    extern void error(const string &msg, const string &location);

    extern void critical(const string &msg, const string &location);

}

#endif /* end Logging */
