#include <core/window.h>

namespace en61 {

Window::Window(const WindowProps &props) : _properties(props) {

	_handle = glfwCreateWindow(_properties.width, _properties.height, _properties.title.c_str(), NULL, 0);
	if (!_handle) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetInputMode(_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwSetWindowUserPointer(_handle, this);
	SetupCallbacks();
}

Window::~Window() {
	glfwDestroyWindow(_handle);
	glfwTerminate();
}

void Window::MakeCurrentContext() {
	glfwMakeContextCurrent(_handle);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(_handle);
}

bool Window::ShouldClose() {
	return (bool)glfwWindowShouldClose(_handle);
}

float Window::Ratio() const {
	return (float)_properties.width / (float)_properties.height;
}

void Window::ErrorCallback(int error, const char *description) {
	(void)error;
	std::cerr << "error: " << description << std::endl;
}

void Window::KeyCallback(int key, int action) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		Close();
}

void Window::ScrollCallback(double xoffset, double yoffset) {
	for (auto callback: scroll_callbacks)
		callback(xoffset, yoffset);
}

void Window::Close() {
	glfwSetWindowShouldClose(_handle, GLFW_TRUE);
}

GLFWwindow *Window::NativeHandle() {
	return _handle;
}

WindowProps Window::Properties() const {
	return _properties;
}

double Window::Width() const {
	return _properties.width;
}

double Window::Height() const {
	return _properties.height;
}

void Window::SetupCallbacks() {
	auto key_func = [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		Window *handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
		return handle->KeyCallback(key, action);
	};

	auto scroll_func = [](GLFWwindow* window, double xoffset, double yoffset) {
		Window *handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
		return handle->ScrollCallback(xoffset, yoffset);
	};

	glfwSetKeyCallback(_handle, key_func);
	glfwSetScrollCallback(_handle, scroll_func);
}

} // namespace en61
