#include <core/base/scene.h>

namespace en61 {

Scene::Scene(Ref<Window> window)
	: _window(window) {
}

void Scene::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Ref<Window> Scene::GetWindow() const {
	return _window;
}

void Scene::SetWindow(Ref<Window> window) {
	_window = window;
}

void Scene::Render() {
	_window->SwapBuffers();
	glfwPollEvents();
}

} // namespace en61
