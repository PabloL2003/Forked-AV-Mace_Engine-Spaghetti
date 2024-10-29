#include "Engine.h"

#include "MyWindow.h"
#include "Input.h"

void Engine::Awake()
{
    window = new MyWindow();
    input = new Input();

    window->Awake();
    input->Awake();
}

void Engine::Start()
{
	window->Start();
    input->Start();
}

bool Engine::PreUpdate()
{
    return true;
}

void Engine::Update(double dt)
{
    this->dt = dt;
}

void Engine::CleanUp()
{

}


std::vector<LogInfo> Engine::GetLogs()
{
    return logs;
}

void Engine::AddLog(LogType type, const char* entry)
{
    std::string toAdd = entry;
    LogInfo info = { type, toAdd };

    logs.push_back(info);
}

void Engine::CleanLogs()
{
    logs.clear();
}
