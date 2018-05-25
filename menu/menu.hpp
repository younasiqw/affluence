#pragma once

#include "../utils/fonts.hpp" 
#include "../main/interfaces.hpp"

class menu
{
public:
	bool visible;
public:
	auto initialise() -> void;
	auto draw() -> void;
	auto render() -> void;
	auto handleinput(WPARAM vk) -> void;
	auto toggle() -> void;
	auto menuvisible() const -> bool { return visible; }
};

extern menu g_menu;