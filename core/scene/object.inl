#include <core/scene/object.h>

namespace en61 {

template <class _Type>
void Object::SetUniform(const std::string &name, _Type value) {
	assert(_shader && "shader=null");
	_shader->Set<_Type>(name, value);
}

} // namespace en61