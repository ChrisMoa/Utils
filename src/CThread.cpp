//
// Created by chris-tab on 15.05.21.
//

#include "CThread.h"
#include "Assert.hpp"
#include <Logging.hpp>

using namespace std;

namespace Thread
{

  CThread::~CThread()
  {
    LTRACE(threadName + " starts to be destroyed");
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

  CThread::CThread(Thread::CThread &a) {}
  CThread &CThread::operator=(const Thread::CThread &a) { return *this; }

  std::string CThread::getThreadName() { return threadName; }

  void CThread::Execute(void) { LDEBUG("I have to be overwritten"); }

  void CThread::Resume(void)
  {
    LTRACE(threadName + " resumes");
    shared_lock sl(lock);
    flagBreak = false;
    executionCounter = 1;
    waiting.notify_one();
  }

  void CThread::Terminate(void)
  {
    LTRACE(threadName + " will be terminated");
    shared_lock sl(lock);
    flagAlive = false;
    flagFinish = false;
    waiting.notify_all();
  }

  void CThread::WaitForThread(void)
  {
    LDEBUG(threadName + " waits until finishing execution");
    unique_lock<mutex> ul(mtxWaiting);
    waiting.wait(ul, [&]
                 {
    onWaiting();
    return flagFinish.load(); });
    onResume();
    waiting.notify_one();
  }

  void CThread::onFinish(void) { LDEBUG("I have to be overwritten"); }

  void CThread::run(void)
  {
    LTRACE("waits for next execution");
    while (flagAlive)
    {
      flagFinish.store(false);
      Execute();
      flagFinish.store(true);
      this->waiting.notify_one();
      unique_lock<mutex> ul(mtxWaiting);
      LTRACE("waits for next execution");
      waiting.wait(ul, [&]
                   { return (!flagFinish.load()); });
      this->waiting.notify_one();
    }
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
    LTRACE(threadName + " will take a break");
    shared_lock sl(lock);
    flagBreak = true;
  }

  void CThread::onWaiting(void) { LTRACE("do on wait execution"); }

  void CThread::onResume(void) { LTRACE("do on resume"); }

} // namespace Thread