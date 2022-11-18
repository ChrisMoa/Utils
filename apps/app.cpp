#include <fmt/format.h>

#include "Assert.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>

#include <Logging.hpp>

int main()
{
  Log::initLogger();

  fmt::report_system_error(0, "main()");
  return 0;
}