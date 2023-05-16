#pragma once

namespace en61 {

struct MousePosition {
	double x;
	double y;
	
	static MousePosition Get();
	static void Set(const MousePosition &pos);
};

} // namespace en61
