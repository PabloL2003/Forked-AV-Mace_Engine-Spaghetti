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
	bool show_hierarchy = true;
	bool show_console = true;
	bool show_inspector = true;
};


#endif // !__PANEL_MENU_H__