#include <lib.hpp>
#include <cThread.h>
#include <Log/Logging.hpp>
#include <Log/LoggerConsole.hpp>

#include <fmt/format.h>

#include <iostream>
#include <vector>
#include <tuple>
#include "assert.hpp"
#include <thread>
#include <chrono>

using namespace Thread;

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

void testLog()
{
    using namespace Log;
    auto logger = shared_ptr<ILogger>(new LoggerConsole());
    addLogger(logger);
    TRACE("Text");
    DEBUG("Text");
    INFO("Text");
    WARNING("Text");
    ERROR("Text");
}

void testThread()
{
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

int main()
{
    // testThread();
    testLog();
    fmt::report_system_error(0, "main()");
    return 0;
}
