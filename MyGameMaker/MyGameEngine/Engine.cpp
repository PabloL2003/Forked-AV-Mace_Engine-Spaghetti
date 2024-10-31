#include "Engine.h"

#include "MyWindow.h"
#include "Input.h"
#include "Renderer.h"
#include "Scene.h"

void Engine::Awake()
{
    LOG(LogType::LOG_INFO, "Welcome to AV_Mace Engine!");
    window = new MyWindow();
    input = new Input();
	renderer = new Renderer();
	scene = new Scene("Scene");

    LOG(LogType::LOG_CHANGEENV, "------------- Application Init -------------");
    window->Awake();
    input->Awake();
}

void Engine::Start()
{
	window->Start();
    input->Start();
	renderer->Start();
	scene->Start();
}

bool Engine::PreUpdate()
{
    input->PreUpdate();
    return true;
}

void Engine::Update(double& dt)
{
    this->dt = dt;
	scene->Update(dt);
}

void Engine::PostUpdate()
{
	window->swapBuffers();
}

void drawFloorGrid(int size, double step) {
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    for (double i = -size; i <= size; i += step) {
        glVertex3d(i, 0, -size);
        glVertex3d(i, 0, size);
        glVertex3d(-size, 0, i);
        glVertex3d(size, 0, i);
    }
    glEnd();
}

void Engine::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw floor grid
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(&scene->_camera.view()[0][0]);

    drawFloorGrid(16, 0.25);

    //draw things
    scene->Draw();

    glViewport(0, 0, window->width(), window->height());
    scene->_camera.aspect = static_cast<double>(window->width()) / window->height();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(&scene->_camera.projection()[0][0]);
}

void Engine::CleanUp()
{
    scene->CleanUp();
    window->close();
    input->CleanUp();
    delete scene;
    delete window;
    delete input;
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

}
