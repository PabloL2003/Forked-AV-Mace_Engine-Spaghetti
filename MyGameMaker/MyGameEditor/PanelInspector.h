#ifndef __PANEL_INSPECTOR_H__
#define __PANEL_INSPECTOR_H__
#pragma once

#include <vector>
#include <memory>  
#include "Panel.h"
#include "MyGameEngine/types.h"
#include "MyGameEngine/GameObject.h"

class PanelInspector : public Panel
{

public:
	PanelInspector(PanelType type, std::string name);
	~PanelInspector();

	std::string currentTagg() const { return _currentTagg; }
	void setTag(const std::string& tag) { _currentTagg = tag; }
	std::string currentLayer() const { return _currentLayer; }
	void setLayer(const std::string& layer) { _currentLayer = layer; }

	bool Draw();
	void DrawGameObjectControls(GameObject* gameObject);
	void DrawTransformControls(GameObject* gameObject);
	void DrawMeshControls(GameObject* gameObject);
	void DrawMaterialControls(GameObject* gameObject);

private:
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