#pragma once

#include <core/math/intersect.h>
#include <core/math/raycast.h>

#include <span>

namespace en61 {

std::optional<size_t> GetNearestCollisionTarget(std::span<AABB> targets, Ray ray);

} // namespace en61
