#pragma once

#include <core/renderer/camera.h>
#include <core/math/raycast.h>

namespace en61 {

class SceneBase {
public:
	virtual void OnUpdate() = 0;
	virtual void OnEvent(Event &event) = 0;
};

class Scene: public SceneBase {
public:
	Scene(Ref<Window> window);

	virtual void Clear();
	virtual void Render();

	Ref<Window> GetWindow() const;
	void SetWindow(Ref<Window> window);

protected:
	Ref<Window> _window;
};

} // namespace en61
