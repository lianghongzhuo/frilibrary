cmake_minimum_required(VERSION 3.0.2)

project(frilibrary)
set(frilibrary_VERSION 0.0.0)
include_directories(
        include
)
file(GLOB FRI_FILES ${PROJECT_SOURCE_DIR}/src/FastResearchInterfaceLibrary/*.cpp)
add_library(FastResearchInterfaceLibrary ${LINUX_ABS_FILES} ${FRI_FILES})

file(GLOB RML_FILES ${PROJECT_SOURCE_DIR}/src/TypeIRML/*.cpp)
add_library(TypeIRML ${LINUX_ABS_FILES} ${RML_FILES})

# install header file hierarchy
file(GLOB HEADER_FILES RELATIVE ${PROJECT_SOURCE_DIR} include/*.h)
foreach(HEADER ${HEADER_FILES})
    string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
    install(FILES ${HEADER} DESTINATION include)
endforeach()
