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
#include <spdlog/sinks/basic_file_sink.h>
#include <Logging.hpp>

int main()
{
  Log::initLogger();
  LTRACE("test");
  LDEBUG("TestDebug");

  std::map<int, int> test = {{1, 2}, {3, 4}, {5, 6}};

  spdlog::info("Test3 {}", 42);
  spdlog::trace("Test3 {}", 43);

  LENTER();
  LLEAVE();
  LWARNING("warn {}", 45);
  LERROR("error");

  spdlog::get("myLogger")->error("testerror");
  // SPDLOG_INFO("Test4 {}", test);

  fmt::report_system_error(0, "main()");
  return 0;
}