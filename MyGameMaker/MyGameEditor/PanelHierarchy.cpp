#include "PanelHierarchy.h"

#include <imgui.h>
#include <memory>

#include "MyGameEngine/Engine.h"
#include "MyGameEngine/MyWindow.h"
#include "MyGameEngine/Scene.h"
#include "MyGameEngine/types.h"
#include "PanelInspector.h"

PanelHierarchy::PanelHierarchy(PanelType type, std::string name) : Panel(type, name, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT - 219)
{
	SwitchState();
}

PanelHierarchy::~PanelHierarchy() {}

bool PanelHierarchy::Draw()
{
   ImGui::SetNextWindowSize(ImVec2(width, Engine::Instance().window->height() - 219));
   ImGui::SetNextWindowPos(ImVec2(0, 19));

   ImGui::Begin("Hierarchy", &showWindow, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
   for (const std::shared_ptr<GameObject>& gameObjectPtr : Engine::Instance().scene->children())
   {
	   DrawGameObjectTree(gameObjectPtr.get());
   }
   ImGui::End();

   if (!showWindow) {
       SwitchState();
   }

   Engine::Instance().scene->selectedGameObject = selectedGameObject();

   return true;
}

void PanelHierarchy::DrawGameObjectTree(GameObject* gameObject)
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
	if (selectedGameObject() == gameObject) flags |= ImGuiTreeNodeFlags_Selected;

	bool isNodeOpen = ImGui::TreeNodeEx(gameObject->name().c_str(), flags);
	if (ImGui::IsItemClicked()) SetSelectedGameObject(gameObject);

	if (isNodeOpen)
	{
		for (const std::shared_ptr<GameObject>& childObjectPtr : gameObject->children())
		{
			DrawGameObjectTree(childObjectPtr.get());
		}
		ImGui::TreePop();
	}
}
