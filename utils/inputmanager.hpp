#pragma once

#include "windows_includes.hpp"
#include "../main/interfaces.hpp"

enum class keystate
{
	NONE = 1,
	DOWN,
	UP,
	PRESSED
};

DEFINE_ENUM_FLAG_OPERATORS(keystate);

class input_manager
{
public:
	input_manager();
	~input_manager();

	auto initialise() -> void;
	auto get_main_window() const -> HWND { return m_hTargetWindow; }
	auto get_key_state(uint32_t vk) -> keystate;
	auto is_key_down(uint32_t vk) -> bool;
	auto was_key_pressed(uint32_t vk) -> bool;
	auto register_hotkey(uint32_t vk, std::function<void(void)> f) -> void;
	auto remove_hotkey(uint32_t vk) -> void;
private:
	static auto WINAPI wnd_proc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param) -> LRESULT;
	auto process_message(UINT msg, WPARAM w_param, LPARAM l_param) -> bool;
	auto process_mouse_message(UINT msg, WPARAM w_param, LPARAM l_param) -> bool;
	auto process_keybd_message(UINT msg, WPARAM w_param, LPARAM l_param) -> bool;

	HWND m_hTargetWindow;
	LONG_PTR m_ulOldWndProc;
	keystate m_iKeyMap[256];

	std::function<void(void)> m_Hotkeys[256];
};

extern input_manager g_inputmanager;