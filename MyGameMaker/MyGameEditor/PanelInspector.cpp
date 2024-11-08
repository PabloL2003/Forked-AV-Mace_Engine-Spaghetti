#include "PanelInspector.h"
#include <imgui.h>
#include "MyGUI.h"
#include "PanelHierarchy.h"
#include "MyGameEngine/Engine.h"
#include "MyGameEngine/MyWindow.h"
#include "MyGameEngine/Transform.h"
#include "MyGameEngine/Mesh.h"
#include "MyGameEngine/Material.h"

PanelInspector::PanelInspector(PanelType type, std::string name) : Panel(type, name, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT - 200)
{
	SwitchState();
}

PanelInspector::~PanelInspector() {}

bool PanelInspector::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(width, Engine::Instance().window->height() - 200));
	ImGui::SetNextWindowPos(ImVec2(Engine::Instance().window->width() - width, 0));

    if (auto* selectedGameObject = MyGUI::Instance().hierarchy().selectedGameObject())
    {
        ImGui::Begin("Inspector", &showWindow, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        DrawGameObjectControls(selectedGameObject);
        DrawTransformControls(selectedGameObject);
        DrawMeshControls(selectedGameObject);
        DrawMaterialControls(selectedGameObject);

        ImGui::End();
    }

    if (!showWindow) {
        SwitchState();
    }
    return true;
}

void PanelInspector::DrawGameObjectControls(GameObject* gameObject)
{
    ImGui::Checkbox("Active", &gameObject->isActive());
    ImGui::SameLine();

    // Name input
    ImGui::SetNextItemWidth(100.0f);
    char buffer[128] = {};
    strncpy_s(buffer, gameObject->name().c_str(), sizeof(buffer));
    if (ImGui::InputText("##gameobject_name", buffer, sizeof(buffer)))
    {
        gameObject->name() = buffer;
    }
    ImGui::SameLine();
    ImGui::Checkbox("Static", &gameObject->isActive());

    // Tag selection
    ImGui::Text("Tag");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100.0f);
    if (ImGui::BeginCombo("##tag", gameObject->tag().c_str()))
    {
        for (const auto& option : options)
        {
            if (ImGui::Selectable(option.c_str(), gameObject->tag() == option))
            {
                gameObject->tag() = option;
            }
        }
        ImGui::EndCombo();
    }
	ImGui::SameLine();

    // Layer selection
    ImGui::Text("Layer");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100.0f);
    if (ImGui::BeginCombo("##layer", currentLayer().c_str()))
    {
        for (const auto& layer : layers)
        {
            if (ImGui::Selectable(layer.c_str(), currentLayer() == layer))
            {
                setLayer(layer);
				//gameObject->layer() = layer;
            }
        }
        ImGui::EndCombo();
    }
	ImGui::Separator();
}

void PanelInspector::DrawTransformControls(GameObject* gameObject)
{
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto* transform = gameObject->GetComponent<Transform>();

		ImGui::Checkbox("Active", &transform->isActive());
		ImGui::SameLine();
        ImGui::Text("      X         Y         Z");

        // Position
        ImGui::Text("Position   ");
		ImGui::SameLine();
        ImGui::SetNextItemWidth(210.0f);
        float pos[3] = { transform->pos().x, transform->pos().y, transform->pos().z };
        if (ImGui::DragFloat3("##position", pos, 0.1f, -FLT_MAX, FLT_MAX, "%.2f") | ImGuiInputTextFlags_CharsDecimal)
        {
            if (ImGui::IsItemActive()) {
                Engine::Instance().input->ActivateTextInput();
                transform->pos() = glm::vec3(pos[0], pos[1], pos[2]);
            }
            else if (ImGui::IsItemDeactivatedAfterEdit()) {
                Engine::Instance().input->ActivateTextInput(false);
            }
        }

        // Rotation
        ImGui::Text("Rotation   ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(210.0f);
        glm::vec3 eulerAngles = glm::degrees(glm::eulerAngles(transform->rot()));
        if (ImGui::DragFloat3("##rotation", &eulerAngles.x, 0.1f, -360.0f, 360.0f, "%.2f"))
        {
            if (ImGui::IsItemActive()) {
                Engine::Instance().input->ActivateTextInput();
                transform->rotate(glm::radians(eulerAngles));
            }
            else if (ImGui::IsItemDeactivatedAfterEdit()) {
                Engine::Instance().input->ActivateTextInput(false);
            }
        }
        
		ImGui::Text("Scale      ");
        ImGui::SameLine();
		ImGui::SetNextItemWidth(210.0f);
		float scale[3] = { transform->scale().x, transform->scale().y, transform->scale().z };
        if (ImGui::DragFloat3("##scale", scale, 0.1f, -FLT_MAX, FLT_MAX, "%.2f"))
        {
            transform->scale() = glm::vec3(scale[0], scale[1], scale[2]);
        }
		ImGui::Separator();
    }
}

void PanelInspector::DrawMeshControls(GameObject* gameObject)
{
    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {
		auto* mesh = gameObject->GetComponent<Mesh>();

        ImGui::Checkbox("Active", &gameObject->GetComponent<Mesh>()->isActive());
		ImGui::SameLine();
		ImGui::Text("   File:");
		ImGui::SameLine();
        ImGui::SetNextItemWidth(150.0f);
        char buffer[128] = {};
        strncpy_s(buffer, mesh->getFilePath().c_str(), sizeof(buffer));
        ImGui::InputText("##mesh_path", buffer, sizeof(buffer));

        ImGui::Text("Display Normals:");
        showPerTriangleNormals = mesh->getDebugNormals();
        ImGui::Checkbox("Vertex Normals", &showPerTriangleNormals);
        mesh->setDebugNormals(showPerTriangleNormals);

        showPerFaceNormals = gameObject->GetComponent<Mesh>()->getDebugFaceNormals();
        ImGui::Checkbox("Face Normals", &showPerFaceNormals);
        mesh->setDebugFaceNormals(showPerFaceNormals);
        ImGui::Separator();
    }
}

void PanelInspector::DrawMaterialControls(GameObject* gameObject)
{
    if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("Active", &gameObject->GetComponent<Material>()->isActive());
        ImGui::Text(" ");
        ImGui::Text("Main Maps");
        ImGui::Text("Texture Path: Assets/Textures/texture.png");
        ImGui::Checkbox("Albedo", &showCheckers);
        ImGui::Checkbox("Show Checkers", &showCheckers);
        ImGui::Separator();
    }
}
