#include <core/controls.h>

#include <core/application.h>

namespace en61 {

std::pair<double, double> MousePosition() {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return {xpos, ypos};
}

void SetMousePosition(double width, double height) {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());

	glfwSetCursorPos(window, width, height);
}


bool IsKeyPressed(int key) {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());
	
	return glfwGetKey(window, key) == GLFW_PRESS;
}

} // namespace en61

