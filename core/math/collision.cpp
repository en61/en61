#include <core/math/collision.h>

#include <list>

namespace en61 {

std::optional<size_t> GetNearestCollisionTarget(std::vector<Ref<Collidable>> targets, Ray ray) {

	using Collision = std::pair<size_t, double>;
	std::list<Collision> collisions;

	for (size_t i = 0; i < targets.size(); i++) {

		AABB box = targets[i]->GetBox();

		if (auto distance = GetIntersection(ray, box)) {
			collisions.emplace_back(i, distance.value());
		} 
	}

	if (collisions.empty())
		return std::nullopt;

	double minDist = std::numeric_limits<double>::max();
	size_t minCollisionIndex = 0;
	for (auto &collision: collisions) {
		if (std::abs(collision.second) < minDist) {
			minDist = std::abs(collision.second);
			minCollisionIndex = collision.first;
		}
	}
	return minCollisionIndex;
}

} // namespace en61
