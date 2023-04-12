#include <core/application.h>
#include <core/renderer/camera.h>
#include <core/scene/object.h>
#include <core/scene/scene.h>

using namespace en61;

class Cube: public Object {
public:
	Cube() {
		auto mesh = MakeRef<Mesh>();
		auto shader = MakeRef<Shader>();
		auto texture = MakeRef<Texture>();

		mesh->Load("../assets/cube.obj");
		texture->Load("../assets/cube.png");
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
		: Scene(window) { }

	void Render() override {
		Scene::Update();
		Scene::Clear();

		auto view = Scene::GetCamera()->GetView();
		auto proj = Scene::GetCamera()->GetProjection();

		_surface.Render(view, proj);
		
		_cubes[0].SetPosition({2, 0.5, 0});
		_cubes[1].SetPosition({3, 1.5, 0});
		_cubes[2].SetPosition({4, 2.5, 0});
		_cubes[3].SetPosition({3, 3.5, 0});
		_cubes[4].SetPosition({2, 4.5, 0});
		_cubes[5].SetPosition({1, 3.5, 0});
		_cubes[6].SetPosition({0, 2.5, 0});
		_cubes[7].SetPosition({1, 1.5, 0});

		for (size_t i = 0; i < 8; i++)
			_cubes[i].Render(view, proj);

		Scene::Render();
	}

protected:
	Cube _cubes[8];
	Surface _surface;
};

class Sandbox: public Application {
public:

	Sandbox(const WindowProps &props)
		: Application(props), _scene(GetWindow()) {
	}

	void OnUpdate() override {
		_scene.Render();
	}

	static auto Create(const WindowProps &props = {}) {
		return MakeScoped<Sandbox>(props);
	}

protected:
	SandboxScene _scene;
};

int main() {
	auto app = Sandbox::Create({2560, 1440, "EN61"});
	app->Run();
	return 0;
}
