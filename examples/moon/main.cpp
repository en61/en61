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
		
		    enable_depth_testing();
		    glEnable(GL_CULL_FACE);
		    glCullFace(GL_BACK);
		    glEnable(GL_BLEND);
		    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	virtual void render() override {
		Application::clear(); 

		_camera.update();
		auto model = _camera.get_model();
		auto view = _camera.get_view();
		auto projection = _camera.get_projection();

		_surface.render(model, view, projection);
		_cloud.render(model, view, projection);

		Application::render();
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
	app->start();
	return 0;
}
