#include <fmt/format.h>

#include "Assert.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>

#include <Logging.hpp>
#include <JsonUtils.hpp>
#include <rapidcsv.h>

#include <Poco/Data/Session.h>

#include <CThread.h>
#include <ExecutionThread.hpp>

class TestThread : public Thread::CThread
{
public:
  TestThread() : CThread("TestThread") {}
  ~TestThread() {}

private:
  void Execute() override
  {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    LINFO("I did a hard job");
    while (!finished)
    {
      // std::this_thread::sleep_for(std::chrono::milliseconds(100));
      // CheckFlags();
    }
  }

  void onException(std::string msg) override
  {
    if (msg == UPDATE_ERROR)
    {
      return;
    }
    Terminate();
    LERROR("I got a hard fault: {}", msg);
  }

  void onStartWaiting() override
  {
    LTRACE("I start waiting");
  }

  void onResume() override
  {
    LTRACE("I continue");
  }

  bool finished = false;
};

int main()
{
  Log::initLogger();
  LWARNING("Begin");
  auto executionThread = std::shared_ptr<Thread::ExecutionThread>(new Thread::ExecutionThread());
  size_t counter = 1;
  auto executeCb = [&](Util::Settings &settings)
  {
    LINFO("I execute something difficult: {}", counter);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    LINFO("I finished executing something difficult: {}", counter);
  };
  auto exceptionCb = [&](Util::Settings &settings)
  {
    LINFO("I got an exception but it do nothing: {}", counter);
  };
  auto finishCb = [&](Util::Settings &settings)
  {
    LINFO("I finished the job: {}", counter);
    counter++;
  };
  Thread::Job jb1("1st job", executeCb, exceptionCb, finishCb);
  executionThread->addJob(jb1);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  Thread::Job jb2("2nd job", executeCb, exceptionCb, finishCb);
  executionThread->addJob(jb2);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  Thread::Job jb3("3rd job", executeCb, exceptionCb, finishCb);
  executionThread->addJob(jb3);

  executionThread->WaitForThread();
  LWARNING("put in a value to finish");
  executionThread.reset();

  std::string inString;
  std::cin >> inString;
  fmt::report_system_error(0, "main()");
  return 0;
}