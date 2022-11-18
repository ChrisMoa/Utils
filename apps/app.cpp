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

  fmt::report_system_error(0, "main()");
  return 0;
}