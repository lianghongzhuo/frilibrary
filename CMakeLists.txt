cmake_minimum_required(VERSION 3.0.2)

project(frilibrary)
set(frilibrary_VERSION 0.0.1)
include_directories(
        include/
        ${catkin_INCLUDE_DIRS}
)

find_package(catkin REQUIRED COMPONENTS nodelet)

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES FastResearchInterfaceLibrary TypeIRML)

file(GLOB FRI_FILES ${PROJECT_SOURCE_DIR}/src/FastResearchInterfaceLibrary/*.cpp)
add_library(FastResearchInterfaceLibrary  ${FRI_FILES} ${PROJECT_SOURCE_DIR}/src/LinuxAbstraction/LinuxAbstraction.cpp)

file(GLOB RML_FILES ${PROJECT_SOURCE_DIR}/src/TypeIRML/*.cpp)
add_library(TypeIRML ${RML_FILES})

install(TARGETS FastResearchInterfaceLibrary TypeIRML
        DESTINATION lib)

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        )
