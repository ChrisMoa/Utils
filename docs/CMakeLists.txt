# set(DOXYGEN_EXTRACT_ALL YES)
# set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

# # doxygen_add_docs(docs Utils/lib.hpp "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
# #                  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include")
set(DOXYGEN_GENERATE_HTML YES)
# set(DOXYGEN_GENERATE_MAN YES)

# doxygen_add_docs(
#     docs Utils/lib.hpp "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
#     WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"}
#     COMMENT "Generate man pages"
# )
add_custom_target(
  doc ALL
  COMMAND $<$<CONFIG:Release>:${DOXYGEN_EXECUTABLE} ${doxyfile_in}>
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
  COMMENT "Generating API documentation with Doxygen"
  VERBATIM
)