#include <core/utils/random.h>

#include <stdlib.h>

namespace en61 {

float RandomFloat() {
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

} // namespace en61
