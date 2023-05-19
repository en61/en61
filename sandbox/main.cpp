#include <core/base/application.h>
#include <core/renderer/camera.h>
#include <core/world/object.h>
#include <core/world/world.h>
#include <core/world/crosshair.h>
#include <core/world/assets.h>
#include <core/math/collision.h>
#include <core/event/event.h>
#include <core/opengl.h>

using namespace en61;

static AssetManager assets("../assets/");

struct CubeAssets {
	Asset<Shader> shader{assets, "cube.vert", "cube.frag"};
	Asset<Shader> outlineShader{assets, "cube_outline.vert", "cube_outline.frag"};
	Asset<Model> model{assets, "cube.obj"};
	Asset<Texture> texture{assets, "blue_cube.png"};
};

struct TreeAssets {
	Asset<Shader> shader{assets, "tree.vert", "tree.frag"};
	Asset<Model> model{assets, "tree.obj"};
};

class Tree: public Object {
public:
	Tree(TreeAssets assets): _assets(assets) {
		SetShader(assets.shader);
		SetModel(assets.model);
	}

protected:
	TreeAssets _assets;
};

class Cube: public Object, public Collidable {
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

	AABB GetBox() const override {
		auto model = GetModelMatrix();
		auto min = glm::vec3(model * glm::vec4(-1, -1, -1, 1));
		auto max = glm::vec3(model * glm::vec4(1, 1, 1, 1));
		return { min, max };
	}

	void Render(const glm::mat4 &view, const glm::mat4 &projection) override {
		if (_outline) {
			SetShader(_assets.outlineShader);
			Object::RenderOutline(view, projection);
			SetShader(_assets.shader);
		}

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


class SandboxWorld: public World {
public:
	SandboxWorld(Ref<Window> window): World(window) {
		_current_cube = MakeRef<Cube>(_cubeAssets);
		_tree = MakeRef<Tree>(_treeAssets);
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
		
		_current_cube = MakeRef<Cube>(_cubeAssets);
	}

	void UpdateOutlineState() {

		std::vector<Ref<Collidable>> targets = { _cubes.begin(), _cubes.end() };
		auto newTarget = GetNearestCollisionTarget(targets, GetOrthogonalRay());

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
		ed.Handle<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
		ed.Handle<MousePressedEvent>(BIND_EVENT_FN(OnMousePressed));

		_camera->OnEvent(e);
	}

	void OnUpdate() override {
		World::UpdateCamera();
		Scene::Clear();
		UpdateOutlineState();

		auto view = World::GetCamera()->GetViewMatrix();
		auto proj = World::GetCamera()->GetProjectionMatrix();

		_surface.Render(view, proj);
		_tree->Render(view, proj);
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
	CubeAssets _cubeAssets;
	TreeAssets _treeAssets;
	Ref<Tree> _tree;
};

class Sandbox: public Application {
public:
	Sandbox(const WindowProps &props): Application(props) {
		SetMainScene(MakeRef<SandboxWorld>(GetWindow()));
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
