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
	Asset<Shader> shader{assets, "cube.vert", "cube.frag"};
	Asset<Shader> outlineShader{assets, "cube_outline.vert", "cube_outline.frag"};
	Asset<Model> model{assets, "cube.obj"};
	Asset<Texture> texture{assets, "blue_cube.png"};
};

struct TreeAssets {
	Asset<Shader> shader{assets, "tree.vert", "tree.frag"};
	Asset<Model> model{assets, "tree.obj"};
};

struct CastleAssets {
	Asset<Shader> shader{assets, "castle.vert", "castle.frag"};
	Asset<Model> model{assets, "castle.obj"};
};

struct SurfaceAssets {
	Asset<Shader> shader{assets, "surface.vert", "surface.frag"};
	Asset<Model> model{assets, "surface.obj"};
	Asset<Texture> texture{assets, "grass.png"};
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

class Cube: public Object, public Collidable {
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
		
		SetShader(_assets.shader);
		SetUniform("cubeColor", _color);
		Object::Render(view, projection);
	}

	void SetColor(glm::vec3 color) {
		_color = color;
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
		}
	}

	void PlaceBlock() {
		auto cube = MakeRef<Cube>(_cubeAssets);
		auto ray = GetOrthogonalRay();
		auto cubepos = ray.origin + ray.direction * 5.f;
		
		cube->SetPosition(cubepos);
		cube->SetColor(_selectedColor);
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
	
	void RenderMenu() override {

		ImGui::Begin("Sandbox");

		static constexpr std::array<const char*, 3> names = {
			"Block", "Tree", "Castle"
		};

		ImGui::Text("Selected Block: %s", names[_currentItem]);

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::ListBox("Choose item", &_currentItem, &names[0], names.size())) {

		}

		ImGui::Spacing();
		ImGui::Spacing();

		if (_currentItem == 0) {
			ImGui::Text("Cube color selector");
			ImGui::PushItemWidth(600);
			ImGui::ColorPicker3("label", &_selectedColor.x);
		}

		ImGui::SliderFloat("camera speed", &GetCamera()->GetMoveSpeed(), 0, 30);

		ImGui::Spacing();
		ImGui::Spacing();


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

		_crosshair.Render(view, proj);

		for (auto &tree: _trees) {
			tree.Render(view, proj);
		}

		for (auto &cube: _cubes) {
			cube->Render(view, proj);
		}


		World::Render();
	}

protected:
	// objects
	std::vector<Ref<Cube>> _cubes;
	std::vector<Tree> _trees;
	std::optional<size_t> _target;
	Ref<Castle> _castle;
	Crosshair _crosshair;
	Surface _surface;

	// assets
	CubeAssets _cubeAssets;
	CastleAssets _castleAssets;
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
