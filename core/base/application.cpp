#include <core/base/application.h>

#include <core/renderer/api.h>
#include <core/platform/system.h>

#include <cassert>
#include <utility>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace en61 {

Application *Application::_instance{nullptr}; 

Application::Application(const WindowProps &win_props) {
	
	assert((!_instance && "Application already launched!"));
	_instance = this;

	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = Window::Create(win_props);
	_window->MakeCurrentContext();

	gladLoadGL();
	PrintGLVersion();
	glfwSwapInterval(0);

	InitAPI();

	_window->SetEventCallback(BIND_EVENT_FN(OnEvent));


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO &io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window->NativeHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

}

std::pair<int, int> Application::GetMonitorResolution() {
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return std::make_pair(mode->width, mode->height);
}

void Application::SetMainScene(Ref<SceneBase> scene) {
	_scene = scene;
}

void Application::OnEvent(Event &event) {
	if (_scene)
		_scene->OnEvent(event);
}

void Application::OnUpdate() {
	if (_scene)
		_scene->OnUpdate();
}

void Application::Run() {

	double lasttime = glfwGetTime();
	static constexpr double target_fps = 144.f;

	while (!_window->ShouldClose()) {
		OnUpdate();

		while (glfwGetTime() < lasttime + 1.0 / target_fps) {
			Sleep(1);
		}

		lasttime += 1.0 / target_fps;
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
