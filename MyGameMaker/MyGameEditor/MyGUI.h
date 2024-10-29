#pragma once

#include <list>

#include "MyGameEngine/input.h"
#include "Panel.h"

class PanelConsole;
class PanelMenu;

class MyGUI : public IEventProcessor
{
	std::list<Panel*> _panels;

public:
	static MyGUI& Instance() {
		static MyGUI instance;  // La instancia única de la clase Engine
		return instance;
	}

	// Evita la copia y asignación del singleton
	MyGUI(const MyGUI&) = delete;
	MyGUI& operator=(const MyGUI&) = delete;

	MyGUI(SDL_Window* window, void* context);
	MyGUI(MyGUI&&) noexcept = delete;
	MyGUI(const MyGUI&) = delete;
	MyGUI& operator=(const MyGUI&) = delete;
	~MyGUI();



	void render();

	void processEvent(const SDL_Event& event) override;

	PanelConsole& console() const { return *_console; }

private:
	//List of panels
	PanelConsole* _console = nullptr;
	PanelMenu* _menu = nullptr;
	
	void addPanel(Panel* panel);
};