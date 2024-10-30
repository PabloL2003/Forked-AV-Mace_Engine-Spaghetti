#pragma once
#include "Panel.h"

#include <vector>

class PanelConfiguration :  public Panel
{
public:
	PanelConfiguration(PanelType type, std::string name);
	~PanelConfiguration();

	bool Draw();
};

