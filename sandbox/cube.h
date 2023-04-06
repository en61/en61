#include <core/scene/object.h>
#include <core/renderer/texture.h>

using namespace en61;

class Cube: public Object {
public:
	Cube();

protected:
	std::shared_ptr<Texture> _texture;
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Shader> _shader;
};
