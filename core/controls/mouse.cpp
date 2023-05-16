#include <core/controls/mouse.h>

#include <core/base/application.h>

namespace en61 {

MousePosition MousePosition::Get() {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());

	MousePosition pos;
	glfwGetCursorPos(window, &pos.x, &pos.y);
	return pos;
}

void MousePosition::Set(const MousePosition &pos) {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());

	glfwSetCursorPos(window, pos.x, pos.y);
}

} // namespace en61
