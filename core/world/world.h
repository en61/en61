#pragma once

#include <core/base/scene.h>
#include <core/renderer/camera.h>
#include <core/math/raycast.h>

namespace en61 {

class World: public Scene {
public:
	World(Ref<Window> window);

	virtual void OnEvent(Event &e);
	virtual void OnUpdate();

	virtual void UpdateCamera();

	Ref<Camera> GetCamera() const { return _camera; }
	void SetCamera(Ref<Camera> camera) { _camera = camera; }

	Ref<Raycast> GetRaycast() const { return _raycast; }
	void SetRaycast(Ref<Raycast> raycast) { _raycast = raycast; }
	
	Ray GetOrthogonalRay() const;

protected:
	Ref<Camera> _camera;
	Ref<Raycast> _raycast;
};

} // namespace en61
