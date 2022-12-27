
SET(AppName "app")
add_executable(${AppName} app.cpp)

target_compile_features(${AppName} PRIVATE cxx_std_20)

# spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${AppName} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# jsoncpp
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${AppName} PRIVATE PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)

# fmt
find_package(fmt REQUIRED)
target_link_libraries(${AppName} PRIVATE fmt::fmt)

# rapid csv
target_link_libraries(${AppName} PRIVATE rapidcsv)

target_link_libraries(${AppName} PRIVATE Utils)

# POCO
find_package(Poco REQUIRED Foundation Util Data)
target_link_libraries(${AppName} PRIVATE
    Poco::Foundation
    Poco::Util
    Poco::Data
)