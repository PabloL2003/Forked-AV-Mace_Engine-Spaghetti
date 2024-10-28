#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "BufferObject.h"
#include "BoundingBox.h"

class Mesh
{
	std::vector<glm::vec3 > _vertices;
	std::vector<unsigned int> _indices;

	BufferObject _vertices_buffer;
	BufferObject _indices_buffer;
	BufferObject _texCoords_buffer;
	BufferObject _normals_buffer;
	BufferObject _colors_buffer;

	BoundingBox _boundingBox;

public:
	const auto& vertices() const { return _vertices; }
	const auto& indices() const { return _indices; }
	const auto& boundingBox() const { return _boundingBox; }

	void draw() const;
	void load(const glm::vec3* verts, size_t num_verts, const unsigned int* indexs, size_t num_indexs);
	void loadTexCoords(const glm::vec2* texCoords);
	void loadNormals(const glm::vec3* normals);
	void loadColors(const glm::u8vec3* colors);
};

