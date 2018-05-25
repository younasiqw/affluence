#pragma once

#include "windows_includes.hpp"
#include "../main/interfaces.hpp"
#include "../sdk/math/vector2d.hpp"

class render
{
public:
	auto drawrectangle(int, int, int, int, sdk::Color) -> void;
	auto drawoutlinedrectangle(int, int, int, int, sdk::Color) -> void;
	auto drawstring(int, int, sdk::Color, unsigned int, const char*) -> void;
	auto drawstringunicode(int, int, sdk::Color, unsigned int, const wchar_t*) -> void;
	auto drawgradientfilledrectangle(sdk::Vector2D, sdk::Vector2D, sdk::Color, sdk::Color) -> void;
};

extern render g_render;