#include "../utils/windows_includes.hpp"
#include "hooks.hpp"

vmthook* modelhook;
vmthook* clienthook;
vmthook* panelhook;
vmthook* mdlhook;

auto hooks::initialise() -> void
{
	modelhook = new vmthook(g_interfaces.g_modelrender);
	modelhook->hook((void*)drawmodelexecutehook, 21);

	clienthook = new vmthook(g_interfaces.g_clientmode);
	clienthook->hook((void*)createmovehook, 24);
	clienthook->hook((void*)framestagenotify, 36);

	panelhook = new vmthook(g_interfaces.g_panel);
	panelhook->hook((void*)painttraversehook, 41);

	mdlhook = new vmthook(g_interfaces.g_mdlcache);
	mdlhook->hook((void*)findmdlhook, 10);
}

auto hooks::uninitialise() -> void
{
	delete modelhook;
	delete clienthook;
	delete panelhook;
	delete mdlhook;
}

hooks g_hooks;