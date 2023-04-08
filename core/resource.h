#pragma once

#include <core/opengl.h>
#include <core/common.h>

#include <string>

namespace en61 {

class ResourceManager {
public:
	ResourceManager(const std::string &workingDir);

	std::string LocateFile(const std::string &file);
	void SetBasePath(const std::string &path);

	static Ref<ResourceManager> Create(const std::string &workingDir) {
		return MakeRef<ResourceManager>(workingDir);
	}

protected:
	std::string _basepath;
};

} // namespace en61
