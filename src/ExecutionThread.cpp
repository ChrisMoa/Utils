#include "ExecutionThread.hpp"
#include "Logging.hpp"
#include <FileSystemUtils.h>

namespace Thread
{
    ExecutionThread::ExecutionThread() : CThread("ExecutionThread")
    {
    }

    ExecutionThread::~ExecutionThread()
    {
    }

    void ExecutionThread::addJob(Job job)
    {
        {
            std::lock_guard<std::mutex>(this->mtx);
            jobQueue.push(job);
        }
        Begin();
    }

    void ExecutionThread::Terminate()
    {
        CThread::Terminate();
    }

    void ExecutionThread::Execute()
    {
        auto queueEmpty = [&]()
        {
            std::lock_guard<std::mutex>(this->mtx);
            return jobQueue.empty();
        };

        while (!queueEmpty())
        {
            // get first job
            mtx.lock();
            auto jb = jobQueue.front();
            if (!jb.retryCounter)
            {
                jobQueue.pop();
                LINFO("there are {} jobs left", jobQueue.size());
                continue;
            }
            mtx.unlock();
            // execute job
            LTRACE("executes \"{} \"", jb.jobName);
            jb.runCallback(jb.internalSettings);
            LTRACE("finished \"{} \"", jb.jobName);
            if (jb.finishCallback)
            {
                jb.finishCallback(jb.internalSettings);
            }
            {
                std::lock_guard<std::mutex>(this->mtx);
                jobQueue.pop();
                LINFO("there are {} jobs left", jobQueue.size());
            }
        }
    }

    void ExecutionThread::onException(std::string msg)
    {
        {
            std::lock_guard<std::mutex>(this->mtx);
            auto jb = jobQueue.front();
            jb.internalSettings.set("ErrorMsg", msg);
            jb.internalSettings.set("ErrorJobName", jb.jobName);
            jb.internalSettings.set("retryCounter", jb.retryCounter);
            jb.exceptionCallback(jb.internalSettings);
            if (jb.retryCounter)
            {
                jb.retryCounter--;
            }
        }
    }

    void ExecutionThread::onFinish()
    {
        LINFO("finished executing job list");
    }

    Job::Job(std::string jobName, std::function<void(Util::Settings &)> runCallback)
        : jobName(jobName), runCallback(runCallback)
    {
    }

    Job::Job(std::string jobName, std::function<void(Util::Settings &)> runCallback, std::function<void(Util::Settings &)> exceptionCallback)
        : jobName(jobName), runCallback(runCallback), exceptionCallback(exceptionCallback)
    {
    }

    Job::Job(std::string jobName, std::function<void(Util::Settings &)> runCallback, std::function<void(Util::Settings &)> exceptionCallback, std::function<void(Util::Settings &)> finishCallback)
        : jobName(jobName), runCallback(runCallback), exceptionCallback(exceptionCallback), finishCallback(finishCallback)
    {
    }

    Job::~Job()
    {
    }

}
