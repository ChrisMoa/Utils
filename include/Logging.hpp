//
// Created by chris-tab on 11.05.21.
//

#include <spdlog/spdlog.h>
#include <utility>

#ifndef LENTER
#define LENTER() spdlog::trace("enter")
#endif
#ifndef LLEAVE
#define LLEAVE() spdlog::trace("leave")
#endif
#ifndef LTRACE
#define LTRACE(...) spdlog::trace(__VA_ARGS__)
#endif
#ifndef LDEBUG
#define LDEBUG(...) spdlog::debug(__VA_ARGS__)
#endif
#ifndef LINFO
#define LINFO(...) spdlog::info(__VA_ARGS__)
#endif
#ifndef LWARNING
#define LWARNING(...) spdlog::warn(__VA_ARGS__)
#endif
#ifndef LERROR
#define LERROR(...) spdlog::error(__VA_ARGS__)
#endif

namespace Log
{
    /**
     * @brief initialize the logger
     * @return void
     */
    void initLogger();

} // namespace LOG

#ifndef LOGGING_HPP
#define LOGGING_HPP

#endif // LOGGING_HPP