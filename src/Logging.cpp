#include "Logging.hpp"
#include <thread>
#include <spdlog/sinks/basic_file_sink.h>

//__PRETTY_FUNCTION__

namespace Log
{
  void initLogger()
  {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%d.%m.%Y %H:%M:%S -- %n -- %^%l%$ -- th: %t] %v");
    if (!spdlog::get("myLogger"))
    {
      spdlog::basic_logger_mt("myLogger", "log.txt");
    }
  }
} // namespace LOG
