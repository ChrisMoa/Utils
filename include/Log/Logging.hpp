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
#include <array>

#ifndef LOG_BUFFER
#define LOG_BUFFER 10000
#endif
#define LOG_USE_THREAD
#ifdef LOG_USE_THREAD
#include <CThread.h>
#include <mutex>
#include <atomic>
#endif

#define ENTER() Log::LoggerManager::getInstance()->addLogMsg(Log::LogEntry(Log::LogEntry::Level::TRACE, "", __PRETTY_FUNCTION__, "Enter"))      //< just for finding out function name -> at beginning of function
#define LEAVE() Log::LoggerManager::getInstance()->addLogMsg(Log::LogEntry(Log::LogEntry::Level::TRACE, "", __PRETTY_FUNCTION__, "Leave"))      //< just for finding out function name -> at end of function
#define TRACE(MSG) Log::LoggerManager::getInstance()->addLogMsg(Log::LogEntry(Log::LogEntry::Level::TRACE, "", __PRETTY_FUNCTION__, MSG))       //< lowest log level -> write entry as trace level
#define DEBUG(MSG) Log::LoggerManager::getInstance()->addLogMsg(Log::LogEntry(Log::LogEntry::Level::DEBUG, "", __PRETTY_FUNCTION__, MSG))       //< write entry as debug level
#define LINFO(MSG) Log::LoggerManager::getInstance()->addLogMsg(Log::LogEntry(Log::LogEntry::Level::INFO, "", __PRETTY_FUNCTION__, MSG))        //< write entry as info level
#define WARNING(MSG) Log::LoggerManager::getInstance()->addLogMsg(Log::LogEntry(Log::LogEntry::Level::WARNING, "", __PRETTY_FUNCTION__, MSG))   //< write entry as warning level
#define ERROR(MSG) Log::LoggerManager::getInstance()->addLogMsg(Log::LogEntry(Log::LogEntry::Level::ERROR, "", __PRETTY_FUNCTION__, MSG))       //< write entry as error level
#define CRITICAL(MSG) Log::LoggerManager::getInstance()->addLogMsg(Log::LogEntry(Log::LogEntry::Level::CRITICAL, "", __PRETTY_FUNCTION__, MSG)) //< write entry as critical level and throw exception with <msg>

namespace Log
{

    class LoggerManager : public Thread::CThread
    {
    public:
        /**
         * @brief get the instance of the logger
         * @return the logger instance
         */
        static LoggerManager *getInstance();

        /*Logger specific ************************************************************************/

        /**
         * @brief add a new log entry to the loggermanager
         * @param entry the lot entry
         * @return void
         */
        void addLogMsg(LogEntry entry);

        /**
         * @brief get all active logger objects
         * @return all active logger objects
         */
        vector<shared_ptr<ILogger>> &getLoggers();

        /**
         * @brief appends the logger object to the output list
         * @param logger the logger object
         * @return void
         */
        void addLogger(shared_ptr<ILogger> logger);

        /**
         * @brief removes the logger object from the list if $logger is included in the list
         * @param logger the logger pattern
         * @return void
         */
        void removeLoggerFromList(shared_ptr<ILogger> logger);

    private:
        /*Singleton ******************************************************************************/

        /*
         * all constructors and destructors should be deleted
         */

        LoggerManager();
        ~LoggerManager() = default;
        LoggerManager(const LoggerManager &) = delete;
        LoggerManager &operator=(const LoggerManager &) = delete;
        static std::atomic<LoggerManager *> _instance; //! the Logger Singleton instance
        static std::mutex _myMutex;                    //! the mutex to lock the threadsafe getInstance call

        /*CThread Methods*************************************************************************/

        void Execute() override;

        /*own methods and parameters**************************************************************/

        vector<shared_ptr<ILogger>> _loggers;          //! the container for all logger
        std::array<LogEntry, LOG_BUFFER> _entryBuffer; //! stores all entries which should be write to log
        std::atomic<size_t> readCounter;               //! counts the logEntries which were read in the log thread
        std::atomic<size_t> writeCounter;              //! counts the logEntries which were valid in the buffer after adding a entry
    };

}

#endif /* end Logging */
