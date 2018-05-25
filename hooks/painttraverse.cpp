#include "../utils/windows_includes.hpp"
#include "../menu/menu.hpp"
#include "hooks.hpp"

auto __stdcall hooks::painttraversehook(sdk::vgui::VPANEL vpanel, bool forcerepaint, bool allowforce) -> void
{
	static auto painttraverse = panelhook->getoriginal<painttraversefn>(41);
	painttraverse(g_interfaces.g_panel, vpanel, forcerepaint, allowforce);

	static uint32_t hudzoompanel;
	static uint32_t focusoverlaypanel;

	const char* name = g_interfaces.g_panel->PanelName(vpanel);

	if (!hudzoompanel)
	{
		if (lstrcmpA(name, "HudZoom") == 0)
			hudzoompanel = vpanel;
	}

	if (hudzoompanel == vpanel)
		return;

	if (!focusoverlaypanel)
	{
		if (lstrcmpA(name, "FocusOverlayPanel") == 0)
			focusoverlaypanel = vpanel;
	}

	if (focusoverlaypanel == vpanel)
	{
		if (g_menu.visible)
			g_menu.draw();

		if (g_options.watermark)
			g_render.drawstring(7, 7, sdk::Color(255, 255, 255, 255), font_framework, "affluence for counter-strike: global offensive");
	}
}
