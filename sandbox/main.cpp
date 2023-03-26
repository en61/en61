#include <core/application.h>
#include <memory>

using namespace en61;

class Sandbox: public Application {
public:
    Sandbox() {
        enable_depth_testing();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    virtual void render() override {
        Application::clear();
        Application::render();
    }

    static auto create() {
        return std::make_unique<Sandbox>();
    }
};

int main() {
    auto app = Sandbox::create();
    app->start();
    return 0;
}
