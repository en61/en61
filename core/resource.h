#pragma once

#include <core/opengl.h>

#include <string>
#include <memory>

namespace en61 {

class ResourceManager {
public:
	ResourceManager(const std::string &workingDir);

	std::string LocateFile(const std::string &file);
	void SetBasePath(const std::string &path);

	static std::shared_ptr<ResourceManager> Create(const std::string &workingDir) {
		return std::make_shared<ResourceManager>(workingDir);
	}

protected:
	std::string _basepath;
};

} // namespace en61
