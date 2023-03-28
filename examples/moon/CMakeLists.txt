cmake_minimum_required(VERSION 3.9)
project(moon VERSION 0.1)

set(EN61_OUTPUT_FOLDER "en61_lib/")
file(GLOB MOON_SOURCES "*.cpp")

add_executable(moon ${MOON_SOURCES})

# adding en61
add_subdirectory(../../ ${EN61_OUTPUT_FOLDER})
target_include_directories(moon PRIVATE ${EN61_INCLUDE_DIRS})
target_link_libraries(moon PRIVATE en61)
