#include "PanelConfiguration.h"

#include <imgui.h>
#include <SDL2/SDL.h>
#include <windows.h>

#include "MyGameEngine/Engine.h"
#include "MyGameEngine/types.h"
#include "MyGameEngine/Renderer.h"
#include "MyGameEngine/MyWindow.h"

std::vector<float> fpsHistory(100, 0.0f);
int historyIndex = 0;
MEMORYSTATUSEX memInfo;

PanelConfiguration::PanelConfiguration(PanelType type, std::string name) : Panel(type, name, WINDOW_WIDTH, 200) {}

PanelConfiguration::~PanelConfiguration() {}

bool PanelConfiguration::Draw()
{
    ImGui::Begin("Configuration",&showWindow);

    if (ImGui::CollapsingHeader("FPS")){
        // 1. Gráfico de FPS
        fpsHistory[historyIndex] = *Engine::Instance().GetFPS();
        historyIndex = (historyIndex + 1) % fpsHistory.size();  // Mantener el índice circular

        ImGui::Text("FPS Graph", *Engine::Instance().GetFPS());
        ImGui::PlotLines("", fpsHistory.data(), fpsHistory.size(), historyIndex, nullptr, 0.0f, 240, ImVec2(0, 40));
        ImGui::Text("FPS: %.1f", *Engine::Instance().GetFPS());
    }

    if (ImGui::CollapsingHeader("Modules Configuration"))
    {
        // Window settings
        ImGui::Text("Window");
        int windowWidth = Engine::Instance().window->width();
		int windowHeight = Engine::Instance().window->height(); 
        ImGui::SliderInt("Width", &windowWidth, 400, 1920);
        ImGui::SliderInt("Height", &windowHeight, 400, 1080);
        Engine::Instance().window->ResizeWindow(windowWidth, windowHeight);
    }


    if (ImGui::CollapsingHeader("System Information"))
    {
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        ImGui::Text("Memory Usage: %.2f MB", (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024.0f * 1024.0f));
        ImGui::Text("Hardware:");
        ImGui::BulletText("CPU Cores: %d", SDL_GetCPUCount());
        ImGui::BulletText("RAM: %d GB", SDL_GetSystemRAM() / 1024);

        ImGui::Text("Software Versions:");
        ImGui::BulletText("SDL Version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
        ImGui::BulletText("OpenGL Version: %s", glGetString(GL_VERSION));
    }

    ImGui::End();

    if (!showWindow) {
        SwitchState();
    }

	return true;
}
