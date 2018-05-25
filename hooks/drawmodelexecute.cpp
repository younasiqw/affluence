#include "../utils/windows_includes.hpp"
#include "hooks.hpp"

auto __stdcall hooks::drawmodelexecutehook(sdk::IMatRenderContext* ctx, const sdk::DrawModelState_t& state, const sdk::ModelRenderInfo_t& info, sdk::matrix3x4_t* bone) -> void
{
	static auto drawmodelexecute = modelhook->getoriginal<drawmodelexecutefn>(21);

	const auto model = info.pModel;
	bool player = strstr(model->szName, "models/player") != nullptr;
	bool weapons = strstr(model->szName, "models/weapons") != nullptr; 

	if (player && g_options.playerchams && g_interfaces.g_localplayer->m_iTeamNum())
	{
		sdk::IMaterial* material = g_interfaces.g_materialsystem->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER);
		g_interfaces.g_modelrender->ForcedMaterialOverride(material);
	}

	if (weapons && g_options.weaponchams)
	{
		sdk::IMaterial* material = g_interfaces.g_materialsystem->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER);
		g_interfaces.g_modelrender->ForcedMaterialOverride(material);
	}

	drawmodelexecute(g_interfaces.g_modelrender, ctx, state, info, bone); 
	g_interfaces.g_modelrender->ForcedMaterialOverride(nullptr);
}
