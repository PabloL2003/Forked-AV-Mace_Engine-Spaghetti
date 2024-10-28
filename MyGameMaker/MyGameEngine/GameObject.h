#pragma once
#include <string>
#include "TreeExtension.h"

class GameObject : public TreeExt<GameObject>
{
	std::string _name;

public:
	std::string name() const { return _name; }
	void setName(const string& name) { _name = name; }


	void paint();
};

