#include <core/application.h>
#include <core/renderer/camera.h>
#include <core/window.h>
#include <memory>

#include "surface.h"

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
		auto model = _camera.GetModel();
		auto view = _camera.GetView();
		auto projection = _camera.GetProjection();

		_surface.Render(model, view, projection);

		Application::Render();
	}

	static auto create(const WindowProps &props) {
		return std::make_unique<Sandbox>(props);
	}

protected:
	Surface _surface;
	Camera _camera;
};

int main() {
	auto app = Sandbox::create({1920, 1080, "Sandbox"});
	app->Start();
	return 0;
}
