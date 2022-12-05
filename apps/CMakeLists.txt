add_executable(app app.cpp)

target_compile_features(app PRIVATE cxx_std_20)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Poco REQUIRED Foundation Util Data)

target_link_libraries(app PRIVATE
    Utils
    fmt::fmt 
    spdlog::spdlog
    jsoncpp
)

target_link_libraries(app PUBLIC
    rapidcsv
    Poco::Foundation
    Poco::Util
    Poco::Data
)