#include "Mesh.h"
#include <GL/glew.h>
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>
#include <iostream>

#include "Engine.h"

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

void Mesh::loadModel(const std::string& path)
{
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
	}
	else {
		numMeshes = scene->mNumMeshes;
		models.resize(scene->mNumMeshes);

		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[i];
			std::cout << "Malla " << i << ": " << mesh->mName.C_Str() << std::endl;

			for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
				aiVector3D vertex = mesh->mVertices[j];
				vec3 aux = vec3(vertex.x, vertex.y, vertex.z);
				models[i].modelData.vertexData.push_back(aux);

				// Coordenadas UV (si existen)
				if (mesh->mTextureCoords[0]) {  // Comprueba si hay UVs
					aiVector3D uv = mesh->mTextureCoords[0][j];
					aux.x = uv.x;  // Solo X y Y
					aux.y = 1.0f - uv.y;
				}
				models[i].modelData.vertex_texCoords.push_back(aux);
			}

			for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
				aiFace face = mesh->mFaces[j];
				for (unsigned int k = 0; k < face.mNumIndices; k++) {
					models[i].modelData.indexData.push_back(face.mIndices[k]);
				}
			}
		}

	}
}

void Mesh::loadToOpenGL()
{
	for (size_t i = 0; i < models.size(); i++)
	{
		glGenVertexArrays(1, &models[i].modelData.vA);
		glBindVertexArray(models[i].modelData.vA);

		//buffer de positions
		glGenBuffers(1, &models[i].modelData.vBPosID);
		glBindBuffer(GL_ARRAY_BUFFER, models[i].modelData.vBPosID);
		glBufferData(GL_ARRAY_BUFFER, models[i].modelData.vertexData.size() * sizeof(vec3), models[i].modelData.vertexData.data(), GL_STATIC_DRAW);

		//position layout
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(vec3), (const void*)0);

		//buffer de coordenades de textura
		glGenBuffers(1, &models[i].modelData.vBTCoordsID);
		glBindBuffer(GL_ARRAY_BUFFER, models[i].modelData.vBTCoordsID);
		glBufferData(GL_ARRAY_BUFFER, models[i].modelData.vertex_texCoords.size() * sizeof(vec3), models[i].modelData.vertex_texCoords.data(), GL_STATIC_DRAW);

		//tex coord layout
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, sizeof(vec2), (const void*)0);

		glCreateBuffers(1, &models[i].modelData.iBID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, models[i].modelData.iBID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, models[i].modelData.indexData.size() * sizeof(unsigned int), models[i].modelData.indexData.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

void Mesh::drawModel() const
{
	for (size_t i = 0; i < models.size(); i++)
	{ 
		glBindVertexArray(models[i].modelData.vA);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, models[i].modelData.iBID);

		getOwner()->GetComponent<Material>()->m_Texture->Bind();
		getOwner()->GetComponent<Material>()->m_Shader->Bind();

		getOwner()->GetComponent<Material>()->m_Shader->SetUniformMat4f("u_MVP", (glm::mat4)Engine::Instance().scene->_camera.projection() * (glm::mat4)Engine::Instance().scene->_camera.view() * (glm::mat4)getOwner()->GetComponent<Transform>()->mat());
		getOwner()->GetComponent<Material>()->m_Shader->SetUniform1i("u_Texture", 0);

		glDrawElements(GL_TRIANGLES, models[i].modelData.indexData.size(), GL_UNSIGNED_INT, nullptr);

		getOwner()->GetComponent<Material>()->m_Shader->UnBind();
		getOwner()->GetComponent<Material>()->m_Texture->Unbind();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
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
