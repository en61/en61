#pragma once

#include <core/opengl.h>
#include <core/base/scene.h>
#include <core/base/window.h>

namespace en61 {

class Application {
public:
	Application(const WindowProps &win_props = WindowProps());
	virtual ~Application() = default;
   
	void SetMainScene(Ref<SceneBase> scene);

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
	Ref<SceneBase> _scene;

	static Application *_instance;
};

} // namespace en61
