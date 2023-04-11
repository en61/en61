#include <core/window.h>

namespace en61 {

Window::Window(const WindowProps &props) : _properties(props) {

	_handle = glfwCreateWindow(_properties.width, _properties.height, _properties.title.c_str(), NULL, 0);
	if (!_handle) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetInputMode(_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

void Window::SetEventCallback(EventCallbackFunc callback) {
	_event_callback = callback;
}

void Window::SetupCallbacks() {
	auto key_func = [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		Window *handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
		switch (action) {
			case GLFW_PRESS:
				KeyPressedEvent event(key);
				handle->_event_callback(event);
				break;
		}
	};

	auto scroll_func = [](GLFWwindow* window, double xoffset, double yoffset) {
		Window *handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
		MouseScrolledEvent event(xoffset, yoffset);
		handle->_event_callback(event);
	};

	auto framebuffer_resize_func = [](GLFWwindow* window, int width, int height) {
		Window *handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
		FramebufferResizedEvent event(width, height);
		handle->_event_callback(event);
	};

	auto mouse_moved_func = [](GLFWwindow* window, double x, double y) {
		Window *handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
		MouseMovedEvent event(x, y);
		handle->_event_callback(event);
	};

	glfwSetFramebufferSizeCallback(_handle, framebuffer_resize_func);
	glfwSetCursorPosCallback(_handle, mouse_moved_func);
	glfwSetKeyCallback(_handle, key_func);
	glfwSetScrollCallback(_handle, scroll_func);
}

} // namespace en61
