#include "Scene.h"
#include "types.h"
#include "Camera.h"

void Scene::Start()
{
	// Init camera
	Camera camera;
	camera.transform().pos() = vec3(0, 1, 4);
	camera.transform().rotate(glm::radians(180.0), vec3(0, 1, 0));
	float cameraSpeed = 10.0f;

	GameObject bakerhouse = GameObject("Baker House");
	bakerhouse.CreateComponent(ComponentType::Transform, &bakerhouse);
	bakerhouse.CreateComponent(ComponentType::Mesh, &bakerhouse);
}

void Scene::Update()
{

}

void Scene::CleanUp()
{

}

void Scene::OnSceneChange()
{
}
