#ifndef __PANEL_INSPECTOR_H__
#define __PANEL_INSPECTOR_H__
#pragma once

#include "Panel.h"
#include <vector>

class PanelInspector : public Panel
{

public:
	PanelInspector(PanelType type, std::string name);
	~PanelInspector();

	bool Draw();

private:
	bool openHeader = true;	// Delete Me
	std::string text = "GameObject";
	char buffer[128]; // Temporary buffer to hold the string

	// Tag
	std::string currentTagg = "Untagged";
	std::vector<std::string> options = { "Untagged", "Player", "Other" };

	// Layer
	std::string currentLayer = "Default";
	std::vector<std::string> layers = { "Default", "TransparentFX", "Ignore Raycast", "Water", "UI", "PostProcessing" };

	bool showPerTriangleNormals = false;
	bool showPerFaceNormals = false;
	bool showCheckers = false;
};

#endif // !__PANEL_INSPECTOR_H__

