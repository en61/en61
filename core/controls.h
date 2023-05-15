#pragma once

#include <core/opengl.h>

#include <memory>

namespace en61 {

struct MousePosition {
	double x;
	double y;
	
	static MousePosition Get();
	static void Set(const MousePosition &pos);
};

bool IsKeyPressed(int key);

} // namespace en61
