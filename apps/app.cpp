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
      CheckFlags();
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
    LINFO("I start waiting");
  }

  void onResume() override
  {
    LINFO("I continue");
  }

  void onEnd() override
  {
    LWARNING("Thread is destroyed");
  }

  bool finished = false;
};

int main()
{
  Log::initLogger();
  auto testThread = std::shared_ptr<TestThread>(new TestThread());
  testThread->Begin();
  LINFO("I do something");
  LINFO("Thread should do a break");
  testThread->Break();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  LINFO("Thread should return from break");
  // testThread->Resume();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  testThread->Terminate();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  fmt::report_system_error(0, "main()");
  return 0;
}