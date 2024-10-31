#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>

#include "Component.h"
#include "BufferObject.h"
#include "BoundingBox.h"

#include "Model.h"

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
	std::shared_ptr<Model> model;

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
	void loadToOpenGL();
	void drawModel() const;
	void setModel(std::shared_ptr<Model> model) { this->model = model; }
};

