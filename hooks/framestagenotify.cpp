#include "hooks.hpp"
#include "../utils/windows_includes.hpp"

auto __stdcall hooks::framestagenotify(sdk::ClientFrameStage_t stage) -> void
{
	static auto framestagenotify = clienthook->getoriginal<framestagenotifyfn>(36);
	framestagenotify(g_interfaces.g_client, stage);
}