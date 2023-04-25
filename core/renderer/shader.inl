#include <core/renderer/shader.h>

namespace en61 {

template <typename _Type>
void Shader::Set(const std::string &name, _Type type) {
	std::cerr << "No uniform setter for " << typeid(_Type).name() << " type found!" << std::endl;
}

} // namespace en61