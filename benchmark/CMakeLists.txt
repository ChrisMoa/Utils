find_package(benchmark REQUIRED)

# Tests need to be added as executables first
add_executable(ownBenchmark BaseBenchmarks.cpp)

# I'm using C++17 in the test
target_compile_features(ownBenchmark PRIVATE cxx_std_20)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(ownBenchmark PRIVATE Utils benchmark::benchmark)