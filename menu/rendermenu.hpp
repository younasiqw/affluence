#pragma once

#include "../main/interfaces.hpp"

struct render_struct
{
	const char* title;
	float* value;
	float min;
	float max;
	float step;
	bool isTab;
};

class render_definitions
{
public:
	int index = 0;
	int items = 0;
	float tab, tab2, tab3, tab4;
};

class render_menu
{
public:
	render_struct frame[150];
};

extern render_menu g_rendermenu;
extern render_definitions g_renderdefinitions;