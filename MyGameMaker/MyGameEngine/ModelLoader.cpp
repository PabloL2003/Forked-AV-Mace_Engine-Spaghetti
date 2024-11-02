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

		std::vector<std::shared_ptr<ModelData>> modelsData;
		modelsData.resize(scene->mNumMeshes);

		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[i];
			modelsData[i] = std::make_shared<ModelData>();
			models[i] = std::make_shared<Model>();
			models[i]->SetMeshName(mesh->mName.C_Str());

			for (unsigned int j = 0; j < mesh->mNumVertices; j++) {

				// Coordenadas de los vértices
				aiVector3D vertex = mesh->mVertices[j];
				vec3 aux = vec3(vertex.x, vertex.y, vertex.z);
				modelsData[i]->vertexData.push_back(aux);

				// Coordenadas UV (si existen)
				if (mesh->mTextureCoords[0]) {  // Comprueba si hay UVs
					aiVector3D uv = mesh->mTextureCoords[0][j];
					aux.x = uv.x;  // Solo X y Y
					aux.y = 1.0f - uv.y;
				}
				modelsData[i]->vertex_texCoords.push_back(aux);

				if (mesh->HasNormals()) {  // Verifica si hay normales
					aiVector3D normal = mesh->mNormals[j];
					vec3 auxNormal(normal.x, normal.y, normal.z);
					modelsData[i]->vertex_normals.push_back(auxNormal);
				}

				if (mesh->HasVertexColors(0)) {  // Verifica si hay colores
					aiColor4D color = mesh->mColors[0][j];
					vec3 auxColor(color.r, color.g, color.b);
					modelsData[i]->vertex_colors.push_back(auxColor);
				}

			}

			for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
				aiFace face = mesh->mFaces[j];
				for (unsigned int k = 0; k < face.mNumIndices; k++) {
					modelsData[i]->indexData.push_back(face.mIndices[k]);
				}
			}

			models[i]->SetModelData(*modelsData[i]);

		}

	}
}

void ModelLoader::load(Shapes shape, std::shared_ptr<Model>& model)
{

	std::shared_ptr<ModelData> modelData;

	switch (shape)
	{
	case Shapes::CUBE:

		model = std::make_shared<Model>();
		model->SetMeshName("Cube");

		
		modelData = std::make_shared<ModelData>();

		modelData.get()->vertexData = {
			vec3(-1,-1,-1),
			vec3(1,-1,-1), 
			vec3(1,1,-1),  
			vec3(-1,1,-1), 
			vec3(-1,-1,1), 
			vec3(1,-1,1),  
			vec3(1,1,1),   
			vec3(-1,1,1)  
		};

		modelData.get()->vertex_colors = {
			vec3(0.8,0,0),
			vec3(0.0,1,0),
			vec3(0.0,0,1),
			vec3(1,1,1),
			vec3(1,0,1),
			vec3(0.5,1,0),
			vec3(0.8,1,0.5),
			vec3(0.8,0.3,0.6)
		};

		modelData.get()->indexData = {
			0, 1, 2, 0, 2, 3,
			1, 5, 6, 1, 6, 2,
			5, 4, 7, 5, 7, 6,
			4, 0, 3, 4, 3, 7,
			3, 2, 6, 3, 6, 7,
			4, 5, 1, 4, 1, 0
		};

		model->SetModelData(*modelData);

		break;
	
	case Shapes::PLANE:

		model = std::make_shared<Model>();
		model->SetMeshName("Pane");

		modelData = std::make_shared<ModelData>();

		modelData.get()->vertexData = {
			vec3(-1,0,-1),
			vec3(1,0,-1),
			vec3(1,0,1),
			vec3(-1,0,1)
		};

		modelData.get()->vertex_colors = {
			vec3(0.8,0,0),
			vec3(0.0,1,0),
			vec3(0.0,0,1),
			vec3(1,1,1)
		};

		modelData.get()->indexData = {
			0, 1, 2, 0, 2, 3
		};

		model->SetModelData(*modelData);

		break;
	
	default:

		break;

	}
}
