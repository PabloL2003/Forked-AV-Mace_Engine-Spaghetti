#include "PanelInspector.h"

#include <imgui.h>

#include "MyGameEngine/Engine.h"
#include "MyGameEngine/MyWindow.h"
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
	ImGui::SetNextWindowSize(ImVec2(width, Engine::Instance().window->height() - 200));
	ImGui::SetNextWindowPos(ImVec2(Engine::Instance().window->width() - width, 0));

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
	glm::vec3 scale = { 1, 1, 1 };

	ImGui::Begin("Inspector", &showWindow, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::Checkbox("##active", &openHeader);
	ImGui::SameLine();

    // Copy the current value of `text` into the buffer initially
    strncpy_s(buffer, text.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = 0; // Ensure null-termination

    ImGui::SetNextItemWidth(100.0f);
    if (ImGui::InputText("##gameobject_name", buffer, sizeof(buffer)))
    {
        text = std::string(buffer); // Update `text` with the modified buffer
    }
	ImGui::SameLine();
	ImGui::Checkbox("Static", &openHeader);
    ImGui::Text("Current Text: %s", text.c_str()); // Display the current text value

	ImGui::Text("Tag");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    if (ImGui::BeginCombo("##tag", currentTagg.c_str())) // Start the dropdown menu
    {
        for (const auto& option : options) // Iterate over each option
        {
            bool isSelected = (currentTagg == option); // Check if this option is currently selected
            if (ImGui::Selectable(option.c_str(), isSelected))
                currentTagg = option; // Set this option as selected if clicked

            // Set the initial focus when opening the combo (scrolling effect)
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo(); // End the dropdown menu
    }
	ImGui::SameLine();
	ImGui::Text("Layer");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
    if (ImGui::BeginCombo("##layer", currentLayer.c_str())) // Start the dropdown menu
    {
        for (const auto& layer : layers)
        {
            bool isSelected = (currentLayer == layer);
		    if (ImGui::Selectable(layer.c_str(), isSelected))
				currentLayer = layer;

			if (isSelected)
				ImGui::SetItemDefaultFocus();
        }
		ImGui::EndCombo();
    }

    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        // Position Inputs
        ImGui::Text("Position");
        ImGui::SameLine();
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##pos_x", &position.x, 0.0f, 0.0f, "%.2f");
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##pos_y", &position.y, 0.0f, 0.0f, "%.2f");
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##pos_z", &position.z, 0.0f, 0.0f, "%.2f");

        // Rotation Inputs
        ImGui::Text("Rotation");
        ImGui::SameLine();
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##rot_x", &rotation.x, 0.0f, 0.0f, "%.1f");
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##rot_y", &rotation.y, 0.0f, 0.0f, "%.1f");
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##rot_z", &rotation.z, 0.0f, 0.0f, "%.1f");

        // Scale Inputs
        ImGui::Text("Scale   ");
        ImGui::SameLine();
        ImGui::Text("X");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##scale_x", &scale.x, 0.0f, 0.0f, "%.2f");
        ImGui::SameLine();
        ImGui::Text("Y");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##scale_y", &scale.y, 0.0f, 0.0f, "%.2f");
        ImGui::SameLine();
        ImGui::Text("Z");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(35.0f);
        ImGui::InputFloat("##scale_z", &scale.z, 0.0f, 0.0f, "%.2f");

        ImGui::Separator();
    }

    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Cube");
        ImGui::SameLine();
        ImGui::Text("Vertices:");
        ImGui::SameLine();
        ImGui::Text("24");
        ImGui::Text("Triangles:");
        ImGui::SameLine();
        ImGui::Text("12");
        ImGui::Separator();

        // Options to show normals
        ImGui::Text("Display Normals");
        ImGui::Checkbox("Per-Triangle Normals", &showPerTriangleNormals);
        ImGui::Checkbox("Per-Face Normals", &showPerFaceNormals);
        ImGui::Separator();
    }

	if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Size: ");
		ImGui::SameLine();
		ImGui::Text("1024x1024");
		ImGui::Text("Path: ");
		ImGui::SameLine();
		ImGui::Text("Assets/Textures/texture.png");
		ImGui::Checkbox("Show Checkers", &showCheckers);
		ImGui::Separator();
	}
    ImGui::End();


    if (!showWindow) {
        SwitchState();
    }

	return true;
}