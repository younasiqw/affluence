#include "misc.hpp"
#include "../utils/utils.hpp"

auto misc::bunnyhop(sdk::CUserCmd* cmd) -> void
{
	if (cmd->buttons & sdk::IN_JUMP && !(g_interfaces.g_localplayer->m_fFlags() & sdk::FL_ONGROUND))
		cmd->buttons &= ~sdk::IN_JUMP;
}

auto misc::clantag(const char* clantag) -> void
{
	static auto pattern = (int(__fastcall*)(const char*))g_utils.patternscan("engine.dll", "53 56 57 8B DA 8B F9 FF 15");
	pattern(clantag);
}

auto misc::moonwalk(sdk::CUserCmd* cmd) -> void
{
	if (cmd->forwardmove > 0)
	{
		cmd->buttons |= sdk::IN_BACK;
		cmd->buttons &= ~sdk::IN_FORWARD;
	}

	if (cmd->forwardmove < 0)
	{
		cmd->buttons |= sdk::IN_FORWARD;
		cmd->buttons &= ~sdk::IN_BACK;
	}

	if (cmd->sidemove < 0)
	{
		cmd->buttons |= sdk::IN_MOVERIGHT;
		cmd->buttons &= ~sdk::IN_MOVELEFT;
	}

	if (cmd->sidemove > 0)
	{
		cmd->buttons |= sdk::IN_MOVELEFT;
		cmd->buttons &= ~sdk::IN_MOVERIGHT;
	}
}

auto misc::revealranks() -> void
{
	typedef char(__cdecl* revealranksfn)(int*);
	static auto pattern = g_utils.patternscan("client.dll", "55 8B EC 8B 0D ? ? ? ? 68");
	int array[3] = { 0, 0, 0 };
	reinterpret_cast<revealranksfn>(pattern)(array);
}

misc g_misc;