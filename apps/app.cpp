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
    Log::setLogLevel(4);
    addLogger(logger);
    DEBUG("Logger created");
}

int main()
{
    createLogger();
    testThread();

    fmt::report_system_error(0, "main()");
    return 0;
}
