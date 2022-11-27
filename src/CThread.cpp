//
// Created by chris-tab on 15.05.21.
//

#include "CThread.h"
#include "Assert.hpp"
#include <Logging.hpp>
#include <exception>
#include <FileSystemUtils.h>

using namespace std;

namespace Thread
{

  CThread::~CThread()
  {
    LTRACE(threadName + " starts to be destroyed");
    Terminate();
  }

  CThread::CThread(std::string name) : threadName(name)
  {
    flagAlive = true;
    flagBegin = false;
    flagFinish = true;
    _threadHandle = new thread(&CThread::run, this);
    _threadHandle->detach();
  }

  CThread::CThread(Thread::CThread &a) {}
  CThread &CThread::operator=(const Thread::CThread &a) { return *this; }

  std::string CThread::getThreadName() { return threadName; }

  void CThread::Resume(void)
  {
    LTRACE(threadName + " resumes");
    shared_lock sl(lock);
    flagBreak = false;
    waiting.notify_all();
  }

  void CThread::Begin(void)
  {
    if (!flagFinish)
    {
      return;
    }
    LTRACE(threadName + " begins");
    shared_lock sl(lock);
    flagBegin = true && flagFinish;
    begin.notify_all();
  }

  void CThread::Break(void)
  {
    LTRACE(threadName + " will take a break");
    shared_lock sl(lock);
    flagBreak = true;
  }

  void CThread::Terminate(void)
  {
    LTRACE(threadName + " will be terminated");
    shared_lock sl(lock);
    flagAlive = false;
    flagFinish = false;
    flagBegin = true;
    waiting.notify_all();
    begin.notify_all();
  }

  void CThread::WaitForThread(void)
  {
    LDEBUG(threadName + " waits until finishing execution");
    unique_lock<mutex> ul(mtxWaiting);
    waiting.wait(ul, [&] { //
      return flagFinish.load();
    });
  }

  void CThread::run(void)
  {
    while (flagAlive)
    {
      try
      {
        LTRACE("waits for execution");
        {
          unique_lock<mutex> ul(mtxWaiting);
          begin.wait(ul, [&]
                     { return (flagBegin.load()); });
        }
        if (!flagAlive)
        {
          continue;
        }
        flagBegin.store(false);
        flagFinish.store(false);
        CheckFlags();
        onBeginning();
        CheckFlags();
        Execute();
        CheckFlags();
        onFinish(); // will be only excuted if no error occurs during onBeginning, Execute
      }
      catch (std::exception &e)
      {
        LERROR("error occured: {}", e.what());
        onException(e.what());
      }
      catch (...)
      {
        LERROR("unknown error occured");
        onException(UNKNOWN_ERROR);
      }
      flagFinish.store(true);
      waiting.notify_all();
    }
  }

  void CThread::CheckFlags(void)
  {
    ASSERT_EXCEPTION(flagAlive, threadName + " stops running");
    if (flagBreak && flagAlive)
    {
      onStartWaiting();
      unique_lock<mutex> ul(mtxWaiting);
      waiting.wait(ul, [&]
                   { return flagBreak.load() && flagAlive; });
      onResume();
    }
    onFlagCheck();
  }

  void CThread::onFlagCheck()
  {
    // implement me
  }

  void CThread::onStartWaiting(void)
  {
    // implement me TODO delete me
  }

  void CThread::onResume(void)
  {
    // implement me
  }

  bool CThread::IsRunning()
  {
    return flagAlive.load() && !flagFinish.load();
  }

  void CThread::onBeginning(void)
  {
    // implement me
  }

  void CThread::onException(std::string msg)
  {
    LINFO(threadName + " will be destroyed");
    Terminate();
    // implement me
  }

  void CThread::onFinish(void)
  {
    // implement me
  }

  void CThread::Execute(void)
  {
    // implement me
  }

} // namespace Thread