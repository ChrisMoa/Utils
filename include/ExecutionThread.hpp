#ifndef EXECUTIONTHREAD_HPP
#define EXECUTIONTHREAD_HPP

/******************************C/QT-Libs************************************************************/
#include <CThread.h>
#include <functional>
#include <queue>

/******************************own******************************************************************/
#include "Settings.hpp"

namespace Thread
{
    struct Job
    {
        std::function<void(Util::Settings &)> runCallback = nullptr;
        std::function<void(Util::Settings &)> exceptionCallback = nullptr;
        std::function<void(Util::Settings &)> finishCallback = nullptr;
        Util::Settings internalSettings;
        std::string jobName;
        const size_t retryCounterMax = 2; //! maximum amount of retrys per job
        size_t retryCounter = retryCounterMax;

        Job(std::string jobName,
            std::function<void(Util::Settings &)> runCallback);
        Job(std::string jobName,
            std::function<void(Util::Settings &)> runCallback,
            std::function<void(Util::Settings &)> exceptionCallback);
        Job(std::string jobName,
            std::function<void(Util::Settings &)> runCallback,
            std::function<void(Util::Settings &)> exceptionCallback,
            std::function<void(Util::Settings &)> finishCallback);
        ~Job();
    };

    class ExecutionThread : public CThread
    {
    public:
        ExecutionThread();
        ~ExecutionThread();

        void addJob(Job job);

    private:
        void Execute() override;

        void onException(std::string msg) override;

        void onFinish() override;

        void Terminate() override;

        std::queue<Job> jobQueue;
        std::mutex mtx;
    };
}

#endif // EXECUTIONTHREAD_HPP
