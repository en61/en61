cmake_minimum_required(VERSION 3.9)
project(sandbox VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EN61_OUTPUT_FOLDER "en61_lib/")
file(GLOB SANDBOX_SOURCES "*.cpp")

add_executable(sandbox ${SANDBOX_SOURCES})

# adding EN61
add_subdirectory(../ ${EN61_OUTPUT_FOLDER})
target_include_directories(sandbox PRIVATE ${EN61_INCLUDE_DIRS})
target_link_libraries(sandbox PRIVATE en61)
