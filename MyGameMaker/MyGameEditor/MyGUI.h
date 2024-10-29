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
		static MyGUI instance;  // La instancia �nica de la clase Engine
		return instance;
	}

	// Evita la copia y asignaci�n del singleton
	MyGUI(const MyGUI&) = delete;
	MyGUI& operator=(const MyGUI&) = delete;
	MyGUI(MyGUI&&) noexcept = delete;

	void Awake(SDL_Window* window, void* context);

	void render();

	void processEvent(const SDL_Event& event) override;

	PanelConsole& console() const { return *_console; }

private:
	MyGUI() = default;
	~MyGUI();
	//List of panels
	PanelConsole* _console = nullptr;
	PanelMenu* _menu = nullptr;
	
	void addPanel(Panel* panel);
};