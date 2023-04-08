#include <core/renderer/api.h>
#include <core/opengl.h>

namespace en61 {

void InitAPI() {

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

} // namespace en61
