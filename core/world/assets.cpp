#include <core/world/assets.h>

#include <iostream>

namespace en61 {

void AssetManager::WrongAssetType(const std::type_info &info) {
	std::cerr << "no loader for type " << info.name() << " found!" << std::endl;
}

template <>
Ref<Model> AssetManager::Load(const std::string &path) {
	Ref<Model> model = MakeRef<Model>();
	model->Load(_dir + path);
	return model;
}

template <>
Ref<Texture> AssetManager::Load(const std::string &path) {
	Ref<Texture> texture = MakeRef<Texture>();
	texture->Load(_dir + path);
	return texture;
}

template <>
Ref<Shader> AssetManager::Load(const std::string &vertexPath, const std::string &fragmentPath) {
	Ref<Shader> shader = MakeRef<Shader>();
	shader->Load(_dir + vertexPath, _dir + fragmentPath);
	return shader;
}

AssetManager::AssetManager(const std::string &path) {
	SetDir(path);
}

} // namespace en61
