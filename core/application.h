#pragma once

#include <core/opengl.h>
#include <core/window.h>
#include <core/resource.h>
#include <core/scene/interfaces.h>

namespace en61 {

class Application {
public:
	Application(const WindowProps &win_props = WindowProps());
	virtual ~Application() = default;
   
	void SetMainScene(Ref<SceneInterface> scene);
	virtual void Run();

	static void PrintGLVersion();
	static void ErrorCallback(int error, const char *description);
	
	static std::pair<int, int> GetMonitorResolution();

	static Application *Get() { return _instance; }
	Ref<Window> GetWindow() const { return _window; }

private:
	virtual void OnEvent(Event &event);
	virtual void OnUpdate(); 

protected:
	Ref<Window> _window;
	Ref<SceneInterface> _scene;

	static Application *_instance;
};

} // namespace en61
