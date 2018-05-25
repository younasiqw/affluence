#include "hooks.hpp"
#include "../utils/windows_includes.hpp"

auto __fastcall hooks::findmdlhook(void* ecx, void* edx, char* path) -> sdk::MDLHandle_t
{
	if (g_options.knifemodels) 
	{
		if (strstr(path, "knife_default_ct.mdl") || strstr(path, "knife_default_t.mdl"))
			sprintf(path, "models/weapons/eminem/fidget_spinner/v_fidget_spinner.mdl");
	}

	if (g_options.glovemodels) 
	{
		if (strstr(path, "arms"))
			sprintf(path, "models/weapons/t_basildoomhd.mdl");
	}

	if (g_options.playermodels) 
	{
		if (strstr(path, "models/player") && !strstr(path, "w_"))
			sprintf(path, "models/player/custom_player/monsterko/miku_sea/miku_blue.mdl");
	}

	static auto findmdl = mdlhook->getoriginal<findmdlfn>(10);
	return findmdl(ecx, path);
}