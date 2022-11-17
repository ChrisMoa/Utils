/**
 * @file Logging.cpp
 * @author chrismint
 * @brief short description
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Log/Logging.hpp>
#include <algorithm>

namespace Log
{
    std::atomic<LoggerManager *> LoggerManager::_instance;
    std::mutex LoggerManager::_myMutex;

    LoggerManager::LoggerManager() : Thread::CThread("LoggerManager")
    {
        readCounter = 0;
        writeCounter = 0;
    }

    LoggerManager *LoggerManager::getInstance()
    {
        LoggerManager *sin = _instance.load();
        if (!sin)
        {
            std::lock_guard<std::mutex> myLock(_myMutex);
            sin = _instance.load();
            if (!sin)
            {
                sin = new LoggerManager();
                _instance.store(sin);
            }
        }
        return sin;
    }

    void LoggerManager::addLogMsg(LogEntry entry)
    {
        if (writeCounter.load() == _entryBuffer.size())
        {
            writeCounter.store(0);
        }
        _entryBuffer[writeCounter.load()] = entry;
        writeCounter++;
        Resume();
    }

    vector<shared_ptr<ILogger>> &LoggerManager::getLoggers()
    {
        return _loggers;
    }

    void LoggerManager::addLogger(shared_ptr<ILogger> logger)
    {
        _loggers.push_back(logger);
    }

    void LoggerManager::removeLoggerFromList(shared_ptr<ILogger> logger)
    {
        auto iter = std::find(_loggers.begin(), _loggers.end(), logger);
        if (iter != _loggers.end())
        {
            _loggers.erase(iter);
        }
    }

    void LoggerManager::Execute()
    {
        while (readCounter.load() < writeCounter.load())
        {
            for (auto logger : _loggers)
            {
                logger->writeToLog(_entryBuffer[readCounter.load()]);
                readCounter++;
            }
        }
    }

} /* namespace Log end */
