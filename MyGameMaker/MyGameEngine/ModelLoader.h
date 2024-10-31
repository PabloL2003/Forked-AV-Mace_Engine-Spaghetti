#pragma once

#include <memory>

#include "Model.h"

class ModelLoader
{
public:
	ModelLoader() = default;
	~ModelLoader() = default;

	void load(const std::string& filename, std::vector<std::shared_ptr<Model>>& models) const;
};

