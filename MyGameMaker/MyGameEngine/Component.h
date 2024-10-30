#pragma once

#include "GameObject.h"
#include <string>

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
	ComponentType type;
public:
	Component() : active(true), owner(nullptr) {}
	Component(bool active, GameObject* owner) : active(active), owner(owner) {}
	virtual ~Component() = default;
	GameObject* getOwner() const { return owner; }
};
