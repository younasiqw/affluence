#include "../utils/inputmanager.hpp"
#include "menu.hpp"
#include "rendermenu.hpp"

auto additem(int indexname, const char* title, float* value, float min, float max, float step, bool btab = false) -> int
{
	g_rendermenu.frame[indexname].title = title;
	g_rendermenu.frame[indexname].value = value;
	g_rendermenu.frame[indexname].min = min;
	g_rendermenu.frame[indexname].max = max;
	g_rendermenu.frame[indexname].step = step;
	g_rendermenu.frame[indexname].isTab = btab;

	return (indexname + 1);
}

auto menu::initialise() -> void
{
	visible = false;

	g_inputmanager.register_hotkey(VK_UP, []()
	{
		if (g_renderdefinitions.index > 0)
			g_renderdefinitions.index--;
		else
			g_renderdefinitions.index = g_renderdefinitions.items - 1;
	});

	g_inputmanager.register_hotkey(VK_DOWN, []()
	{
		if (g_renderdefinitions.index < g_renderdefinitions.items - 1)
			g_renderdefinitions.index++;
		else
			g_renderdefinitions.index = 0;
	});

	g_inputmanager.register_hotkey(VK_LEFT, []()
	{
		if (g_rendermenu.frame[g_renderdefinitions.index].value)
		{
			g_rendermenu.frame[g_renderdefinitions.index].value[0] -= g_rendermenu.frame[g_renderdefinitions.index].step;

			if (g_rendermenu.frame[g_renderdefinitions.index].value[0] < g_rendermenu.frame[g_renderdefinitions.index].min)
				g_rendermenu.frame[g_renderdefinitions.index].value[0] = g_rendermenu.frame[g_renderdefinitions.index].max;
		}
	});

	g_inputmanager.register_hotkey(VK_RIGHT, []()
	{
		if (g_rendermenu.frame[g_renderdefinitions.index].value)
		{
			g_rendermenu.frame[g_renderdefinitions.index].value[0] += g_rendermenu.frame[g_renderdefinitions.index].step;

			if (g_rendermenu.frame[g_renderdefinitions.index].value[0] > g_rendermenu.frame[g_renderdefinitions.index].max)
				g_rendermenu.frame[g_renderdefinitions.index].value[0] = g_rendermenu.frame[g_renderdefinitions.index].min;
		}
	});
}

auto menu::draw() -> void
{
	if (visible)
		render();
}

auto menu::render()	-> void
{
	int i = 0;
	int x = 40;
	int y = 300;
	int w=  150;
	int h = 16;

	i = additem(i, "chams", &g_renderdefinitions.tab, 0, 1, 1, true);
	if (g_renderdefinitions.tab == 1)
	{
		i = additem(i, " - player chams", &g_options.playerchams, 0, 1, 1, false);
		i = additem(i, " - weapon chams", &g_options.weaponchams, 0, 1, 1, false);
	}

	i = additem(i, "misc", &g_renderdefinitions.tab2, 0, 1, 1, true);
	if (g_renderdefinitions.tab2 == 1)
	{
		i = additem(i, " - auto jump", &g_options.bunnyhop, 0, 1, 1, false);
		i = additem(i, " - clantag spam", &g_options.clantag, 0, 1, 1, false);
		i = additem(i, " - moonwalk", &g_options.moonwalk, 0, 1, 1, false);
		i = additem(i, " - watermark", &g_options.watermark, 0, 1, 1, false);
		i = additem(i, " - rank revealer", &g_options.revealranks, 0, 1, 1, false);
	}

	i = additem(i, "models", &g_renderdefinitions.tab3, 0, 1, 1, true);
	if (g_renderdefinitions.tab3 == 1)
	{
		i = additem(i, " - glove models", &g_options.glovemodels, 0, 1, 1, false);
		i = additem(i, " - knife models", &g_options.knifemodels, 0, 1, 1, false);
		i = additem(i, " - player models", &g_options.playermodels, 0, 1, 1, false);
	}

	i = additem(i, "settings", &g_renderdefinitions.tab4, 0, 1, 1, true);
	if (g_renderdefinitions.tab4 == 1)
	{
		i = additem(i, " - unload cheat", &g_options.unloadcheat, 0, 1, 1, false);
		i = additem(i, " - anti untrusted", &g_options.antiuntrusted, 0, 1, 1, false);
	}

	g_renderdefinitions.items = i;
	g_render.drawoutlinedrectangle(x - 1, 270 + 1 - 1, w + 2, 23 + 4, sdk::Color(173, 173, 173, 255));
	g_render.drawrectangle(x, 270 + 1, w, 23 + 4, sdk::Color(67, 67, 67, 246));
	g_render.drawoutlinedrectangle(x - 1, 292 + 1 - 1, w + 2, g_renderdefinitions.items * 23 + 5, sdk::Color(173, 173, 173, 255));
	g_render.drawrectangle(x, 292 + 1, w, g_renderdefinitions.items * 23 + 3, sdk::Color(67, 67, 67, 246));
	g_render.drawstring(82, 275, sdk::Color(255, 255, 255, 255), font_framework, "affluence");

	for (int i = 0; i < g_renderdefinitions.items; i++)
	{
		int in = (int)*g_rendermenu.frame[i].value;
		wchar_t out[12];
		_itow_s(in, out, sizeof(out) / 2, 10);
		char mbstr[11];
		std::wcstombs(mbstr, out, 11);

		g_render.drawstring(x + 5, y + (22 * i), (i == g_renderdefinitions.index) ? sdk::Color(150, 150, 150, 255) : sdk::Color(255, 255, 255, 255), font_framework, g_rendermenu.frame[i].title);

		if (!g_rendermenu.frame[i].isTab)
			g_render.drawstring(x + 5 + 100 + 20, y + (22 * i), (i == g_renderdefinitions.index) ? sdk::Color(150, 150, 150, 255) : sdk::Color(255, 255, 255, 255), font_framework, mbstr);
	}
}

auto menu::handleinput(WPARAM vk) -> void
{
	if (visible)
		handleinput(vk);
}

auto menu::toggle()	-> void
{
	visible = !visible;
	g_interfaces.g_engineclient->ClientCmd(visible ? "cl_mouseenable 0" : "cl_mouseenable 1");
}

menu g_menu;