#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "BufferObject.h"

class Mesh
{
	std::vector<glm::vec3 > _vertices;
	std::vector<unsigned int> _indices;

	BufferObject _vertices_buffer;
	BufferObject _indices_buffer;
	BufferObject _texCoords_buffer;
	BufferObject _normals_buffer;
	BufferObject _colors_buffer;

public:
	const auto& vertices() const { return _vertices; }
	const auto& indices() const { return _indices; }

	void draw() const;
	void load(const glm::vec3* vertices, size_t num_vertices, const unsigned int* indices, size_t num_indices);
	void loadTextCoords(const glm::vec2* texCoords, size_t num_texCoords);
	void loadNormals(const glm::vec3* normals, size_t num_normals);
	void loadColors(const glm::u8vec3* colors, size_t num_colors);
};

