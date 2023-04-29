#include <core/application.h>
#include <core/renderer/camera.h>
#include <core/renderer/interfaces.h>
#include <core/scene/object.h>
#include <core/scene/scene.h>
#include <core/scene/crosshair.h>
#include <core/math/raycast.h>
#include <core/math/intersect.h>
#include <core/event/event.h>
#include <core/opengl.h>

using namespace en61;


class Cube: public Object {
public:
	Cube() {
		auto mesh = MakeRef<Mesh>();
		auto shader = MakeRef<Shader>();
		auto texture = MakeRef<Texture>();

		mesh->Load("../assets/cube.obj");
		texture->Load("../assets/blue_cube.png");
		shader->Load("../assets/cube.vert", "../assets/cube.frag");

		AddTexture(texture);
		SetShader(shader);
		SetMesh(mesh);
	}
};


class Surface: public Object {
public:
	Surface() {
		auto mesh = MakeRef<Mesh>();
		auto shader = MakeRef<Shader>();
		auto texture = MakeRef<Texture>();

		shader->Load("../assets/surface.vert", "../assets/surface.frag");
		mesh->Load("../assets/surface.obj");
		texture->Load("../assets/grass.png");

		SetMesh(mesh);
		SetShader(shader);
		AddTexture(texture);
	}
};


class SandboxScene: public Scene {
public:
	SandboxScene(Ref<Window> window)
		: Scene(window), _raycast(window) {
			_current_cube = MakeRef<Cube>();
		}

	void OnKeyPressed(KeyPressedEvent &event) {
		if (event.GetKeycode() == GLFW_KEY_P) {
			std::cout << "p pressed" << std::endl;
			PlaceBlock();
		}
	}
	
	void OnMousePressed(MousePressedEvent &event) {
		if (event.GetButtonCode() == GLFW_MOUSE_BUTTON_RIGHT) {
			std::cout << "right mouse button pressed" << std::endl;
			PlaceBlock();
		}
	}

	void PlaceBlock() {
		if (_current_cube)
			_cubes.push_back(_current_cube);
		
		_current_cube = MakeRef<Cube>();
	}

	void OnMouseMoved(MouseMovedEvent &e) {

		double x_center = _window->Width() / 2;
		double y_center = _window->Height() / 2;
		Ray ray = _raycast.Create(_camera->GetPosition(), x_center, y_center);

		for (size_t i = 0; i < _cubes.size(); i++) {

			auto model = _cubes[i]->GetModel();
			AABB box = {
				glm::vec3(model * glm::vec4(-1, -1, -1, 1)),
				glm::vec3(model * glm::vec4(1, 1, 1, 1)),
			};
			
			std::cout << "cube " << i << ":";
			if (auto distance = GetIntersection(ray, box)) {
				std::cout <<  " distance [" << distance.value() << "]" << std::endl;
			} 
			else {
				std::cout << " no intersection" << std::endl;
			}
		}
	}

	void OnEvent(Event &e) override {
		EventDispatcher ed(e);
		ed.Register<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
		ed.Register<MousePressedEvent>(BIND_EVENT_FN(OnMousePressed));
		ed.Register<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoved));

		_camera->OnEvent(e);
	}

	void OnUpdate() override {
		Scene::UpdateCamera();
		Scene::Clear();

		auto view = Scene::GetCamera()->GetView();
		auto proj = Scene::GetCamera()->GetProjection();

		_surface.Render(view, proj);
		_raycast.UpdateData(view, proj);

		double x_center = _window->Width() / 2;
		double y_center = _window->Height() / 2;

		auto ray = _raycast.Create(_camera->GetPosition(), x_center, y_center);
		auto cubepos = ray.origin + ray.direction * 5.f;
		
		_current_cube->SetPosition(cubepos);
		//_current_cube->Render(view, proj);
		_crosshair.Render(view, proj);

		for (size_t i = 0; i < _cubes.size(); i++) {
			_cubes[i]->Render(view, proj);
		}

		Scene::Render();
	}

protected:
	std::vector<Ref<Cube>> _cubes; 
	Ref<Cube> _current_cube;
	Crosshair _crosshair;
	Surface _surface;
	Raycast _raycast;
};

class Sandbox: public Application {
public:
	Sandbox(const WindowProps &props): Application(props) {
		SetMainScene(MakeRef<SandboxScene>(GetWindow()));
	}

	static auto Create(const WindowProps &props = {}) {
		return MakeScoped<Sandbox>(props);
	}
};

int main() {
	auto app = Sandbox::Create({2560, 1440, "EN61"});
	app->Run();
	return 0;
}
