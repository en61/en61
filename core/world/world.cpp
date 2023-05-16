#include <core/world/world.h>

namespace en61 {

World::World(Ref<Window> window)
	: Scene(window) {

	_camera = MakeRef<Camera>(_window);
	_raycast = MakeRef<Raycast>(_window->Width(), _window->Height());
}

void World::OnEvent(Event &e) {
	_camera->OnEvent(e);
}

void World::OnUpdate() {
}

void World::UpdateCamera() {
	_camera->CalcFrameTime();
	_camera->ProcessInput();

	auto view = GetCamera()->GetViewMatrix();
	auto proj = GetCamera()->GetProjectionMatrix();
	_raycast->UpdateMatrices(view, proj);
	_raycast->UpdateWindowSize(_window->Width(), _window->Height());
}

Ray World::GetOrthogonalRay() const {
	return _raycast->CreateFromScreenCentre(_camera->GetPosition());
}

} // namespace en61
