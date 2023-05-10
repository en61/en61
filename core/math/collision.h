#pragma once

#include <core/math/intersect.h>
#include <core/math/raycast.h>

#include <optional>
#include <list>

namespace en61 {

class Collidable {
public:
	virtual AABB GetBox() const = 0; 
};

template <class _T>
concept IsCollidableObject = std::convertible_to<_T, Collidable>;

template <class _T>
concept IsCollidablePointer = std::convertible_to<_T, Collidable*>
	|| std::convertible_to<_T, Ref<Collidable>>
	|| std::convertible_to<_T, Scoped<Collidable>>
	|| std::convertible_to<_T, WeakRef<Collidable>>;

template <class _T>
concept IsCollidable = IsCollidableObject<_T> || IsCollidablePointer<_T>;


template <IsCollidable _T>
std::optional<size_t> GetNearestCollisionTarget(std::vector<_T> targets, Ray ray) {

	using Collision = std::pair<size_t, double>;
	std::list<Collision> collisions;

	for (size_t i = 0; i < targets.size(); i++) {

		AABB box;
		if constexpr(IsCollidablePointer<_T>)
			box = targets[i]->GetBox();
		else
			box = targets[i].GetBox();

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
