#include "../utils/windows_includes.hpp"
#include "../hooks/hooks.hpp"
#include "interfaces.hpp"

auto initialise(LPVOID value) -> void
{
	g_interfaces.initialise();

	while (!g_options.unloadcheat)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	FreeLibraryAndExitThread(static_cast<HMODULE>(value), 1);
}

auto uninitialise() -> bool
{
	g_hooks.uninitialise();

	return true;
}

auto __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) -> BOOL
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(instance);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)initialise, instance, 0, 0);
		break;

	case DLL_PROCESS_DETACH:
		if (reserved == nullptr)
			return uninitialise();
		break;
	}

	return true;
}
