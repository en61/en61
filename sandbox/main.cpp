#include <core/base/application.h>
#include <core/renderer/camera.h>
#include <core/world/object.h>
#include <core/world/world.h>
#include <core/world/crosshair.h>
#include <core/world/assets.h>
#include <core/math/collision.h>
#include <core/event/event.h>
#include <core/opengl.h>

#include <imgui/imgui.h>

using namespace en61;

static AssetManager assets("../assets/");

struct CubeAssets {
	Asset<Shader> shader{assets, "cube.vs", "cube.fs"};
	Asset<Shader> outlineShader{assets, "cube_outline.vs", "cube_outline.fs"};
	Asset<Model> model{assets, "cube/cube.obj"};
	Asset<Texture> texture{assets, "cube/blue_cube.png"};
};

struct TreeAssets {
	Asset<Shader> shader{assets, "tree.vs", "tree.fs"};
	Asset<Model> model{assets, "tree/tree.obj"};
};

struct CastleAssets {
	Asset<Shader> shader{assets, "castle.vs", "castle.fs"};
	Asset<Model> model{assets, "castle/castle.obj"};
};

struct SurfaceAssets {
	Asset<Shader> shader{assets, "surface.vs", "surface.fs"};
	Asset<Model> model{assets, "surface/surface.obj"};
	Asset<Texture> texture{assets, "surface/grass.png"};
};

struct SpaceshipAssets {
	Asset<Shader> shader{assets, "spaceship.vs", "spaceship.fs"};
	Asset<Model> model{assets, "spaceship/spaceship.obj"};
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

class Castle: public Object {
public:
	Castle(CastleAssets assets): _assets(assets) {
		SetShader(assets.shader);
		SetModel(assets.model);
	}

protected:
	CastleAssets _assets;
};

class Spaceship: public Object {
public:
	Spaceship(SpaceshipAssets assets): _assets(assets) {
		SetShader(assets.shader);
		SetModel(assets.model);
	}

	void Render(const glm::mat4 &view, const glm::mat4 &proj) override {
		auto pos = GetPosition();
		pos.z += _speed;
		SetPosition(pos);
		
		Object::Render(view, proj);
	}

	void RenderSpeedSelector() {
		ImGui::SliderFloat("spaceship speed", &_speed, 0.01f, 1.f);
	}

protected:
	SpaceshipAssets _assets;
	float _speed = 0.01f;
};

class Cube: public Object {
public:
	Cube(CubeAssets assets): _assets(assets) {
		AddTexture(_assets.texture);
		SetShader(_assets.shader);
		SetModel(_assets.model);
	}

	void EnableOutline() {
		_outline = true;
	}

	void HideOutline() {
		_outline = false;
	}

	void Render(const glm::mat4 &view, const glm::mat4 &projection) override {
		if (_outline) {
			SetShader(_assets.outlineShader);
			Object::RenderOutline(view, projection);
			SetShader(_assets.shader);
		}
		
		SetShader(_assets.shader);
		SetUniform("cubeColor", _color);
		Object::Render(view, projection);
	}

	void SetColor(glm::vec3 color) {
		_color = color;
	}

	operator AABB() {
		auto model = GetModelMatrix();
		auto min = glm::vec3(model * glm::vec4(-1, -1, -1, 1));
		auto max = glm::vec3(model * glm::vec4(1, 1, 1, 1));
		return { min, max };
	}

protected:
	CubeAssets _assets;
	glm::vec3 _color;
	bool _outline = false;
};


class Surface: public Object {
public:
	Surface() {
		SurfaceAssets assets;
		SetModel(assets.model);
		SetShader(assets.shader);
		AddTexture(assets.texture);
	}
};


class SandboxWorld: public World {
public:
	SandboxWorld(Ref<Window> window): World(window) {
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
			if (_currentItem == 0) PlaceBlock();
			if (_currentItem == 1) PlaceTree();
			if (_currentItem == 2) PlaceCastle();
			if (_currentItem == 3) PlaceSpaceship();
		}
	}

	void PlaceBlock() {
		auto cube = Cube(_cubeAssets);
		auto ray = GetOrthogonalRay();
		auto cubepos = ray.origin + ray.direction * 5.f;
		
		cube.SetPosition(cubepos);
		cube.SetColor(_selectedColor);
		_cubes.push_back(cube);
	}

	void PlaceCastle() {
		if (!_castle)
			_castle = MakeRef<Castle>(_castleAssets);
		
		auto ray = GetOrthogonalRay();
		auto cubepos = ray.origin + ray.direction * 5.f;
		cubepos.y = 0.f;
		_castle->SetPosition(cubepos);
	}

	void PlaceTree() {
		Tree tree(_treeAssets);
		auto ray = GetOrthogonalRay();
		auto cubepos = ray.origin + ray.direction * 5.f;
		cubepos.y = 0.f;

		tree.SetPosition(cubepos);
		_trees.push_back(tree);
	}

	void PlaceSpaceship() {
		Spaceship spaceship(_spaceshipAssets);
		if (!_spaceship)
			_spaceship = MakeRef<Spaceship>(_spaceshipAssets);
		
		auto ray = GetOrthogonalRay();
		auto cubepos = ray.origin + ray.direction * 5.f;
		_spaceship->SetPosition(cubepos);
	}

	void UpdateOutlineState() {

		std::vector<AABB> targets = { _cubes.begin(), _cubes.end() };
		auto newTarget = GetNearestCollisionTarget(targets, GetOrthogonalRay());

		if (newTarget != _target) {
			if (_target)
				_cubes[_target.value()].HideOutline();

			if (newTarget)
				_cubes[newTarget.value()].EnableOutline();

			_target = newTarget;
		}
	}
	
	void RenderMenu() override {

		ImGui::Begin("Sandbox");

		static constexpr std::array<const char*, 4> names = {
			"Block", "Tree", "Castle", "Spaceship"
		};

		ImGui::Text("Selected Block: %s", names[_currentItem]);

		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::ListBox("Choose item", &_currentItem, &names[0], names.size());

		ImGui::Spacing();
		ImGui::Spacing();

		if (_currentItem == 0) {
			ImGui::Text("Cube color selector");
			ImGui::PushItemWidth(600);
			ImGui::ColorPicker3("label", &_selectedColor.x);
		}

		GetCamera()->RenderSpeedSelector();

		ImGui::Spacing();
		ImGui::Spacing();

		if (_currentItem == 3 && _spaceship) {
			_spaceship->RenderSpeedSelector();
		}


		ImGui::End();
	}

	void OnEvent(Event &e) override {
		World::OnEvent(e);

		EventDispatcher ed(e);
		ed.Handle<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
		ed.Handle<MousePressedEvent>(BIND_EVENT_FN(OnMousePressed));
	}

	void OnUpdate() override {
		World::UpdateCamera();
		Scene::Clear();
		UpdateOutlineState();

		auto view = World::GetCamera()->GetViewMatrix();
		auto proj = World::GetCamera()->GetProjectionMatrix();

		_surface.Render(view, proj);

		if (_castle)
			_castle->Render(view, proj);

		if (_spaceship)
			_spaceship->Render(view, proj);

		_crosshair.Render(view, proj);

		for (auto &tree: _trees) {
			tree.Render(view, proj);
		}

		for (auto &cube: _cubes) {
			cube.Render(view, proj);
		}


		World::Render();
	}

protected:
	// objects
	std::vector<Cube> _cubes;
	std::vector<Tree> _trees;
	std::optional<size_t> _target;
	Ref<Castle> _castle;
	Ref<Spaceship> _spaceship;
	Crosshair _crosshair;
	Surface _surface;

	// assets
	SpaceshipAssets _spaceshipAssets;
	CastleAssets _castleAssets;
	CubeAssets _cubeAssets;
	TreeAssets _treeAssets;

	int _currentItem = 0;
	glm::vec3 _selectedColor;
};

class Sandbox: public Application {
public:
	Sandbox(const WindowProps &props): Application(props) {
		SetMainScene(MakeRef<SandboxWorld>(GetWindow()));
		World::SetMenuFontScale(2.0f);
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
