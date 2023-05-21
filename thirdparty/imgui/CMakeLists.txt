cmake_minimum_required(VERSION 3.9)

project(imgui)

set(IMGUI_SOURCES
	"imgui/imgui_demo.cpp"
	"imgui/imgui_draw.cpp"
	"imgui/imgui_tables.cpp"
	"imgui/imgui_widgets.cpp"
	"imgui/imgui.cpp"
	"imgui/backends/imgui_impl_opengl3.cpp"
	"imgui/backends/imgui_impl_glfw.cpp"
)

set(IMGUI_INCLUDE_DIRS
	"./"
	"imgui/"
)

add_library(imgui STATIC ${IMGUI_SOURCES})

find_package(OpenGL REQUIRED)

target_link_libraries(imgui PUBLIC ${OPENGL_LIBRARIES})
target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIRS})
