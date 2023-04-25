#pragma once

#include <core/opengl.h>

#include <memory>

namespace en61 {

std::pair<double, double> MousePosition();

void SetMousePosition(double width, double height);

bool IsKeyPressed(int key);

} // namespace en61
