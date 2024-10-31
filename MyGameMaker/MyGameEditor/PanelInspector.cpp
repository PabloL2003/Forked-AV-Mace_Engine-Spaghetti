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
    char buffer[256] = {};
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
            }
        }
        ImGui::EndCombo();
    }
    //MyGUI::Instance().hierarchy().selectedGameObject()->layer = this->currentLayer();
}
void PanelInspector::DrawTransformControls(GameObject* gameObject)
{
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto* transform = gameObject->GetComponent<Transform>();
        const char* axis[] = { "X", "Y", "Z" };
        ImGui::Text("       X       Y       Z");
        ImGui::Text("Position");

        for (int i = 0; i < 3; ++i)
        {
            ImGui::SetNextItemWidth(35.0f);

            float pos[3] = { static_cast<float>(transform->pos().x), static_cast<float>(transform->pos().y), static_cast<float>(transform->pos().z) };
            ImGui::SameLine();
            if (ImGui::InputFloat(std::string("##pos_" + std::string(axis[i])).c_str(), &pos[i], 0.0f, 0.0f, "%.2f"))
            {
                transform->pos() = glm::vec3(pos[0], pos[1], pos[2]);
            }
        }

        // Convert quaternion to Euler angles (in radians)
        glm::vec3 eulerAngles = glm::eulerAngles(transform->rot());

        ImGui::Text("Rotation");

        for (int i = 0; i < 3; ++i)
        {
            ImGui::SetNextItemWidth(35.0f);

            ImGui::SameLine();
            // Input field for each Euler angle
            if (ImGui::InputFloat(std::string("##" + std::string("rotation") + "_").append(1, "XYZ"[i]).c_str(), &eulerAngles[i], 0.0f, 0.0f, "%.2f"))
            {
                // Update the quaternion with the new Euler angles
                transform->rot() = glm::quat(glm::vec3(eulerAngles.x, eulerAngles.y, eulerAngles.z));
            }
        }

        //DrawVector3Input("Scale", scale);
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
