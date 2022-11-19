# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST 
  "${PROJECT_SOURCE_DIR}/include/CThread.h"
  "${PROJECT_SOURCE_DIR}/include/Assert.hpp"
  "${PROJECT_SOURCE_DIR}/include/Exception.h"
  "${PROJECT_SOURCE_DIR}/include/FileSystemUtils.h"
  "${PROJECT_SOURCE_DIR}/include/StringUtils.hpp"
  "${PROJECT_SOURCE_DIR}/include/Logging.hpp"
  "${PROJECT_SOURCE_DIR}/include/Stopwatch.h"
  "${PROJECT_SOURCE_DIR}/include/JsonUtils.hpp"
)

# Make an automatic library - will be static or dynamic based on user setting
add_library(Utils 
  CThread.cpp
  FileSystemUtils.cpp
  StringUtils.cpp
  Logging.cpp
  ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(Utils PUBLIC ../include)

# This depends on (header only) boost
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(jsoncpp REQUIRED)
target_link_libraries(Utils PRIVATE Boost::boost)
target_link_libraries(Utils PRIVATE fmt::fmt spdlog::spdlog jsoncpp_lib)
target_link_libraries(Utils PUBLIC rapidcsv)

# for android later
if(ANDROID)
    target_link_libraries(Utils PUBLIC log)
    target_link_libraries(Utils INTERFACE log)
endif()


# All users of this library will need at least C++11
target_compile_features(Utils PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

message(STATUS "successfully build lib <Utils>")  