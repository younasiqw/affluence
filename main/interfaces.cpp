#include "interfaces.hpp"
#include "../utils/windows_includes.hpp"
#include "../utils/utils.hpp"
#include "../hooks/hooks.hpp"
#include "../menu/menu.hpp"
#include "../utils/inputmanager.hpp"

template<typename T>
inline T findinterface(const char* dll, const char* name)
{
	return (T)(((void *(*)(const char*, void*))GetProcAddress(GetModuleHandleA(dll), "CreateInterface"))(name, 0));
}

template<typename T>
inline T findexport(const char* dll, const char* name)
{
	return (T)((void*(*)(const char*, const char*))GetProcAddress(GetModuleHandleA(dll), name));
}

auto interfaces::initialise() -> void
{
	g_msg = findexport<MsgFn>("tier0.dll", "Msg");
	g_warning = findexport<WarningFn>("tier0.dll", "Warning");

	g_client = findinterface<sdk::IBaseClientDLL*>("client.dll", "VClient018");
	g_cliententity = findinterface<sdk::IClientEntityList*>("client.dll", "VClientEntityList003");
	g_engineclient = findinterface<sdk::IVEngineClient*>("engine.dll", "VEngineClient014");
	g_modelinfo = findinterface<sdk::IVModelInfoClient*>("engine.dll", "VModelInfoClient004");
	g_modelrender = findinterface<sdk::IVModelRender*>("engine.dll", "VEngineModel016");
	g_panel = findinterface<sdk::IPanel*>("vgui2.dll", "VGUI_Panel009");
	g_surface = findinterface<sdk::ISurface*>("vguimatsurface.dll", "VGUI_Surface031");
	g_materialsystem = findinterface<sdk::IMaterialSystem*>("materialsystem.dll", "VMaterialSystem080");
	g_renderview = findinterface<sdk::IVRenderView*>("engine.dll", "VEngineRenderView014");
	g_clientmode = **reinterpret_cast<sdk::IClientMode***>((*reinterpret_cast<uintptr_t**>(g_client))[10] + 0x5u);
	g_mdlcache = findinterface<sdk::IMDLCache*>("datacache.dll", "MDLCache004");

	g_globalvars = **(sdk::CGlobalVarsBase***)(g_utils.patternscan("client.dll", "A1 ? ? ? ? 5E 8B 40 10") + 1);
	g_d3d9 = **(IDirect3DDevice9***)(g_utils.patternscan("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
	g_client_state = **(sdk::CClientState***)(g_utils.patternscan("engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3") + 1);
	g_input = *(sdk::CInput**)(g_utils.patternscan("client.dll", "B9 ? ? ? ? 8B 40 38 FF D0 84 C0 0F 85") + 1);
	g_localplayer = *(C_LocalPlayer*)(g_utils.patternscan("client.dll", "8B 0D ? ? ? ? 83 FF FF 74 07") + 2);

	g_inputmanager.initialise();
	g_hooks.initialise();
	g_fonts.initialise();
	g_menu.initialise();

	g_inputmanager.register_hotkey(VK_INSERT, []() 
	{
		g_menu.toggle();
	});
}

interfaces g_interfaces;