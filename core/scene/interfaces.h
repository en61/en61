#pragma once

#include <core/event/event.h>

namespace en61 {

class SceneInterface {
public:
	virtual void OnUpdate() = 0;
	virtual void OnEvent(Event &event) = 0;
};

} // namespace en61
