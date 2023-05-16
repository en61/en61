#pragma once

#include <core/math/intersect.h>
#include <core/math/raycast.h>

#include <vector>

namespace en61 {

class Collidable {
public:
	virtual AABB GetBox() const = 0; 
};

std::optional<size_t> GetNearestCollisionTarget(std::vector<Ref<Collidable>> targets, Ray ray);

} // namespace en61
