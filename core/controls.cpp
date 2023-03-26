#include <core/controls.h>

#include <core/application.h>

namespace en61 {

std::pair<double, double> mouse_position() {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::get()->window()->native_handle());

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return {xpos, ypos};
}

void set_mouse_position(double width, double height) {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::get()->window()->native_handle());

	glfwSetCursorPos(window, width, height);
}


bool is_key_pressed(int key) {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::get()->window()->native_handle());
	
	return glfwGetKey(window, key) == GLFW_PRESS;
}

} // namespace en61

