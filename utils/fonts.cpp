#include "fonts.hpp"
#include "render.hpp"

sdk::vgui::HFont font_watermark;
sdk::vgui::HFont font_weapon;
sdk::vgui::HFont font_name;
sdk::vgui::HFont font_framework;

auto fonts::initialise() -> void
{
	font_watermark = g_interfaces.g_surface->CreateFont_();
	g_interfaces.g_surface->SetFontGlyphSet(font_watermark, "Verdana", 16, 320, 0, 0, sdk::FONTFLAG_OUTLINE);

	font_weapon = g_interfaces.g_surface->CreateFont_();
	g_interfaces.g_surface->SetFontGlyphSet(font_weapon, "Smallest Pixel-7", 10, 100, 0, 0, sdk::FONTFLAG_OUTLINE);

	font_name = g_interfaces.g_surface->CreateFont_();
	g_interfaces.g_surface->SetFontGlyphSet(font_name, "Tahoma", 13, 555, 0, 0, sdk::FONTFLAG_DROPSHADOW);

	font_framework = g_interfaces.g_surface->CreateFont_();
	g_interfaces.g_surface->SetFontGlyphSet(font_framework, "Verdana", 15, 320, 0, 0, sdk::FONTFLAG_OUTLINE);
}

fonts g_fonts;