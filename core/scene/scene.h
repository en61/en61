#pragma once

#include <core/renderer/camera.h>
#include <core/scene/interfaces.h>
#include <core/math/raycast.h>

namespace en61 {

class Scene: public SceneInterface {
public:
	Scene(Ref<Window> window);

	virtual void OnEvent(Event &e);
	virtual void OnUpdate();

	virtual void Clear();
	virtual void UpdateCamera();
	virtual void Render();

	Ref<Camera> GetCamera() const { return _camera; }
	void SetCamera(Ref<Camera> camera) { _camera = camera; }

	Ref<Raycast> GetRaycast() const { return _raycast; }
	void SetRaycast(Ref<Raycast> raycast) { _raycast = raycast; }
	
	Ray GetOrthogonalRay() const;

protected:
	Ref<Camera> _camera;
	Ref<Window> _window;
	Ref<Raycast> _raycast;
};

} // namespace en61
