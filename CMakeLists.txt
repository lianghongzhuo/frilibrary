cmake_minimum_required(VERSION 3.0.2)

project(frilibrary)
set(frilibrary_VERSION 0.0.1)

find_package(catkin REQUIRED COMPONENTS nodelet)

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES FastResearchInterfaceLibrary TypeIRML)

include_directories(
        include/
        ${catkin_INCLUDE_DIRS}
)
file(GLOB FRI_FILES ${PROJECT_SOURCE_DIR}/src/FastResearchInterfaceLibrary/*.cpp)
add_library(FastResearchInterfaceLibrary  ${FRI_FILES} ${PROJECT_SOURCE_DIR}/src/LinuxAbstraction/LinuxAbstraction.cpp)

file(GLOB RML_FILES ${PROJECT_SOURCE_DIR}/src/TypeIRML/*.cpp)
add_library(TypeIRML ${RML_FILES})

install(TARGETS FastResearchInterfaceLibrary TypeIRML
        DESTINATION lib)

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        )

add_executable(LWRCartImpedanceControlExample src/LWRGettingStartedExamples/LWRCartImpedanceControlExample.cpp)
add_dependencies(LWRCartImpedanceControlExample ${catkin_EXPORTED_TARGETS})
target_link_libraries(LWRCartImpedanceControlExample ${catkin_LIBRARIES} FastResearchInterfaceLibrary pthread)

add_executable(LWRJointImpedanceControlExample src/LWRGettingStartedExamples/LWRJointImpedanceControlExample.cpp)
add_dependencies(LWRJointImpedanceControlExample ${catkin_EXPORTED_TARGETS})
target_link_libraries(LWRJointImpedanceControlExample ${catkin_LIBRARIES} FastResearchInterfaceLibrary pthread)

add_executable(LWRJointPositionControlExample src/LWRGettingStartedExamples/LWRJointPositionControlExample.cpp)
add_dependencies(LWRJointPositionControlExample ${catkin_EXPORTED_TARGETS})
target_link_libraries(LWRJointPositionControlExample ${catkin_LIBRARIES} FastResearchInterfaceLibrary pthread)

add_executable(LWRLoggingExample src/LWRGettingStartedExamples/LWRLoggingExample.cpp)
add_dependencies(LWRLoggingExample ${catkin_EXPORTED_TARGETS})
target_link_libraries(LWRLoggingExample ${catkin_LIBRARIES} FastResearchInterfaceLibrary pthread)
