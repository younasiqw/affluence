#pragma once

#include "../utils/options.hpp"
#include "../sdk/include/sdk.hpp"

class misc
{
public:
	auto bunnyhop(sdk::CUserCmd*) -> void;
	auto clantag(const char*) -> void;
	auto moonwalk(sdk::CUserCmd*) -> void;
	auto revealranks() -> void;
};

extern misc g_misc;