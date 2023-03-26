#pragma once

#include <core/opengl.h>

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <functional>

namespace en61 {

struct WindowProps {
	std::string title;
	double width = 1280;
	double height = 720;

	WindowProps(double w, double h, const std::string &name = "EN61")
		: width(w), height(h), title(name) {}

	WindowProps(const std::string &name = "EN61") {}
};

class Window {
public:
	Window(const WindowProps &props);
	~Window();

	void make_current_context();
	void swap_buffers();
	bool should_close();
	void close();

	void error_callback(int error, const char *description);
	void key_callback(int key, int action);
	void scroll_callback(double xoffset, double yoffset);

	float ratio() const;

	GLFWwindow *native_handle();

	WindowProps properties() const;
	double width() const;
	double height() const;

	void setup_callbacks();

	static std::shared_ptr<Window> create(const WindowProps &props = WindowProps()) {
		return std::make_shared<Window>(props);
	}

public:
	using ScrollCallback = std::function<void(double, double)>;
	std::vector<ScrollCallback> scroll_callbacks;

protected:
	WindowProps _properties;
	GLFWwindow *_handle;
};

inline void operator+=(std::vector<Window::ScrollCallback> &storage, Window::ScrollCallback callback) {
	storage.push_back(callback);
}

} // namespace en61
