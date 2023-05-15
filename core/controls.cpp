#include <core/controls.h>

#include <core/application.h>

namespace en61 {

MousePosition MousePosition::Get() {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return {xpos, ypos};
}

void MousePosition::Set(const MousePosition &pos) {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());

	glfwSetCursorPos(window, pos.x, pos.y);
}


bool IsKeyPressed(int key) {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());
	
	return glfwGetKey(window, key) == GLFW_PRESS;
}

} // namespace en61
