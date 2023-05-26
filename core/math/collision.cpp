#include <core/math/collision.h>

#include <limits>
#include <list>

namespace en61 {

std::optional<size_t> GetNearestCollisionTarget(std::span<AABB> targets, Ray ray) {

	size_t minTarget = 0;
	double minDist = std::numeric_limits<double>::max();

	bool anyTargetHit = false;

	for (size_t i = 0; i < targets.size(); i++) {
		if (auto distance = GetIntersection(ray, targets[i])) {
			anyTargetHit |= true;
			double absDistance = std::abs(distance.value());
			if (absDistance < minDist) {
				minTarget = i;
				minDist = absDistance;
			}
		}
	}

	if (!anyTargetHit)
		return std::nullopt;

	return minTarget;
}

} // namespace en61
