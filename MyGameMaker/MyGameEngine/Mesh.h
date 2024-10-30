#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>

#include "Component.h"
#include "BufferObject.h"
#include "BoundingBox.h"

struct ModelData
{
	unsigned int vBPosID, vBTCoordsID, iBID, vA;
	std::vector<vec3> vertexData;
	std::vector<unsigned int> indexData;
	std::vector<vec2> vertex_texCoords;
};

class Model
{
public:
	Model() {}
	Model(const std::string& path);
	~Model() {}

	const std::string& GetMeshName() const { return meshName; }

	const ModelData& GetModelData() const { return modelData; }

	std::string meshName;
	ModelData modelData;
};

class Mesh : public Component
{
	std::vector<glm::vec3 > _vertices;
	std::vector<unsigned int> _indices;

	BufferObject _vertices_buffer;
	BufferObject _indices_buffer;
	BufferObject _texCoords_buffer;
	BufferObject _normals_buffer;
	BufferObject _colors_buffer;

	BoundingBox _boundingBox;

	//la nostra manera de carregar un model
	std::vector<Model> models;

public:
	Mesh() {}
	Mesh(bool active, GameObject* owner) : Component(active, owner) {}
	~Mesh() {}

	const auto& vertices() const { return _vertices; }
	const auto& indices() const { return _indices; }
	const auto& boundingBox() const { return _boundingBox; }

	void draw() const;
	void load(const glm::vec3* verts, size_t num_verts, const unsigned int* indexs, size_t num_indexs);
	void loadTexCoords(const glm::vec2* texCoords);
	void loadNormals(const glm::vec3* normals);
	void loadColors(const glm::u8vec3* colors);

	//la nostra manera de carregar un model
	void loadModel(const std::string& path);
	void loadToOpenGL();
	void drawModel() const;

};

