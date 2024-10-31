#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#pragma once

#include <string>
#include <vector>
#include "TreeExtension.h"
#include "Component.h"

class Component;
enum class ComponentType;

class GameObject : public TreeExtension<GameObject>
{
	std::string _name;
	std::string _tag;
	bool _active;
	std::vector<Component*> _components;
	GameObject* _parent;
	std::list<GameObject*> _children;

public:
	GameObject(const std::string& name, const std::string& tag = "Untagged", bool active = true);
	~GameObject() {}

	auto& name() { return _name; }
	auto& tag() { return _tag; }
	auto& parent() { return _parent; }
	
	auto& isActive() { return _active; }
	virtual bool SetActive(bool active) { return this->_active = active; }
	virtual bool SwitchState() { return _active = !_active; }

	Component* CreateComponent(ComponentType type, GameObject* owner);

	void setParent(GameObject* parent) { _parent = parent; }

	template <typename T>
	T* GetComponent() const {
		for (Component* component : _components) {
			if (T* specificComponent = dynamic_cast<T*>(component)) {
				return specificComponent; // Devuelve el componente del tipo específico
			}
		}
		return nullptr; // Si no se encuentra el componente del tipo específico
	}

	bool operator==(const GameObject& other) const;

protected:
	virtual void Start() {}
	virtual void Update() {}
	virtual void CleanUp() {}
	virtual void OnSceneChange() {}
};

#endif // __GAMEOBJECT_H__