#include <CThread.h>
#include <Log/Logging.hpp>
#include <Log/LoggerConsole.hpp>

#include <fmt/format.h>

#include <iostream>
#include <vector>
#include <tuple>
#include "Assert.hpp"
#include <thread>
#include <chrono>

#include <StringUtils.hpp>
#include <FileSystemUtils.h>

#include <filesystem>

using namespace Thread;

void testThread()
{
    class TestThread : public CThread
    {
    public:
        TestThread() : CThread("Test") {}
        ~TestThread() {}

    private:
        void Execute() override
        {
            std::cout << "Execution starts" << std::endl;
        }
    };
    TestThread testThread = TestThread();
    testThread.Resume();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    try
    {
        ASSERT_EXCEPTION(false, "Exception!!!!!");
    }
    catch (std::exception &e)
    {
        std::cout << "exception in main: "
                  << e.what() << std::endl;
    }
}

void createLogger()
{
    using namespace Log;
    auto logger = shared_ptr<ILogger>(new LoggerConsole());
    addLogger(logger);
    DEBUG("Logger created");
}

int main()
{
    // testThread();
    createLogger();
    std::string exePath = Util::getExePath();
    INFO(exePath);
    INFO(std::filesystem::current_path());

    auto exePathStrings = Util::getSubFilesRel(exePath);
    for (auto exePathString : exePathStrings)
    {
        DEBUG(exePathString);
    }
    DEBUG("Filename: " + Util::getFilenameOfName("test/test.txt"));
    DEBUG("Dir: " + Util::getDirOfName("test/test.txt"));
    DEBUG("fileExists: " + std::to_string(Util::fileExists("test/test.txt")));

    fmt::report_system_error(0, "main()");
    return 0;
}
