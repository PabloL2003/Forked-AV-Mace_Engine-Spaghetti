#ifndef __SCENE_H__
#define __SCENE_H__
#pragma once

#include "GameObject.h"

#include <string>

#include "Camera.h"

class Scene : public GameObject
{
public:
	Scene(const std::string& name, const std::string& tag = "Untagged", bool active = true) : GameObject(name, tag, active) {}
	~Scene() {}

	Camera _camera;

	void Start();
	void Update(double& dT);
	void PostUpdate();
	void CleanUp();
	void OnSceneChange();
	void Draw();

	void loadGameObjectByPath(const std::string& path);
};

#endif // !__SCENE_H__