#include "hooks.hpp"
#include "../utils/inputmanager.hpp"
#include "../utils/windows_includes.hpp"

auto __fastcall hooks::createmovehook(sdk::IClientMode* thisptr, void* edx, float frametime, sdk::CUserCmd* cmd) -> bool
{
	static auto createmove = clienthook->getoriginal<createmovefn>(24);	
	createmove(thisptr, edx, frametime, cmd);

	if (!cmd || !cmd->command_number)
		return createmove;

	if (g_options.bunnyhop)
		g_misc.bunnyhop(cmd); 

	if (g_options.clantag)
		g_misc.clantag("affluence");
	else
		g_misc.clantag(""); 

	if (g_options.moonwalk)
		g_misc.moonwalk(cmd);

	if (g_options.revealranks && sdk::IN_SCORE)
		g_misc.revealranks();

	if (g_options.antiuntrusted)
		cmd->viewangles.normalizeangles();

	return false;
}