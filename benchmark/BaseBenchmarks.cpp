#include <benchmark/benchmark.h>
#include <Logging.hpp>

void test1(size_t a)
{
    spdlog::get("myLogger")->error("testerror {}", a);
}

void test2(int &i)
{
    i++;
}

static void BM_Test1(benchmark::State &state)
{
    // Log::initLogger();
    // int i = 0;
    // for (auto _ : state)
    // {
    //         test2(1);
    // }
    Log::initLogger();
    for (auto _ : state)
    {
        test1(state.range(0));
    }
}

static void BM_Test2(benchmark::State &state)
{
    Log::initLogger();
    auto logger = spdlog::get("myLogger");
    for (int i = 0; i < 1e3; i++)
    {
        logger->error("testerror");
    }
}

// BENCHMARK(BM_Test1)->Arg(10);
BENCHMARK(BM_Test1)->Arg(10000);

BENCHMARK_MAIN();