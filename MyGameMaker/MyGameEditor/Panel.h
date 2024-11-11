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

	//ImVec4 red(1.0f, 0.0f, 0.0f, 1.0f); 
	//ImVec4 green(0.0f, 1.0f, 0.0f, 1.0f);
	//ImVec4 blue(0.0f, 0.0f, 1.0f, 1.0f); 
	//ImVec4 white(1.0f, 1.0f, 1.0f, 1.0f);
	//ImVec4 black(0.0f, 0.0f, 0.0f, 1.0f);
	//ImVec4 yellow(1.0f, 1.0f, 0.0f, 1.0f);
	//ImVec4 cyan(0.0f, 1.0f, 1.0f, 1.0f); 
	//ImVec4 magenta(1.0f, 0.0f, 1.0f, 1.0f);
	//ImVec4 gray(0.5f, 0.5f, 0.5f, 1.0f);
	//ImVec4 darkGray(0.2f, 0.2f, 0.2f, 1.0f); 
	//ImVec4 lightGray(0.8f, 0.8f, 0.8f, 1.0f);
	//ImVec4 orange(1.0f, 0.5f, 0.0f, 1.0f);
	//ImVec4 purple(0.5f, 0.0f, 0.5f, 1.0f);
	//ImVec4 brown(0.5f, 0.25f, 0.0f, 1.0f);
	//ImVec4 clear(0.0f, 0.0f, 0.0f, 0.0f); 
};

#endif // !__PANEL_H__
