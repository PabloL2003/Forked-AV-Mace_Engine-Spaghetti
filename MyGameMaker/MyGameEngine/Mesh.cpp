#include "Mesh.h"
#include <GL/glew.h>

void Mesh::load(const glm::vec3* vertices, size_t num_vertices, const unsigned int* indices, size_t num_indices)
{
	_vertices.assign(vertices, vertices + num_vertices);
	_indices.assign(indices, indices + num_indices);
	_vertices_buffer.loadElements(_vertices.size(), _vertices.data());
	_indices_buffer.loadIndices(_indices.size(), _indices.data());
	_texCoords_buffer.unbind();
	_normals_buffer.unbind();
	_colors_buffer.unbind();

	_boundingBox.min = _vertices.front();
	_boundingBox.max = _vertices.front();

	for (const auto& v : _vertices) {
		_boundingBox.min = glm::min(_boundingBox.min, glm::dvec3(v));
		_boundingBox.max = glm::max(_boundingBox.max, glm::dvec3(v));
	}
}

void Mesh::loadTexCoords(const glm::vec2* texCoords) {
	_texCoords_buffer.loadElements(_vertices.size(), texCoords);
}

void Mesh::loadNormals(const glm::vec3* normals) {
	_normals_buffer.loadElements(_vertices.size(), normals);
}

void Mesh::loadColors(const glm::u8vec3* colors) {
	_colors_buffer.loadElements(_vertices.size(), colors);
}

void Mesh::draw() const {

	if (_texCoords_buffer.id()) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		_texCoords_buffer.bind();
		glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
	}

	if (_normals_buffer.id()) {
		glEnableClientState(GL_NORMAL_ARRAY);
		_normals_buffer.bind();
		glNormalPointer(GL_FLOAT, 0, nullptr);
	}

	if (_colors_buffer.id()) {
		glEnableClientState(GL_COLOR_ARRAY);
		_colors_buffer.bind();
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, nullptr);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	_vertices_buffer.bind();
	glVertexPointer(3, GL_FLOAT, 0, nullptr);

	_indices_buffer.bind();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, nullptr);

	glDisableClientState(GL_VERTEX_ARRAY);
	if (_colors_buffer.id()) glDisableClientState(GL_COLOR_ARRAY);
	if (_normals_buffer.id()) glDisableClientState(GL_NORMAL_ARRAY);
	if (_texCoords_buffer.id()) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
