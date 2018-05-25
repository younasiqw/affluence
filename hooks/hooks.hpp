#pragma once

#include "../utils/vmthook.hpp"
#include "../main/interfaces.hpp"
#include "../features/misc.hpp"
#include "../utils/math.hpp"

extern vmthook* modelhook;
extern vmthook* clienthook;
extern vmthook* panelhook;
extern vmthook* mdlhook;

class hooks
{
public:
	auto initialise() -> void;
	auto uninitialise() -> void;

	typedef auto(__thiscall* drawmodelexecutefn)(sdk::IVModelRender*, sdk::IMatRenderContext*, const sdk::DrawModelState_t&, const sdk::ModelRenderInfo_t&, sdk::matrix3x4_t*) -> void;
	static auto __stdcall drawmodelexecutehook(sdk::IMatRenderContext*, const sdk::DrawModelState_t&, const sdk::ModelRenderInfo_t&, sdk::matrix3x4_t*) -> void;

	typedef auto(__fastcall* createmovefn)(sdk::IClientMode*, void*, float, sdk::CUserCmd*) -> bool;
	static auto __fastcall createmovehook(sdk::IClientMode*, void*, float, sdk::CUserCmd*) -> bool;

	typedef auto(__thiscall* painttraversefn)(sdk::IPanel*, sdk::vgui::VPANEL, bool, bool) -> void;
	static auto __stdcall painttraversehook(sdk::vgui::VPANEL, bool, bool) -> void;

	typedef auto(__thiscall* findmdlfn)(void*, char*) ->sdk::MDLHandle_t;
	static auto __fastcall findmdlhook(void*, void*, char*) ->sdk::MDLHandle_t;

	typedef auto(__thiscall* framestagenotifyfn)(sdk::IBaseClientDLL*, sdk::ClientFrameStage_t) -> void;
	static auto __stdcall framestagenotify(sdk::ClientFrameStage_t) -> void;
};

extern hooks g_hooks;