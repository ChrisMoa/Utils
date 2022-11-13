//
// Created by chris-tab on 15.05.21.
//

#include "CThread.h"
#include "Assert.hpp"

#ifndef DEUG
#define DEBUG(msg) ;
#endif
#ifndef INFO
#define INFO(msg) ;
#endif
#ifndef TRACE
#define TRACE(msg) ;
#endif

using namespace std;

namespace Thread
{

    CThread::~CThread()
    {
        onFinish();
        Terminate();
        delete _threadHandle;
    }

    CThread::CThread(std::string name) : threadName(name)
    {
        flagAlive = true;
        _threadHandle = new thread(&CThread::run, this);
        _threadHandle->detach();
    }

    void CThread::Execute(void)
    {
        DEBUG("I have to be overwritten");
    }

    void CThread::Resume(void)
    {
        shared_lock sl(lock);
        flagBreak = false;
        waiting.notify_one();
    }

    void CThread::Terminate(void)
    {
        shared_lock sl(lock);
        flagAlive = false;
        flagFinish = false;
        waiting.notify_all();
    }

    void CThread::WaitForThread(void)
    {
        INFO("waits for finished execution");
        unique_lock<mutex> ul(mtxWaiting);
        waiting.wait(ul, [&]
                     { onWaiting(); return flagFinish.load(); });
        onResume();
        waiting.notify_one();
    }

    void CThread::onFinish(void)
    {
        DEBUG("I have to be overwritten");
    }

    void CThread::run(void)
    {
        INFO("begins running");
        while (flagAlive)
        {
            flagFinish.store(false);
            Execute();
            flagFinish.store(true);
            this->waiting.notify_one();
            unique_lock<mutex> ul(mtxWaiting);
            INFO("waits for next execution");
            waiting.wait(ul, [&]
                         { return (!flagFinish.load()); });
            this->waiting.notify_one();
        }
        INFO("stops running");
        delete _threadHandle;
    }

    void CThread::CheckFlags(void)
    {
        if (flagBreak && flagAlive)
        {
            unique_lock<mutex> ul(mtxWaiting);
            waiting.wait(ul, [&]
                         { return flagBreak.load() && flagAlive; });
        }
        ASSERT_EXCEPTION(flagAlive, threadName + " stops running");
    }

    void CThread::Break(void)
    {
        shared_lock sl(lock);
        flagBreak = true;
    }

    void CThread::onWaiting(void)
    {
        TRACE("do on wait execution");
    }

    void CThread::addExecution(int32_t amount)
    {
    }

    void CThread::onResume(void)
    {
        TRACE("do on resume");
    }

}