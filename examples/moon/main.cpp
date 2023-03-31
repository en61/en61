#include <core/renderer/vertex_array.h>
#include <core/opengl.h>
#include <core/application.h>
#include <core/renderer/camera.h>
#include <core/scene/object.h>
#include <memory>

#include "cloud.h"
#include "surface.h"

using namespace en61;

class MoonAnimation: public Application {
public:
	MoonAnimation(const WindowProps &props = WindowProps())
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
		_cloud.Render(model, view, projection);

		Application::Render();
	}

	static auto create(const WindowProps &props = {}) {
		return std::make_unique<MoonAnimation>(props);
	}

protected:
	Cloud _cloud;
	Surface _surface;
	Camera _camera;
};

int main() {
	auto app = MoonAnimation::create({2560, 1440, "Flame"});
	app->Start();
	return 0;
}
