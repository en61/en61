#pragma once

#include <core/opengl.h>
#include <memory>

namespace en61 {

std::pair<double, double> mouse_position();

void set_mouse_position(double width, double height);

bool is_key_pressed(int key);

} // namespace en61
