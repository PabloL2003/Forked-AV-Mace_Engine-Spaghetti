#pragma once

#include <vector>
#include <string>

#include "types.h"

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
	~Model() {}

	const std::string& GetMeshName() const { return meshName; }

	const ModelData& GetModelData() const { return modelData; }

	std::string meshName;
	ModelData modelData;
};

