#pragma once

#include <core/math/raycast.h>

#include <optional>

namespace en61 {

struct AABB {
	glm::vec3 min;
	glm::vec3 max;
};

std::optional<double> GetIntersection(Ray ray, AABB box);

} // namespace en61
