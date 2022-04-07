cmake_minimum_required(VERSION 3.21)
project(toy_robot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

include_directories(src)

enable_testing()

add_subdirectory(toy-robot-tests)
add_subdirectory(src)

add_executable(toy_robot main.cpp)
target_link_libraries(toy_robot ToyRobotLibrary)