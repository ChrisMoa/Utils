# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST 
  "${PROJECT_SOURCE_DIR}/include/lib.hpp"
  "${PROJECT_SOURCE_DIR}/include/assert.hpp"
  "${PROJECT_SOURCE_DIR}/include/cThread.h"
  "${PROJECT_SOURCE_DIR}/include/Exception.h"
  "${PROJECT_SOURCE_DIR}/include/Log/ILogger.hpp"
  "${PROJECT_SOURCE_DIR}/include/Log/LogEntry.hpp"
  "${PROJECT_SOURCE_DIR}/include/Log/LoggerConsole.hpp"
  "${PROJECT_SOURCE_DIR}/include/Log/Logging.hpp"
)

# Make an automatic library - will be static or dynamic based on user setting
add_library(Utils 
  lib.cpp
  cThread.cpp
  Log/LogEntry.cpp
  Log/LoggerConsole.cpp
  Log/Logging.cpp
  ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(Utils PUBLIC ../include)

# This depends on (header only) boost
target_link_libraries(Utils PRIVATE Boost::boost)

# All users of this library will need at least C++11
target_compile_features(Utils PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

message(STATUS "successfully build lib <Utils>")  