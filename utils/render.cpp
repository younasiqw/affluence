#include "render.hpp"

auto render::drawrectangle(int x, int y, int w, int h, sdk::Color col) -> void
{
	g_interfaces.g_surface->DrawSetColor(col);
	g_interfaces.g_surface->DrawFilledRect(x, y, x + w, y + h);
}

auto render::drawoutlinedrectangle(int x, int y, int w, int h, sdk::Color col) -> void
{
	g_interfaces.g_surface->DrawSetColor(col);
	g_interfaces.g_surface->DrawOutlinedRect(x, y, x + w, y + h);
}

auto render::drawstring(int x, int y, sdk::Color color, unsigned int font, const char* text)	-> void
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	g_interfaces.g_surface->DrawSetTextFont(font);
	g_interfaces.g_surface->DrawSetTextColor(color);
	g_interfaces.g_surface->DrawSetTextPos(x, y);
	g_interfaces.g_surface->DrawPrintText(wcstring, wcslen(wcstring), sdk::FONT_DRAW_DEFAULT);
}

auto render::drawstringunicode(int x, int y, sdk::Color color, unsigned int font, const wchar_t* text) -> void
{
	g_interfaces.g_surface->DrawSetTextColor(color);
	g_interfaces.g_surface->DrawSetTextFont(font);
	g_interfaces.g_surface->DrawSetTextPos(x, y);
	g_interfaces.g_surface->DrawPrintText(text, wcslen(text), 0);
}

auto render::drawgradientfilledrectangle(sdk::Vector2D position, sdk::Vector2D size, sdk::Color top, sdk::Color bottom)	-> void
{
	g_interfaces.g_surface->DrawSetColor(top);
	g_interfaces.g_surface->DrawFilledRectangleFade(position.x, position.y, position.x + size.x, position.y + size.y, 255, 255, false);
	g_interfaces.g_surface->DrawSetColor(bottom);
	g_interfaces.g_surface->DrawFilledRectangleFade(position.x, position.y, position.x + size.x, position.y + size.y, 0, 255, false);
}

render g_render;