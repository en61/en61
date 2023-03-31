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

	void MakeCurrentContext();
	void SwapBuffers();
	bool ShouldClose();
	void Close();

	void ErrorCallback(int error, const char *description);
	void KeyCallback(int key, int action);
	void ScrollCallback(double xoffset, double yoffset);

	float Ratio() const;

	GLFWwindow *NativeHandle();

	WindowProps Properties() const;
	double Width() const;
	double Height() const;

	void SetupCallbacks();

	static std::shared_ptr<Window> Create(const WindowProps &props = WindowProps()) {
		return std::make_shared<Window>(props);
	}

public:
	using ScrollCallbackFunc = std::function<void(double, double)>;
	std::vector<ScrollCallbackFunc> scroll_callbacks;

protected:
	WindowProps _properties;
	GLFWwindow *_handle;
};

inline void operator+=(std::vector<Window::ScrollCallbackFunc> &storage, Window::ScrollCallbackFunc callback) {
	storage.push_back(callback);
}

} // namespace en61
