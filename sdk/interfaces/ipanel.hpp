#pragma once

#include "../misc/getvfunc.hpp"

namespace sdk
{
	class IPanel
	{
	public:
		const char* PanelName(unsigned int vguiPanel)
		{
			typedef const char *(__thiscall* tGetName)(void*, unsigned int);
			return vfunc<tGetName>(this, 36)(this, vguiPanel);
		}

		const char* ClassName(unsigned int vguiPanel)
		{
			typedef const char *(__thiscall* tGetClassName)(void*, unsigned int);
			return vfunc<tGetClassName>(this, 37)(this, vguiPanel);
		}
	};
}

