#pragma once

#include <list>
#include <memory>  // Para std::shared_ptr
#include "readOnlyView.h"

template <class T>
class TreeExtension
{
private:
    T* _parent = nullptr;
    std::list<std::shared_ptr<T>> _children;  // Cambiar a std::shared_ptr<T>

public:
    auto& parent() { return *_parent; }
    const auto& parent() const { return _parent; }
    bool hasParent() const { return _parent != nullptr; }

    auto& root() const { return hasParent() ? _parent->root() : *this; }
    bool isRoot() const { return !hasParent(); }

    auto children() const { return readOnlyListView<std::shared_ptr<T>>(_children); }  // Devuelve vista solo lectura de punteros compartidos

    auto& addChild(const std::shared_ptr<T>& child) {
        child->SetParent(static_cast<T*>(this));  // Asignar al padre
        _children.push_back(child);  // Agregar hijo como shared_ptr
        return child;
    }

    template <typename ...Args>
    auto& emplaceChild(Args&&... args) {
        auto child = std::make_shared<T>(std::forward<Args>(args)...);  // Crear nuevo shared_ptr con argumentos
        child->SetParent(static_cast<T*>(this));  // Asignar al padre
        _children.push_back(child);  // Agregar a la lista
        return *child;
    }

    void removeChild(const std::shared_ptr<T>& child) {
        _children.remove(child);  // Eliminar shared_ptr de la lista
    }
};