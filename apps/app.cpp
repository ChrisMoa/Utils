#include <fmt/format.h>

#include "Assert.hpp"
#include "BaseEncryption.hpp"
#include "FileSystemUtils.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>

#include <JsonUtils.hpp>
#include <Logging.hpp>
#include <json/json.h>
#include <rapidcsv.h>

#include <Poco/Data/Session.h>

#include <CThread.h>
#include <ExecutionThread.hpp>

#include <sstream>

using namespace CryptoPP;

int main() {
    Log::initLogger();
    LWARNING("Begin");

    fmt::report_system_error(0, "main()");
    return 0;
}