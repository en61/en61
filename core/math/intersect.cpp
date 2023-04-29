#include <core/math/intersect.h>

namespace en61 {

std::optional<double> GetIntersection(Ray ray, AABB box) {

	double tmax = std::numeric_limits<double>::max();
	double tmin = std::numeric_limits<double>::min();

	for (size_t i = 0; i < 3; i++) {
		if (ray.direction[i] != 0.f) {
			double t1 = (box.min[i] - ray.origin[i]) / ray.direction[i];
			double t2 = (box.max[i] - ray.origin[i]) / ray.direction[i];

			tmin = std::max(tmin, std::min(t1, t2));
			tmax = std::min(tmax, std::max(t1, t2));

		}
		else if (ray.origin[i] <= box.min[i] || ray.origin[i] >= box.max[i]) {
			return std::nullopt;
		}
	}

	if (tmax < tmin || tmax < 0.f)
		return std::nullopt;
	
	return tmin;
}

} // namespace en61
