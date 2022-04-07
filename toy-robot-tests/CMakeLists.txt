project(toy-robot-tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(toyRobotTests toy_robot_tests.cpp)
target_link_libraries(toyRobotTests ToyRobotLibrary gtest gtest_main)