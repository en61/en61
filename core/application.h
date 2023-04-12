#pragma once

#include <core/opengl.h>
#include <core/window.h>
#include <core/resource.h>

namespace en61 {

class Application {
public:
	Application(const WindowProps &win_props = WindowProps());
	virtual ~Application() = default;
   
	virtual void OnUpdate() = 0;
	virtual void Run();

	static void PrintGLVersion();
	static void ErrorCallback(int error, const char *description);
	
	static std::pair<int, int> GetMonitorResolution();

	static Application *Get() { return _instance; }
	Ref<Window> GetWindow() const { return _window; }

protected:
	Ref<Window> _window;

	static Application *_instance;
};

} // namespace en61
