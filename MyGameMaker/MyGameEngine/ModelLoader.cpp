#include "ModelLoader.h"

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>

#include <iostream>

void ModelLoader::load(const std::string& filename, std::vector<std::shared_ptr<Model>>& models) const
{
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
	}
	else {
		models.resize(scene->mNumMeshes);

		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[i];

			models[i] = std::make_shared<Model>();
			models[i]->meshName = mesh->mName.C_Str();

			for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
				aiVector3D vertex = mesh->mVertices[j];
				vec3 aux = vec3(vertex.x, vertex.y, vertex.z);
				models[i]->modelData.vertexData.push_back(aux);

				// Coordenadas UV (si existen)
				if (mesh->mTextureCoords[0]) {  // Comprueba si hay UVs
					aiVector3D uv = mesh->mTextureCoords[0][j];
					aux.x = uv.x;  // Solo X y Y
					aux.y = 1.0f - uv.y;
				}
				models[i]->modelData.vertex_texCoords.push_back(aux);
			}

			for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
				aiFace face = mesh->mFaces[j];
				for (unsigned int k = 0; k < face.mNumIndices; k++) {
					models[i]->modelData.indexData.push_back(face.mIndices[k]);
				}
			}
		}

	}
}
