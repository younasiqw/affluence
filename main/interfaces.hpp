#pragma once

#include "../sdk/include/sdk.hpp"
#include "../utils/vmthook.hpp"

class interfaces
{
public:
	void initialise();

	class C_LocalPlayer
	{
		friend bool operator==(const C_LocalPlayer& lhs, void* rhs);
	public:
		C_LocalPlayer() : m_local(nullptr) {}

		operator bool() const 
		{ 
			return* m_local != nullptr;
		}

		operator sdk::C_BasePlayer*() const
		{ 
			return* m_local; 
		}

		sdk::C_BasePlayer* operator->()
		{
			return* m_local;
		}
	private:
		sdk::C_BasePlayer** m_local;
	};

	typedef void(__cdecl* MsgFn)(const char*);
	typedef void(__cdecl* WarningFn)(const char*);

	sdk::CGlobalVarsBase* g_globalvars;
	sdk::CClientState* g_client_state;
	sdk::CInput* g_input;
	sdk::IBaseClientDLL* g_client;
	sdk::IClientEntityList* g_cliententity;
	sdk::IVEngineClient* g_engineclient;
	sdk::IVModelInfoClient* g_modelinfo;
	sdk::IVModelRender* g_modelrender;
	sdk::IPanel* g_panel;
	sdk::ISurface* g_surface;
	sdk::IMaterialSystem* g_materialsystem;
	sdk::IVRenderView* g_renderview;
	sdk::IClientMode* g_clientmode;
	sdk::IMDLCache* g_mdlcache;

	C_LocalPlayer g_localplayer;
	IDirect3DDevice9* g_d3d9;
	MsgFn g_msg;
	WarningFn g_warning;
};

extern interfaces g_interfaces;