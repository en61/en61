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
	setup_callbacks();
}

Window::~Window() {
	glfwDestroyWindow(_handle);
	glfwTerminate();
}

void Window::make_current_context() {
	glfwMakeContextCurrent(_handle);
}

void Window::swap_buffers() {
	glfwSwapBuffers(_handle);
}

bool Window::should_close() {
	return (bool)glfwWindowShouldClose(_handle);
}

float Window::ratio() const {
	return (float)_properties.width / (float)_properties.height;
}

void Window::error_callback(int error, const char *description) {
	(void)error;
	std::cerr << "error: " << description << std::endl;
}

void Window::key_callback(int key, int action) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		close();
}

void Window::scroll_callback(double xoffset, double yoffset) {
	for (auto callback: scroll_callbacks)
		callback(xoffset, yoffset);
}

void Window::close() {
	glfwSetWindowShouldClose(_handle, GLFW_TRUE);
}

GLFWwindow *Window::native_handle() {
	return _handle;
}

WindowProps Window::properties() const {
	return _properties;
}

double Window::width() const {
	return _properties.width;
}
double Window::height() const {
	return _properties.height;
}

void Window::setup_callbacks() {
	auto key_func = [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		Window *handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
		return handle->key_callback(key, action);
	};

	auto scroll_func = [](GLFWwindow* window, double xoffset, double yoffset) {
		Window *handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
		return handle->scroll_callback(xoffset, yoffset);
	};

	glfwSetKeyCallback(_handle, key_func);
	glfwSetScrollCallback(_handle, scroll_func);
}

} // namespace en61
