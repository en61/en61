#include <core/scene/scene.h>

namespace en61 {

Scene::Scene(Ref<Window> window)
	: _window(window) {

	_camera = MakeRef<Camera>(_window);
	_raycast = MakeRef<Raycast>(_window);
}

void Scene::OnEvent(Event &e) {
	_camera->OnEvent(e);
}

void Scene::OnUpdate() {
}

void Scene::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::UpdateCamera() {
	_camera->CalcFrameTime();
	_camera->ProcessInput();

	auto view = GetCamera()->GetViewMatrix();
	auto proj = GetCamera()->GetProjectionMatrix();
	_raycast->UpdateData(view, proj);
}

void Scene::Render() {
	_window->SwapBuffers();
	glfwPollEvents();
}

Ray Scene::GetOrthogonalRay() const {
	double x_center = _window->Width() / 2;
	double y_center = _window->Height() / 2;

	return _raycast->Create(_camera->GetPosition(), x_center, y_center);
}

} // namespace en61
