#include "PanelInspector.h"

#include <imgui.h>

#include "MyGameEngine/Engine.h"
#include "MyGameEngine/types.h"

PanelInspector::PanelInspector(PanelType type, std::string name) : Panel(type, name)
{
	SwitchState();
	width = 250;
	height = WINDOW_HEIGHT - 200;
}

PanelInspector::~PanelInspector() {}

bool PanelInspector::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH - width, 0));

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
	glm::vec3 scale = { 1, 1, 1 };

	ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    if (ImGui::CollapsingHeader("Transform")) 
    {
        // Position Inputs
        ImGui::Text("Position");
        ImGui::SameLine();
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##pos_x", &position.x, 0.0f, 0.0f, "%.2f");
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##pos_y", &position.y, 0.0f, 0.0f, "%.2f");
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##pos_z", &position.z, 0.0f, 0.0f, "%.2f");

        // Rotation Inputs
        ImGui::Text("Rotation");
        ImGui::SameLine();
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##rot_x", &rotation.x, 0.0f, 0.0f, "%.1f");
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##rot_y", &rotation.y, 0.0f, 0.0f, "%.1f");
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##rot_z", &rotation.z, 0.0f, 0.0f, "%.1f");

        // Scale Inputs
        ImGui::Text("Scale   ");
        ImGui::SameLine();
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##scale_x", &scale.x, 0.0f, 0.0f, "%.2f");
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##scale_y", &scale.y, 0.0f, 0.0f, "%.2f");
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40.0f);
        ImGui::InputFloat("##scale_z", &scale.z, 0.0f, 0.0f, "%.2f");

        ImGui::Separator();
    }

	ImGui::End();
	
	return true;
}