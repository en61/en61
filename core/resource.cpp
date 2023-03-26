#include <core/resource.h>


#include <iostream>
#include <core/application.h>

namespace en61 {

ResourceManager::ResourceManager(const std::string &working_dir) {
	set_base_path(working_dir);
}

std::string ResourceManager::locate_file(const std::string &file) {
	return _basepath + file;
}

void ResourceManager::set_base_path(const std::string &path) {
	_basepath = path;
}

std::string locate_file(const std::string &file) {
	return Application::get()->resource_manager()->locate_file(file);
}


} // namespace en61
