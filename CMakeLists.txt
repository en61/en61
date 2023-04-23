cmake_minimum_required(VERSION 3.9)

project(en61 VERSION 0.1 DESCRIPTION "EN61")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB EN61_SOURCES
	"core/*.cpp"
	"core/*/*.cpp"
)

file(GLOB EN61_HEADER_FILES
	"core/*.h"
	"core/*/*.h"
)

set(EN61_INCLUDE_DIRS
	"./"
	"thirdparty/"
)

option(DYNAMIC "If true a shared library will be built" OFF)

if (DYNAMIC)
	add_library(en61 SHARED ${EN61_SOURCES} ${EN61_HEADER_FILES})
	message(STATUS "Building dynamic library...")
else()
	add_library(en61 STATIC ${EN61_SOURCES} ${EN61_HEADER_FILES})
	message(STATUS "Building static library...")
endif(DYNAMIC)

add_subdirectory(thirdparty/glfw/)
add_subdirectory(thirdparty/glad/)
add_subdirectory(thirdparty/stb/)
add_subdirectory(thirdparty/glm/)

target_link_libraries(en61 glfw glad stb glm)

target_include_directories(en61 PUBLIC ${EN61_INCLUDE_DIRS})

