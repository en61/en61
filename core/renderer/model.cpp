#include <core/renderer/model.h>

#include <iostream>

#include <assimp/Importer.hpp>

namespace en61 {

Model::Model(const std::string &path) {
	Load(path);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
	std::vector<Texture> textures;
	for(size_t i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.Load(_dir + "/" + str.C_Str());
		textures.push_back(texture);
	}
	return textures;
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;
	std::vector<Texture> textures;

	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		auto &vert= mesh->mVertices[i];
		vertex.position = glm::vec3(vert.x, vert.y, vert.z);

		auto &normal = mesh->mNormals[i];
		vertex.normal = glm::vec3(normal.x, normal.y, normal.z);
		
		if (mesh->mTextureCoords[0]) {
			auto &texture = mesh->mTextureCoords[0][i];
			vertex.texCoords = glm::vec2(texture.x, texture.y);
		}
		else {
			vertex.texCoords = glm::vec2(0.f, 0.f);
		}

		vertices.push_back(vertex);
	}

	for(size_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for(size_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
	for(size_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		_meshes.push_back(ProcessMesh(mesh, scene));
	}
	for(size_t i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

void Model::Draw() {
	for (size_t i = 0; i < _meshes.size(); i++) {
		_meshes[i].Draw();
	}
}

void Model::Load(const std::string &path) {
	Assimp::Importer importer;
	unsigned flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;
	const aiScene *scene = importer.ReadFile(path, flags);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Assimp Error:" << importer.GetErrorString() << std::endl;
		return;
	}

	_dir = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

} // namespace en61
