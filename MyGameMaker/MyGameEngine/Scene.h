#ifndef __SCENE_H__
#define __SCENE_H__
#pragma once

#include "GameObject.h"

#include <string>

#include "Camera.h"

class Scene : public GameObject
{
	GameObject* _root = nullptr;

public:
	Scene(const std::string& name, const std::string& tag = "Untagged", bool active = true) : GameObject(name, tag, active) {}
	~Scene() {}

	Camera _camera;

	void Start();
	void Update(double& dT);
	void PostUpdate();
	void CleanUp();
	void OnSceneChange();
	void Draw(GameObject* root);

	void loadGameObjectByPath(const std::string& path);
	void loadTextureByPath(const std::string& path);

	GameObject* selectedGameObject = nullptr;

	void CreateGameObject();
	void CreateCube();
	void CreatePlane();
	void CreateSphere();
	void CreateCylinder();
	void CreateCone();
	void CreateTorus();

};

#endif // !__SCENE_H__