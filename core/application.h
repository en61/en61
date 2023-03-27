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
   
	virtual void clear();
	virtual void render();
	virtual void start();

	static void enable_depth_testing();

	static void print_gl_version();
	static void error_callback(int error, const char *description);
	
	static Application *get() { return _instance; }
	std::shared_ptr<Window> window() const { return _window; }

protected:
	std::shared_ptr<Window> _window;
	static Application *_instance;
};

} // namespace en61
