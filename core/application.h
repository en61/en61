#pragma once

#include <core/opengl.h>
#include <core/window.h>
#include <core/resource.h>

#include <memory>

namespace en61 {

class Application {
public:
	Application(const WindowProps &win_props = WindowProps());
	virtual ~Application();
   
	virtual void Clear();
	virtual void Render();
	virtual void Start();

	static void EnableDepthTesting();

	static void PrintGLVersion();
	static void ErrorCallback(int error, const char *description);
	
    static std::pair<int, int> GetMonitorResolution();

	static Application *Get() { return _instance; }
	std::shared_ptr<Window> GetWindow() const { return _window; }

protected:
	std::shared_ptr<Window> _window;
	static Application *_instance;
};

} // namespace en61
