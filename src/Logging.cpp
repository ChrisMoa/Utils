#include "Logging.hpp"
#include <thread>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/dist_sink.h>

namespace Log
{
  void initLogger()
  {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("%d.%m.%Y %H:%M:%S;%n;%^%l%$;%t;%v");
    if (!spdlog::get("mainLogger"))
    {
      auto logger = spdlog::basic_logger_mt("mainLogger", "log.csv");
      auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      spdlog::get("mainLogger")->sinks().push_back(consoleSink);
      spdlog::set_default_logger(logger);
    }
  }
} // namespace LOG
