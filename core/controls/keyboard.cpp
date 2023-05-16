#include <core/controls/keyboard.h>

#include <core/base/application.h>

namespace en61 {

bool IsKeyPressed(int key) {
	GLFWwindow *window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->NativeHandle());
	
	return glfwGetKey(window, key) == GLFW_PRESS;
}

} // namespace en61
