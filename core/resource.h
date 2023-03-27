#pragma once

#include <core/opengl.h>

#include <string>
#include <memory>

namespace en61 {

class ResourceManager {
public:
	ResourceManager(const std::string &working_dir);

	std::string locate_file(const std::string &file);
	void set_base_path(const std::string &path);

	static std::shared_ptr<ResourceManager> create(const std::string &working_dir) {
		return std::make_shared<ResourceManager>(working_dir);
	}

protected:
	std::string _basepath;
};

} // namespace en61
