#pragma once

#include "GameObject.h"

class Component
{
	bool active;
	GameObject* gameObject_owner;

public:
	Component() : active(true), gameObject_owner(nullptr) {}
	virtual ~Component() {}

};
