#include "inputmanager.hpp"

input_manager::input_manager() : m_hTargetWindow(nullptr), m_ulOldWndProc(0) {}

input_manager::~input_manager()
{
	if (m_ulOldWndProc)
		SetWindowLongPtr(m_hTargetWindow, GWLP_WNDPROC, m_ulOldWndProc);

	m_ulOldWndProc = 0;
}

auto input_manager::initialise() -> void
{
	D3DDEVICE_CREATION_PARAMETERS params;

	if (FAILED(g_interfaces.g_d3d9->GetCreationParameters(&params)))
		throw std::runtime_error("GetCreationParameters failed");

	m_hTargetWindow = params.hFocusWindow;
	m_ulOldWndProc = SetWindowLongPtr(m_hTargetWindow, GWLP_WNDPROC, (LONG_PTR)wnd_proc);

	if (!m_ulOldWndProc)
		throw std::runtime_error("SetWindowLongPtr failed");
}

auto __stdcall input_manager::wnd_proc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param) -> LRESULT
{
	g_inputmanager.process_message(msg, w_param, l_param);

	return CallWindowProcW((WNDPROC)g_inputmanager.m_ulOldWndProc, wnd, msg, w_param, l_param);
}

auto input_manager::process_message(UINT msg, WPARAM w_param, LPARAM l_param) -> bool
{
	switch (msg)
	{
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_LBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_XBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
	case WM_XBUTTONUP:
		return process_mouse_message(msg, w_param, l_param);
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return process_keybd_message(msg, w_param, l_param);
	default:
		return false;
	}
}

auto input_manager::process_mouse_message(UINT msg, WPARAM w_param, LPARAM l_param)	-> bool
{
	auto key = VK_LBUTTON;
	auto state = keystate::NONE;

	switch (msg)
	{
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		state = msg == WM_MBUTTONUP ? keystate::UP : keystate::DOWN;
		key = VK_MBUTTON;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		state = msg == WM_RBUTTONUP ? keystate::UP : keystate::DOWN;
		key = VK_RBUTTON;
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		state = msg == WM_LBUTTONUP ? keystate::UP : keystate::DOWN;
		key = VK_LBUTTON;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		state = msg == WM_XBUTTONUP ? keystate::UP : keystate::DOWN;
		key = (HIWORD(w_param) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
		break;
	default:
		return false;
	}

	if (state == keystate::UP && m_iKeyMap[int(key)] == keystate::DOWN)
	{
		m_iKeyMap[int(key)] = keystate::PRESSED;

		auto& hotkey_callback = m_Hotkeys[key];

		if (hotkey_callback)
			hotkey_callback();
	}
	else
	{
		m_iKeyMap[int(key)] = state;
	}

	return true;
}

auto input_manager::process_keybd_message(UINT msg, WPARAM w_param, LPARAM l_param)	-> bool
{
	const auto key = w_param;
	auto state = keystate::NONE;

	switch (msg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		state = keystate::DOWN;
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		state = keystate::UP;
		break;
	default:
		return false;
	}

	if (state == keystate::UP && m_iKeyMap[int(key)] == keystate::DOWN)
	{
		m_iKeyMap[int(key)] = keystate::PRESSED;

		auto& hotkey_callback = m_Hotkeys[key];

		if (hotkey_callback)
			hotkey_callback();
	}
	else
	{
		m_iKeyMap[int(key)] = state;
	}

	return true;
}

auto input_manager::get_key_state(std::uint32_t vk)	-> keystate
{
	return m_iKeyMap[vk];
}

auto input_manager::is_key_down(std::uint32_t vk) -> bool
{
	return m_iKeyMap[vk] == keystate::DOWN;
}

auto input_manager::was_key_pressed(std::uint32_t vk) -> bool
{
	if (m_iKeyMap[vk] == keystate::PRESSED)
	{
		m_iKeyMap[vk] = keystate::UP;

		return true;
	}

	return false;
}

auto input_manager::register_hotkey(std::uint32_t vk, std::function<void(void)> f) -> void
{
	m_Hotkeys[vk] = f;
}

auto input_manager::remove_hotkey(std::uint32_t vk) -> void
{
	m_Hotkeys[vk] = nullptr;
}

input_manager g_inputmanager;