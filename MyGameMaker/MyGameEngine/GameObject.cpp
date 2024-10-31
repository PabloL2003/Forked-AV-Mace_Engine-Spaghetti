#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Camera.h"
#include "Material.h"

GameObject::GameObject(const std::string& name, const std::string& tag, bool active) : _name(name), _tag(tag), _active(active), _parent(nullptr)
{
	_components.push_back(new Transform(mat4(1.0f)));
}

Component* GameObject::CreateComponent(ComponentType type, GameObject* owner)
{
	Component* component = nullptr;
	switch (type)
	{
	case ComponentType::Transform:
		component = new Transform(mat4(1.0f));
		_components.push_back(component);
		break;

	case ComponentType::Mesh:
		component = new Mesh(true, owner);
		_components.push_back(component);
		break;

	case ComponentType::Camera:
		break;

	case ComponentType::Material:
		component = new Material(true, owner);
		_components.push_back(component);
		break;

	case ComponentType::Invalid:
		break;

	default:
		break;
	}

	if (component)
	{
		_components.push_back(component);
	}
	return component;
}

bool GameObject::operator==(const GameObject& other) const
{
	// Compare name, tag, and active state
	if (_name != other._name || _tag != other._tag || _active != other._active) {
		return false;
	}

	// Compare components by checking each component type
	if (_components.size() != other._components.size()) {
		return false;
	}

	for (size_t i = 0; i < _components.size(); ++i) {
		if (*_components[i] != *other._components[i]) {
			return false;
		}
	}

	return true;
}
