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

int main()
{
  Log::initLogger();
  LERROR("Test");

  fmt::report_system_error(0, "main()");
  return 0;
}