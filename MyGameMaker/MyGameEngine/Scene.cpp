#include "Scene.h"
#include "types.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <memory>

#include "Engine.h"
#include "Input.h"
#include "ModelLoader.h"
#include "Mesh.h"
#include "Material.h"

//camera movement variables
bool rightMouse = false;
int lastMouseX = -1;
int lastMouseY = -1;
int mouseX = 0;
int mouseY = 0;
float yaw = 0.0f;
float pitch = 0.0f;

//camera zoom variables
float fovModifier = 0;
float zoomValue = 0;
bool isZooming = false;

void Scene::Start()
{
	// Init camera
	_camera.transform().pos() = vec3(0, 1, 4);
	_camera.transform().rotate(glm::radians(180.0), vec3(0, 1, 0));

	ModelLoader modelLoader;
	std::vector<std::shared_ptr<Model>> models;
	modelLoader.load("../MyGameEngine/BakerHouse.fbx", models);
	for (size_t i = 0; i < models.size(); i++)
	{
		std::shared_ptr<GameObject> go = std::make_shared<GameObject>(models[i].get()->GetMeshName());
		go->CreateComponent(ComponentType::Transform, go.get());
		go->GetComponent<Transform>()->pos() = vec3(0, 0, 0);
		go->CreateComponent(ComponentType::Mesh, go.get());
		go->GetComponent<Mesh>()->setModel(models[i]);
		go->GetComponent<Mesh>()->setFilePath("../MyGameEngine/BakerHouse.fbx");
		go->CreateComponent(ComponentType::Material, go.get());
		go->GetComponent<Material>()->m_Texture = std::make_unique<Texture>("../MyGameEngine/Baker_house.png");
		go->GetComponent<Material>()->m_Shader = std::make_unique<Shader>("../MyGameEngine/Basic.shader");
		go->GetComponent<Mesh>()->loadToOpenGL();
		addChild(go);
	}
}

void Scene::Update(double& dT)
{
	//camera speed
	if (Engine::Instance().input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
		_camera.speed = 20.0f;
	}
	else {
		_camera.speed = 10.0f;
	}

	//camera movement
	if (Engine::Instance().input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		_camera.transform().translate(vec3(0, 0, _camera.speed * dT));
	}
	if (Engine::Instance().input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		_camera.transform().translate(vec3(_camera.speed * dT, 0, 0));
	}
	if (Engine::Instance().input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		_camera.transform().translate(vec3(0, 0, -_camera.speed * dT));
	}
	if (Engine::Instance().input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		_camera.transform().translate(vec3(-_camera.speed * dT, 0, 0));
	}

	//camera rotation
	if (Engine::Instance().input->GetMouseButtonDown(3) == KEY_DOWN) {
		rightMouse = true;
		Engine::Instance().input->GetMousePosition(lastMouseX, lastMouseY);
	}
	else if (Engine::Instance().input->GetMouseButtonDown(3) == KEY_UP) {
		rightMouse = false;
	}

	if (rightMouse) {
		Engine::Instance().input->GetMousePosition(mouseX, mouseY);

		float dx = (float)(mouseX - lastMouseX);
		float dy = (float)(mouseY - lastMouseY);

		// Ajusta la sensibilidad
		float sensitivity = 0.5f;
		dx *= sensitivity;
		dy *= sensitivity;

		yaw = glm::degrees(atan2(_camera.transform().fwd().z, _camera.transform().fwd().x));
		pitch = glm::degrees(atan2(_camera.transform().fwd().y, glm::sqrt(_camera.transform().fwd().x * _camera.transform().fwd().x + _camera.transform().fwd().z * _camera.transform().fwd().z)));

		yaw += dx;
		pitch -= dy;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		//actualizo el vector forward de la camera
		_camera.transform().setFwd(glm::normalize(direction));
		//uso vec3(0,1,0) porque busco el vector up en coordenadas world!!! igualmente acutalizo el vector up(local) de la camera
		_camera.transform().setRigth(glm::normalize(glm::cross(vec3(0, 1, 0), _camera.transform().fwd())));
		_camera.transform().setUp(glm::normalize(glm::cross(_camera.transform().fwd(), _camera.transform().right())));

		Engine::Instance().input->GetMousePosition(lastMouseX, lastMouseY);
	}

	//camera zoom
	Engine::Instance().input->GetMouseWheelMotion(isZooming);
	if (isZooming) {
		Engine::Instance().input->GetMouseWheel((int&)zoomValue);
		if (zoomValue > 0) {
			if (fovModifier > -30.0) {
				fovModifier -= 1.0;
			}
		}
		else {
			if (fovModifier < 0) {
				fovModifier += 1.0;
			}
		}
		_camera.fov = glm::radians(60 + fovModifier);
	}
}

void Scene::PostUpdate()
{
	
}

void Scene::CleanUp()
{
	/*for (auto& child : children())
	{
		child.get()->CleanUp()
	}*/
}

void Scene::OnSceneChange()
{
}

void Scene::Draw()
{
	for (auto& child : children())
	{
		child->GetComponent<Mesh>()->drawModel();
	}
}

void Scene::loadGameObjectByPath(const std::string& path)
{
	ModelLoader modelLoader;
	std::vector<std::shared_ptr<Model>> models;
	modelLoader.load(path, models);
	for (size_t i = 0; i < models.size(); i++)
	{
		std::shared_ptr<GameObject> go = std::make_shared<GameObject>(models[i].get()->GetMeshName());
		go->CreateComponent(ComponentType::Transform, go.get());
		go->GetComponent<Transform>()->pos() = vec3(5, 0, 0);
		go->CreateComponent(ComponentType::Mesh, go.get());
		go->GetComponent<Mesh>()->setModel(models[i]);
		go->GetComponent<Mesh>()->setFilePath(path);
		go->GetComponent<Mesh>()->loadToOpenGL();
		go->CreateComponent(ComponentType::Material, go.get());
		go->GetComponent<Material>()->m_Texture = std::make_unique<Texture>("../MyGameEngine/Baker_house.png");
		go->GetComponent<Material>()->m_Shader = std::make_unique<Shader>("../MyGameEngine/Basic.shader");
		addChild(go);
	}
}
