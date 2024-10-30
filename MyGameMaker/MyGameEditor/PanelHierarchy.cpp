#include "PanelHierarchy.h"

#include <imgui.h>

#include "MyGameEngine/Engine.h"
#include "MyGameEngine/types.h"

PanelHierarchy::PanelHierarchy(PanelType type, std::string name) : Panel(type, name)
{
	SwitchState();
	width = 150;
	height = WINDOW_HEIGHT - 219;
}

PanelHierarchy::~PanelHierarchy() {}

bool PanelHierarchy::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowPos(ImVec2(0, 19));

	ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::End();

	return true;
}