#include <fmt/format.h>

#include "Assert.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>

#include <Logging.hpp>
#include <JsonUtils.hpp>
#include <json/json.h>
#include <rapidcsv.h>

#include <Poco/Data/Session.h>

#include <CThread.h>
#include <ExecutionThread.hpp>

int main()
{
  Log::initLogger();
  LWARNING("Begin");
  fmt::report_system_error(0, "main()");
  return 0;
}