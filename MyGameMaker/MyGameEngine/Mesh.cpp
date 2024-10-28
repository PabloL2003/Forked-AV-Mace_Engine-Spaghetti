#include "Mesh.h"
#include <GL/glew.h>
using namespace std;

void Mesh::load(const glm::vec3* vertices, size_t num_vertices, unsigned int* indices, size_t num_indices)
{
	_vertices_buffer.loadData(vertices, num_vertices * sizeof(glm::vec3));
	_indices_buffer.loadIndices(indices, num_indices);
	_texCoords_buffer.unload();
	_normals_buffer.unload();
	_colors_buffer.unload();

	_vertices.clear();
	_indices.clear();
	_vertices.assign(vertices, vertices + num_vertices);
	_indices.assign(indices, indices + num_indices);
}

void Mesh::loadTextCoords(const glm::vec2* tex_coords, size_t num_tex_coords)
{
	_texCoords_buffer.loadData(tex_coords, num_tex_coords * sizeof(glm::vec2));
}

void Mesh::loadNormals(const glm::vec3* normals, size_t num_normals)
{
	_normals_buffer.loadData(normals, num_normals * sizeof(glm::vec3));
}

void Mesh::loadColors(const glm::u8vec3* colors, size_t num_colors)
{
	_colors_buffer.loadData(colors, num_colors * sizeof(glm::u8vec3));
}

void Mesh::draw() const
{
	if (_texCoords_buffer.id() != 0)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		_texCoords.bind();
		glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
	}

	if (_normals_buffer.id() != 0)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		_normals.bind();
		glNormalPointer(GL_FLOAT, 0, nullptr);
	}

	if (_colors_buffer.id() != 0)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		_colors.bind();
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, nullptr);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	_vertices_buffer.bind();
	glVertexPointer(3, GL_FLOAT, 0, nullptr);

	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	if (_colors.id() != 0) glDisableClientState(GL_COLOR_ARRAY);
	if (_normals.id() != 0)	glDisableClientState(GL_NORMAL_ARRAY);
	if (_texCoords.id() != 0) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}