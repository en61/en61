#include <core/utils/resource.h>

namespace en61 {

ResourceManager::ResourceManager(const std::string &workingDir) {
	SetBasePath(workingDir);
}

std::string ResourceManager::LocateFile(const std::string &file) {
	return _basepath + file;
}

void ResourceManager::SetBasePath(const std::string &path) {
	_basepath = path;
}

} // namespace en61
