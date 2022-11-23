add_executable(app app.cpp)

target_compile_features(app PRIVATE cxx_std_20)

# INCLUDE_DIRECTORIES(
#     /opt/vcpkg/packages/poco_x64-linux/include
# )

# LINK_DIRECTORIES(
#     /opt/vcpkg/packages/poco_x64-linux/include/lib
# ) 


find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Poco REQUIRED Foundation Util Data JSON)

target_link_libraries(app 
    PRIVATE Utils
    PRIVATE fmt::fmt spdlog::spdlog jsoncpp_lib
)
target_link_libraries(app PUBLIC rapidcsv)

target_link_libraries(app PUBLIC
    Poco::Foundation
    Poco::Util
    Poco::Data
    Poco::JSON
)
    