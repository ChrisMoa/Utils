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
    if (!spdlog::get("mainLogger"))
    {
      auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      console_sink->set_level(spdlog::level::info);
      console_sink->set_pattern("[%^%l%$] %v");

      auto file_logger = spdlog::daily_logger_mt("mainLogger", "logfiles/log.csv", 2, 30); // creates a new logfile at 02:30am
      file_logger->set_level(spdlog::level::trace);
      file_logger->set_pattern("%d.%m.%Y %H:%M:%S;%n;%^%l%$;%t;%v");
      file_logger->sinks().push_back(console_sink);
      spdlog::set_default_logger(file_logger);
    }
  }
} // namespace LOG
