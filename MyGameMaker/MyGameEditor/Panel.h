#ifndef __PANEL_H__
#define __PANEL_H__
#pragma once

#include <string>

enum class PanelType
{
	MENU,
	CONSOLE,
	CONFIGURATION,
	HIERARCHY,
	INSPECTOR,

	UNKNOWN
};

class Panel
{
public:

	Panel(PanelType type, std::string name, int width, int height) : type(type), name(name), width(width), height(height) {}
	virtual ~Panel() {}

	virtual void Start() {}
	virtual bool Draw() = 0;
	virtual bool CleanUp() { return true; }

	virtual void OnSceneChange() {}

	virtual PanelType GetType() { return type; }
	virtual std::string GetName() { return name; }

	virtual bool GetState() { return enabled; }
	virtual void SetState(bool state) { this->enabled = state; }
	virtual void SwitchState() { 
		enabled = !enabled; 
		showWindow = enabled;
	}

protected:

	PanelType type = PanelType::UNKNOWN;
	std::string name;
	bool enabled = false;
	int width, height;
	bool showWindow = true;
};

#endif // !__PANEL_H__
