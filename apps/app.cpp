#include <CThread.h>
#include <Log/LoggerConsole.hpp>
#include <Log/Logging.hpp>

#include <fmt/format.h>

#include "Assert.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>

#include <FileSystemUtils.h>
#include <StringUtils.hpp>

#include <filesystem>
#include <spdlog/spdlog.h>

using namespace Thread;

class TestThread : public CThread
{
public:
  TestThread(std::string name = "Test") : CThread(name) {}
  ~TestThread() {}

private:
  void Execute() override
  {
    std::string msg = getThreadName() + " starts testing";
    std::cout << msg << std::endl;
    WARNING(msg);
  }
};

void testThread()
{
  TestThread testThread = TestThread();
  testThread.Resume();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  try {
    ASSERT_EXCEPTION(false, "Exception!!!!!");
  } catch (std::exception &e) {
    std::cout << "exception in main: " << e.what() << std::endl;
  }
}

void createLogger()
{
  using namespace Log;
  auto logger = shared_ptr<ILogger>(new LoggerConsole());
  logger->setLogLevel(Log::LogEntry::Level::TRACE);
  Log::LoggerManager::getInstance()->addLogger(logger);
  DEBUG("Logger created");
  // TRACE("Test");
}

int main()
{
  spdlog::info("Welcome to spdlog!");

  // createLogger();
  //  testThread();

  size_t sz = 10;
  // std::vector<TestThread> thPool;
  // for (size_t i = 0; i < sz; i++)
  // {
  //     thPool.push_back(TestThread("thread" + std::to_string(i)));
  // }

  // for (auto &th : thPool)
  // {
  //     th.Resume();
  // }

  // for (auto &th : thPool)
  // {
  //     th.WaitForThread();
  // }
  // fmt::report_system_error(0, "main()");
  return 0;
}
