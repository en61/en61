#include <core/world/world.h>

namespace en61 {

World::World(Ref<Window> window)
	: Scene(window) {

	_camera = MakeRef<Camera>(_window);
	_raycast = MakeRef<Raycast>(_window);
}

void World::OnEvent(Event &e) {
	_camera->OnEvent(e);
}

void World::OnUpdate() {
}

void World::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void World::UpdateCamera() {
	_camera->CalcFrameTime();
	_camera->ProcessInput();

	auto view = GetCamera()->GetViewMatrix();
	auto proj = GetCamera()->GetProjectionMatrix();
	_raycast->UpdateData(view, proj);
}

void World::Render() {
	_window->SwapBuffers();
	glfwPollEvents();
}

Ray World::GetOrthogonalRay() const {
	double x_center = _window->Width() / 2;
	double y_center = _window->Height() / 2;

	return _raycast->Create(_camera->GetPosition(), x_center, y_center);
}

} // namespace en61
