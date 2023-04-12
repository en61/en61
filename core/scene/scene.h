#pragma once

#include <core/renderer/camera.h>

namespace en61 {

class Scene {
public:
    Scene(Ref<Window> window);

    virtual void OnEvent(Event &e);

    virtual void Clear();
    virtual void Update();
    virtual void Render();

    Ref<Camera> GetCamera() const { return _camera; }
    void SetCamera(Ref<Camera> camera) { _camera = camera; }

protected:
    Ref<Camera> _camera;
    Ref<Window> _window;
};

} // namespace en61
