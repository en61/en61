#include <core/world/world.h>

#include <core/event/event.h>
#include <core/event/key.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace en61 {

World::World(Ref<Window> window)
	: Scene(window) {

	_camera = MakeRef<Camera>(_window);
	_raycast = MakeRef<Raycast>(_window->Width(), _window->Height());
}

void World::OnEvent(Event &event) {
	EventDispatcher e(event);
	e.Handle<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));

	if (!_menuOpen)	
		_camera->OnEvent(event);
}


void World::OnKeyPressed(KeyPressedEvent &e) {
	if (e.GetKeycode() == GLFW_KEY_ESCAPE) {
		ToogleMenu();
	}
}

void World::OnUpdate() {
}

void World::Render() {
	if (_menuOpen) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		this->RenderMenu();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	Scene::Render();
}

void World::SetMenuFontScale(float scale) {
	ImFontConfig cfg;
	cfg.SizePixels = 13 * scale;
	ImGui::GetIO().Fonts->AddFontDefault(&cfg);
}

void World::ToogleMenu() {
	if (_menuOpen) {
		GetWindow()->LockMouse();
	}
	else {
		GetWindow()->UnlockMouse();
		_camera->ResetMousePosition();
	}

	_menuOpen = !_menuOpen;
}

void World::RenderMenu() {
	ImGui::Begin("Window");
	ImGui::End();
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
