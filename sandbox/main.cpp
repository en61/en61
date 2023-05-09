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

struct CubeAssets {
	Ref<Shader> shader, outlineShader;
	Ref<Texture> texture;
	Ref<Model> model;
};

class Cube: public Object {
public:
	Cube(CubeAssets assets): _assets(assets) {
		AddTexture(_assets.texture);
		SetShader(_assets.shader);
		SetModel(_assets.model);
	}

	void EnableOutline() {
		SetShader(_assets.outlineShader);
		_outline = true;
	}

	void HideOutline() {
		SetShader(_shader);
		_outline = false;
	}

	void Render(const glm::mat4 &view, const glm::mat4 &projection) override {
		if (_outline) {
			glLineWidth(5);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			SetShader(_assets.outlineShader);
			Object::Render(view, projection);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		SetShader(_assets.shader);
		Object::Render(view, projection);
	}

protected:
	CubeAssets _assets;
	bool _outline = false;
};


class Surface: public Object {
public:
	Surface() {
		auto model = MakeRef<Model>();
		auto shader = MakeRef<Shader>();
		auto texture = MakeRef<Texture>();

		shader->Load("../assets/surface.vert", "../assets/surface.frag");
		model->Load("../assets/surface.obj");
		texture->Load("../assets/grass.png");

		SetModel(model);
		SetShader(shader);
		AddTexture(texture);
	}
};


class SandboxScene: public Scene {
public:
	SandboxScene(Ref<Window> window): Scene(window) {
		LoadAssets();
		_current_cube = MakeRef<Cube>(_assets);
	}

	void LoadAssets() {
		_assets.model = MakeRef<Model>();
		_assets.texture = MakeRef<Texture>();

		_assets.texture->Load("../assets/blue_cube.png");
		_assets.model->Load("../assets/cube.obj");

		_assets.shader = MakeRef<Shader>();
		_assets.outlineShader = MakeRef<Shader>();

		_assets.shader->Load("../assets/cube.vert", "../assets/cube.frag");
		_assets.outlineShader->Load("../assets/cube_outline.vert", "../assets/cube_outline.frag");
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
		if (_current_cube) {
			auto ray = GetOrthogonalRay();
			auto cubepos = ray.origin + ray.direction * 5.f;
			
			_current_cube->SetPosition(cubepos);
			_cubes.push_back(_current_cube);
		}
		
		_current_cube = MakeRef<Cube>(_assets);
	}

	std::optional<size_t> GetTargetedCube() {

		using Collision = std::pair<size_t, double>;
		std::list<Collision> collisions;

		Ray ray = GetOrthogonalRay();

		for (size_t i = 0; i < _cubes.size(); i++) {

			auto model = _cubes[i]->GetModel();
			AABB box = {
				glm::vec3(model * glm::vec4(-1, -1, -1, 1)),
				glm::vec3(model * glm::vec4(1, 1, 1, 1)),
			};
			
			if (auto distance = GetIntersection(ray, box)) {
				collisions.emplace_back(i, distance.value());
			} 
		}
		if (collisions.empty())
			return std::nullopt;
	
		double minDist = std::numeric_limits<double>::max();
		size_t minCollisionId = 0;
		for (auto &collision: collisions) {
			if (std::abs(collision.second) < minDist) {
				minDist = std::abs(collision.second);
				minCollisionId = collision.first;
			}
		}
		return minCollisionId;
	}

	void UpdateOutlineState() {
		auto newTarget = GetTargetedCube();
		if (newTarget != _target) {
			if (_target)
				_cubes[_target.value()]->HideOutline();

			if (newTarget)
				_cubes[newTarget.value()]->EnableOutline();

			_target = newTarget;
		}
	}

	void OnEvent(Event &e) override {
		EventDispatcher ed(e);
		ed.Register<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
		ed.Register<MousePressedEvent>(BIND_EVENT_FN(OnMousePressed));

		_camera->OnEvent(e);
	}

	void OnUpdate() override {
		Scene::UpdateCamera();
		Scene::Clear();
		UpdateOutlineState();

		auto view = Scene::GetCamera()->GetView();
		auto proj = Scene::GetCamera()->GetProjection();

		_surface.Render(view, proj);
		_crosshair.Render(view, proj);

		for (auto &cube: _cubes) {
			cube->Render(view, proj);
		}

		Scene::Render();
	}

protected:
	std::vector<Ref<Cube>> _cubes;
	std::optional<size_t> _target;
	Ref<Cube> _current_cube;
	Crosshair _crosshair;
	Surface _surface;
	CubeAssets _assets;
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
