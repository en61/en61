#include <core/window.h>
#include <core/application.h>

#include <cassert>
#include <unistd.h>

namespace en61 {

Application *Application::_instance{nullptr}; 

Application::Application(const ApplicationProps &props) : _properties(props) {

	assert((!_instance && "Application already launched!"));
	_instance = this;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_rmanager = ResourceManager::create(_properties.working_dir);

	_window = Window::create(WindowProps(_properties.title));
	_window->make_current_context();

	gladLoadGL();
	print_gl_version();
	glfwSwapInterval(0);
}

void Application::enable_depth_testing() {
	glEnable(GL_DEPTH_TEST);
}

Application::~Application() {
}

void Application::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::render() {
	_window->swap_buffers();
	glfwPollEvents();
}

void Application::start() {

	double lasttime = glfwGetTime();
	static constexpr double target_fps = 60.f;

	while (!_window->should_close()) {
		render();

		while (glfwGetTime() < lasttime + 1.0 / target_fps) {
			usleep(1);
		}

		lasttime += 1.0 / target_fps;
	}
}

void Application::print_gl_version() {
	std::cerr << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void Application::error_callback(int error, const char *description) {
	(void)error;
	std::cerr << "error: " << description << std::endl;
}

} // namespace en61
