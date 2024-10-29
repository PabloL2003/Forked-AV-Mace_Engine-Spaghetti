#include "PanelConsole.h"

#include <imgui.h>

#include "MyGameEngine/Engine.h"

PanelConsole::PanelConsole(PanelType type, std::string name) : Panel(type, name) {}

PanelConsole::~PanelConsole() {}

bool PanelConsole::Draw()
{
	ImGuiWindowFlags consoleFlags = 0;
	consoleFlags |= ImGuiWindowFlags_NoFocusOnAppearing;

	if (ImGui::Begin("Console", &enabled, consoleFlags))
	{
		if (ImGui::Button("Clear")) {
			Engine::Instance().CleanLogs();
		}

		ImGui::SameLine();

		static bool clearOnPlay = false;
		ImGui::Checkbox("Clear on Play", &clearOnPlay);

		ImGui::Separator();

		ImGuiWindowFlags scrollFlags = 0;
		scrollFlags |= ImGuiWindowFlags_HorizontalScrollbar;
		scrollFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;

		if (ImGui::BeginChild("Scrollbar", ImVec2(0, 0), false, scrollFlags))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 15));
			std::string logType;
			ImVec4 color = ImVec4(1, 1, 1, 1);

			for (const auto& log : Engine::Instance().GetLogs())
			{
				switch (log.type)
				{
				case LogType::LOG_INFO:
					logType = "";
					color = ImVec4(1, 1, 1, 1);
					break;

				case LogType::LOG_ASSIMP:
					logType = "[ASSIMP] ";
					color = ImVec4(1, 1, 1, 1);
					break;
				}

				if (log.message[0] == '-')
					logType.insert(0, "\t");

				ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::Text(logType.c_str());
				ImGui::PopStyleColor();

				ImGui::SameLine();
				ImGui::Text(log.message.c_str());
			}

			ImGui::PopStyleVar();

			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
				ImGui::SetScrollHereY(1.0f);

		}
		ImGui::EndChild();
	}
	ImGui::End();

	return true;
}