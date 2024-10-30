#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"

GameObject::GameObject(const std::string& name, const std::string& tag, bool active) : _name(name), _tag(tag), _active(active), _parent(nullptr)
{
	_components.push_back(new Transform());
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