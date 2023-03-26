#include <stdlib.h>

namespace en61 {

inline float random_float() {
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

} // namespace en61
