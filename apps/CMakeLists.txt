add_executable(app app.cpp)
target_compile_features(app PRIVATE cxx_std_20)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(jsoncpp REQUIRED)

target_link_libraries(app 
    PRIVATE Utils
    PRIVATE fmt::fmt spdlog::spdlog jsoncpp_lib
)
target_link_libraries(app PUBLIC rapidcsv)
    