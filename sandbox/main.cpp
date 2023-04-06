#include <core/application.h>
#include <core/renderer/camera.h>
#include <core/window.h>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

#include "glm/ext/matrix_transform.hpp"
#include "surface.h"
#include "cube.h"

using namespace en61;

class Sandbox: public Application {
public:
	Sandbox(const WindowProps &props)
		: Application(props), _camera(_window) {

		EnableDepthTesting();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	virtual void Render() override {
		Application::Clear();

		_camera.Update();
		auto view = _camera.GetView();
		auto projection = _camera.GetProjection();

		
		glDepthMask(false);

		_surface.Render(_surface.GetModel(), view, projection);
		_cube.Render(_cube.GetModel(), view, projection);

		glDepthMask(true);

		Application::Render();
	}

	static auto create(const WindowProps &props) {
		return std::make_unique<Sandbox>(props);
	}

protected:
	Surface _surface;
	Cube _cube;
	Camera _camera;
};

int main() {
	auto app = Sandbox::create({2560, 1440, "Sandbox"});
	app->Start();
	return 0;
}
