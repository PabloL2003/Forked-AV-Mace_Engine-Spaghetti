#ifndef __SCENE_H__
#define __SCENE_H__
#pragma once

#include "GameObject.h"

class Camera;

class Scene : public GameObject
{
	Camera* _camera = nullptr;

public:
	Scene(const std::string& name, const std::string& tag, bool active = true) : GameObject(name, tag, active) {}
	~Scene() {}

	void Start();
	void Update();
	void CleanUp();
	void OnSceneChange();
};

#endif // !__SCENE_H__