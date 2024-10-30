#pragma once

#include "GameObject.h"

class GameObject;

enum class ComponentType
{
	Transform,
	Mesh,
	Camera,
	Material,

	Light,
	Script,
	Audio,
	Physics,
	Animator,
	Particle,
	Count,

	Invalid = -1
};

class Component
{
	bool active;
	GameObject* owner;

public:
	Component() : active(true), owner(nullptr) {}
	virtual ~Component() {}

};
