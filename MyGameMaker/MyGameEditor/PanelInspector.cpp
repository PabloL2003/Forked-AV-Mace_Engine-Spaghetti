#include "PanelInspector.h"
#include <imgui.h>
#include "MyGUI.h"
#include "PanelHierarchy.h"
#include "MyGameEngine/Engine.h"
#include "MyGameEngine/MyWindow.h"
#include "MyGameEngine/Transform.h"

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
        DrawMeshControls();
        DrawMaterialControls();

        ImGui::End();
    }

    if (!showWindow) {
        SwitchState();
    }
    return true;
}

void PanelInspector::DrawGameObjectControls(GameObject* gameObject)
{
    ImGui::Checkbox("##active", &gameObject->isActive());
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
    if (ImGui::BeginCombo("##tag", currentTagg().c_str()))
    {
        for (const auto& option : options)
        {
            if (ImGui::Selectable(option.c_str(), currentTagg() == option))
            {
				setTag(option);
                //gameObject->tag() = option;
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
}

void PanelInspector::DrawTransformControls(GameObject* gameObject)
{
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto* transform = gameObject->GetComponent<Transform>();
        ImGui::Text("                X         Y        Z");

        // Position
        ImGui::Text("Position   ");
		ImGui::SameLine();
        ImGui::SetNextItemWidth(200.0f);
        float pos[3] = { transform->pos().x, transform->pos().y, transform->pos().z };
        if (ImGui::DragFloat3("##position", pos, 0.1f, -FLT_MAX, FLT_MAX, "%.2f"))
        {
            transform->pos() = glm::vec3(pos[0], pos[1], pos[2]);
        }

        // Rotation
        ImGui::Text("Rotation   ");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200.0f);
        glm::vec3 eulerAngles = glm::degrees(glm::eulerAngles(transform->rot()));
        if (ImGui::DragFloat3("##rotation", &eulerAngles.x, 0.1f, -360.0f, 360.0f, "%.2f"))
        {
            transform->rot() = glm::quat(glm::radians(eulerAngles));
        }

        //DrawVector3Input("Scale", scale);
		ImGui::Text("Scale      ");
        ImGui::SameLine();
		ImGui::SetNextItemWidth(200.0f);
		float scale[3] = { 1.0f, 1.0f, 1.0f };
        if (ImGui::DragFloat3("##scale", scale, 0.1f, -FLT_MAX, FLT_MAX, "%.2f"));
    }
}

void PanelInspector::DrawMeshControls()
{
    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Cube");
        ImGui::Text("Vertices: 24");
        ImGui::Text("Triangles: 12");
        ImGui::Separator();

        // Normals display options
        ImGui::Text("Display Normals");
        ImGui::Checkbox("Per-Triangle Normals", &showPerTriangleNormals);
        ImGui::Checkbox("Per-Face Normals", &showPerFaceNormals);
        ImGui::Separator();
    }
}

void PanelInspector::DrawMaterialControls()
{
    if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Size: 1024x1024");
        ImGui::Text("Texture Path: Assets/Textures/texture.png");
        ImGui::Checkbox("Show Checkers", &showCheckers);
        ImGui::Separator();
    }
}
