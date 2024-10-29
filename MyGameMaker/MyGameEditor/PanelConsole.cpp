#include "PanelConsole.h"

#include <imgui.h>

#include "MyGameEngine/Engine.h"
#include "MyGameEngine/types.h"

PanelConsole::PanelConsole(PanelType type, std::string name) : Panel(type, name) 
{
	SwitchState();
	width = WINDOW_WIDTH;
	height = 200;
}

PanelConsole::~PanelConsole() {}

bool PanelConsole::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowPos(ImVec2(0, WINDOW_HEIGHT - height));

	ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	ImVec4 color = ImVec4(1, 1, 1, 1);
	for (size_t i = 0; i < Engine::Instance().GetLogs().size(); i++)
	{
		switch (Engine::Instance().GetLogs()[i].type)
		{
		case LogType::LOG_INFO:
			color = ImVec4(1, 1, 1, 1);
			break;

		case LogType::LOG_APPINFO:
			color = ImVec4(1, 0.5, 1, 1);
			break;
		case LogType::LOG_CHANGEENV:
			color = ImVec4(0.5, 1, 1, 1);
			break;
		};

		ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::Text(Engine::Instance().GetLogs()[i].message.c_str());
		ImGui::PopStyleColor();
	}
	
	ImGui::End();

	return true;
}