cmake_minimum_required(VERSION 3.23)

project(3d)

find_package(SDL2 REQUIRED)

set (CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH bin/)

include_directories(${SDL2_INCLUDE_DIRS})

add_library(geometry src/geometry/geometry.cpp)
add_library(utils src/utils/utils.cpp)

add_executable(3d src/main.cpp)

target_link_libraries(3d ${SDL2_LIBRARIES})
target_link_libraries(3d geometry)
target_link_libraries(3d utils)
