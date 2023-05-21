#pragma once

#include <core/opengl.h>
#include <core/common.h>
#include <core/event/event.h>
#include <core/event/mouse.h>
#include <core/event/key.h>
#include <core/event/system.h>

#include <vector>
#include <string>
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

	using EventCallbackFunc = std::function<void(Event&)>;

	void MakeCurrentContext();
	void SwapBuffers();
	bool ShouldClose();
	void Close();

	void LockMouse();
	void UnlockMouse();

	void ErrorCallback(int error, const char *description);
	void SetEventCallback(EventCallbackFunc callback);

	GLFWwindow *NativeHandle();
	WindowProps Properties() const;

	float Ratio() const;
	double Width() const;
	double Height() const;

	void SetupCallbacks();

	static Ref<Window> Create(const WindowProps &props = WindowProps()) {
		return MakeRef<Window>(props);
	}

protected:
	EventCallbackFunc _event_callback;
	WindowProps _properties;
	GLFWwindow *_handle;
};

} // namespace en61
