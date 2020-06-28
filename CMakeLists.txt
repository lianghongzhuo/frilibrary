cmake_minimum_required(VERSION 2.8)

project(frilibrary)

include(ExternalProject)

set(frilibrary_VERSION 0.0.0)
set(RML_HEADER_DIR "${CMAKE_BINARY_DIR}/frilibrary-prefix/src/frilibrary/include/")
set(RML_RELEASE_LIBRARY_DIR "${CMAKE_BINARY_DIR}/frilibrary-prefix/src/frilibrary/Linux/x64/release/lib/")
set(RML_DEBUG_LIBRARY_DIR "${CMAKE_BINARY_DIR}/frilibrary-prefix/src/frilibrary/Linux/x64/debug/lib/")

ExternalProject_Add(
  frilibrary
  URL "${PROJECT_SOURCE_DIR}/fril.zip"
  DOWNLOAD_NAME fril.zip
  PATCH_COMMAND patch -p0 --binary < ${CMAKE_CURRENT_SOURCE_DIR}/patch_64bit.patch
  CONFIGURE_COMMAND ""
  BINARY_DIR frilibrary-prefix/src/frilibrary/Linux/
  BUILD_COMMAND make clean all
  INSTALL_COMMAND ls "${RML_HEADER_DIR}"
  )

install(
  DIRECTORY ${RML_HEADER_DIR}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
  )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  install(DIRECTORY ${RML_DEBUG_LIBRARY_DIR}
    DESTINATION lib
    FILES_MATCHING PATTERN "*${CMAKE_STATIC_LIBRARY_SUFFIX}"
    )
else()
  install(DIRECTORY ${RML_RELEASE_LIBRARY_DIR}
    DESTINATION lib
    FILES_MATCHING PATTERN "*${CMAKE_STATIC_LIBRARY_SUFFIX}"
    )
endif()

configure_file(frilibrary-config.cmake.in
  ${PROJECT_BINARY_DIR}/frilibrary-config.cmake @ONLY)
configure_file(frilibrary-config-version.cmake.in
  ${PROJECT_BINARY_DIR}/frilibrary-config-version.cmake @ONLY)

install(FILES ${PROJECT_BINARY_DIR}/frilibrary-config.cmake DESTINATION share/frilibrary/cmake)
install(FILES ${PROJECT_BINARY_DIR}/frilibrary-config-version.cmake DESTINATION share/frilibrary/cmake)
install(FILES package.xml DESTINATION share/frilibrary)

