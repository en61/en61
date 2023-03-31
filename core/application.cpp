#include <core/window.h>
#include <core/application.h>

#include <cassert>
#include <unistd.h>
#include <utility>

namespace en61 {

Application *Application::_instance{nullptr}; 

Application::Application(const WindowProps &win_props) {

	assert((!_instance && "Application already launched!"));
	_instance = this;

	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = Window::Create(win_props);
	_window->MakeCurrentContext();

	gladLoadGL();
	PrintGLVersion();
	glfwSwapInterval(0);
}

void Application::EnableDepthTesting() {
	glEnable(GL_DEPTH_TEST);
}

Application::~Application() {
}

void Application::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

std::pair<int, int> Application::GetMonitorResolution() {
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return std::make_pair(mode->width, mode->height);
}

void Application::Render() {
	_window->SwapBuffers();
	glfwPollEvents();
}

void Application::Start() {

	double lasttime = glfwGetTime();
	static constexpr double targetFPS = 60.f;

	while (!_window->ShouldClose()) {
		Render();

		while (glfwGetTime() < lasttime + 1.0 / targetFPS) {
			usleep(1);
		}

		lasttime += 1.0 / targetFPS;
	}
}

void Application::PrintGLVersion() {
	std::cerr << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void Application::ErrorCallback(int error, const char *description) {
	(void)error;
	std::cerr << "error: " << description << std::endl;
}

} // namespace en61
