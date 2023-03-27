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

        Application::render();
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
    app->start();
    return 0;
}
