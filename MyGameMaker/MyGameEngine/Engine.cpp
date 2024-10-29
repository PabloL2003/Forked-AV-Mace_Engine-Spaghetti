#include "Engine.h"

#include "MyWindow.h"
#include "Input.h"
#include "Renderer.h"

void Engine::Awake()
{
    LOG(LogType::LOG_INFO, "Welcome to AV_Mace Engine!");
    window = new MyWindow();
    input = new Input();
	renderer = new Renderer();

    LOG(LogType::LOG_CHANGEENV, "------------- Application Init -------------");
    window->Awake();
    input->Awake();
}

void Engine::Start()
{
	window->Start();
    input->Start();
	renderer->Start();
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

Engine::~Engine()
{
	window->close();
    input->CleanUp();
	delete window;
	delete input;
}
