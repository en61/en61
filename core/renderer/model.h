#pragma once

#include <core/renderer/mesh.h>
#include <core/renderer/interfaces.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace en61 {

class Model: public ModelInterface {
public:
	Model(const std::string &path);
	Model() = default;

	void Load(const std::string &path);
	void Draw() override;

protected:
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string name);

protected:
	std::string _dir;
	std::vector<Mesh> _meshes;
};

} // namespace en61
