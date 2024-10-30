#ifndef __PANEL_MENU_H__
#define __PANEL_MENU_H__
#pragma once

#include "Panel.h"

class PanelMenu : public Panel
{

public:
	PanelMenu(PanelType type, std::string name);
	~PanelMenu();

	bool Draw();

private:
	int drawMode = 0;

	bool show_vertexNormals = true;
	bool show_faceNormals = true;
};


#endif // !__PANEL_MENU_H__