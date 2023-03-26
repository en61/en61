#pragma once

#include <core/opengl.h>
#include <core/window.h>
#include <core/resource.h>

#include <memory>

namespace en61 {

struct ApplicationProps {
	std::string title = "en61";
	std::string working_dir = "";

	ApplicationProps() = default;
	ApplicationProps(const std::string &t, const std::string &w)
		: title(t), working_dir(w) {}
};

class Application {
public:
	Application(const ApplicationProps &props = ApplicationProps());
	virtual ~Application();
   
	virtual void clear();
	virtual void render();
	virtual void start();

	static void enable_depth_testing();

	static void print_gl_version();
	static void error_callback(int error, const char *description);
	
	static Application *get() { return _instance; }
	std::shared_ptr<Window> window() const { return _window; }
	std::shared_ptr<ResourceManager> resource_manager() const { return _rmanager; }

protected:
	ApplicationProps _properties;
	std::shared_ptr<Window> _window;
	std::shared_ptr<ResourceManager> _rmanager;
	static Application *_instance;
};

} // namespace en61
