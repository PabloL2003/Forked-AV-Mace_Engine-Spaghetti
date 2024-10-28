#pragma once
#include <list>

template <class T>
class TreeExt
{
	T* _parent = nullptr;
	list<T> _children;

public:
	auto& parent() { return _parent; }
	const auto& parent() const { return _parent; }
	bool hasParent() const { return _parent != nullptr; }

	const auto& children() const { return _children; }
	auto& addChild(const T& child)
	{
		_children.push_back(child);
		_children.back()._parent = static_cast<T*>(this);
		return _children.back();
	}
};