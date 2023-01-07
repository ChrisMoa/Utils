# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(LibName "Utils")

file(GLOB HEADER_LIST "${PROJECT_SOURCE_DIR}/include/*.h" "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SRC_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp")

#message(STATUS "found headers: ${HEADER_LIST}")
#message(STATUS "found src: ${SRC_LIST}")

add_library(${LibName} ${SRC_LIST} ${HEADER_LIST} ${UI_LIST})
# We need this directory, and users of our library will need it too
target_include_directories(${LibName} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# boost
target_link_libraries(${LibName} PRIVATE Boost::boost)

# spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${LibName} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# json cpp
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${LibName} PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)

# fmt
find_package(fmt REQUIRED)
target_link_libraries(${LibName} PRIVATE fmt::fmt)

# poco cpp
find_package(Poco REQUIRED Foundation Util Data)
target_link_libraries(${LibName} PRIVATE 
  Poco::Foundation
  Poco::Util
  Poco::Data)

# crypto cpp
find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(${LibName} PRIVATE cryptopp::cryptopp)


# rapidcsv
target_link_libraries(${LibName} PRIVATE rapidcsv)

# for android later
if(ANDROID)
    target_link_libraries(${LibName} PUBLIC log)
    target_link_libraries(${LibName} INTERFACE log)
endif()


# All users of this library will need at least C++20
target_compile_features(${LibName} PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

message(STATUS "successfully build lib <${LibName}>")  