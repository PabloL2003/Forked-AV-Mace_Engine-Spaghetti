#include "Mesh.h"

#include "Engine.h"
#include "Renderer.h"

#include "Scene.h"
#include "Material.h"

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

void Mesh::loadToOpenGL()
{

	GLCall(glGenVertexArrays(1, &model.get()->GetModelData().vA));
	GLCall(glBindVertexArray(model.get()->GetModelData().vA));

	//buffer de positions
	GLCall(glGenBuffers(1, &model.get()->GetModelData().vBPosID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, model.get()->GetModelData().vBPosID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, model.get()->GetModelData().vertexData.size() * sizeof(vec3), model.get()->GetModelData().vertexData.data(), GL_STATIC_DRAW));

	//position layout
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(vec3), (const void*)0));

	//buffer de coordenades de textura
	if (model.get()->GetModelData().vertex_texCoords.size() > 0)
	{
		GLCall(glGenBuffers(1, &model.get()->GetModelData().vBTCoordsID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, model.get()->GetModelData().vBTCoordsID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, model.get()->GetModelData().vertex_texCoords.size() * sizeof(vec2), model.get()->GetModelData().vertex_texCoords.data(), GL_STATIC_DRAW));

		//tex coord layout
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, sizeof(vec2), (const void*)0));
	}

	//buffer de normals
	if (model.get()->GetModelData().vertex_normals.size() > 0)
	{
		GLCall(glGenBuffers(1, &model.get()->GetModelData().vBNormalsID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, model.get()->GetModelData().vBNormalsID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, model.get()->GetModelData().vertex_normals.size() * sizeof(vec3), model.get()->GetModelData().vertex_normals.data(), GL_STATIC_DRAW));

		//normal layout
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 3, GL_DOUBLE, GL_FALSE, sizeof(vec3), (const void*)0));
	}

	//buffer de index
	GLCall(glCreateBuffers(1, &model.get()->GetModelData().iBID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.get()->GetModelData().iBID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.get()->GetModelData().indexData.size() * sizeof(unsigned int), model.get()->GetModelData().indexData.data(), GL_STATIC_DRAW));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	
}

void Mesh::drawModel() const
{
	
	GLCall(glBindVertexArray(model.get()->GetModelData().vA));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.get()->GetModelData().iBID));

	if (getOwner()->GetComponent<Material>()->m_Texture) {
		getOwner()->GetComponent<Material>()->m_Texture->Bind();
	}

	getOwner()->GetComponent<Material>()->m_Shader->Bind();

	getOwner()->GetComponent<Material>()->m_Shader->SetUniformMat4f("u_MVP", (glm::mat4)Engine::Instance().scene->_camera.projection() * (glm::mat4)Engine::Instance().scene->_camera.view() * (glm::mat4)getOwner()->GetComponent<Transform>()->mat());
	
	if (getOwner()->GetComponent<Material>()->m_Texture) {
		getOwner()->GetComponent<Material>()->m_Shader->SetUniform1i("u_Texture", 0);
	}

	glDrawElements(GL_TRIANGLES, model.get()->GetModelData().indexData.size(), GL_UNSIGNED_INT, nullptr);

	getOwner()->GetComponent<Material>()->m_Shader->UnBind();

	if (getOwner()->GetComponent<Material>()->m_Texture) {
		getOwner()->GetComponent<Material>()->m_Texture->Unbind();
	}

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	
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
