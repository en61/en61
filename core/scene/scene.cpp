#include "scene.h"

namespace en61 {

Scene::Scene(Ref<Window> window)
    : _window(window) {

    _camera = MakeRef<Camera>(_window);
    _window->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

void Scene::OnEvent(Event &e) {
	_camera->OnEvent(e);
}

void Scene::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::Update() {
    _camera->CalcFrameTime();
	_camera->ProcessInput();
}

void Scene::Render() {
    _window->SwapBuffers();
	glfwPollEvents();
}


} // namespace en61