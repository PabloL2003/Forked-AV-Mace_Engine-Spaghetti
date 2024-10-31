#ifndef __PANEL_INSPECTOR_H__
#define __PANEL_INSPECTOR_H__
#pragma once

#include <vector>
#include <memory>  
#include "Panel.h"
#include "MyGameEngine/GameObject.h"

class PanelInspector : public Panel
{

public:
	PanelInspector(PanelType type, std::string name);
	~PanelInspector();

	std::string text() const { return _text; }
	std::string currentTagg() const { return _currentTagg; }
	std::string currentLayer() const { return _currentLayer; }
	bool Draw();

private:
	std::string _text = "GameObject";
	char buffer[128]; // Temporary buffer to hold the string

	// Tag
	std::string _currentTagg = "Untagged";
	std::vector<std::string> options = { "Untagged", "Player", "Other" };

	// Layer
	std::string _currentLayer = "Default";
	std::vector<std::string> layers = { "Default", "TransparentFX", "Ignore Raycast", "Water", "UI", "PostProcessing" };

	bool showPerTriangleNormals = false;
	bool showPerFaceNormals = false;
	bool showCheckers = false;
};

#endif // !__PANEL_INSPECTOR_H__