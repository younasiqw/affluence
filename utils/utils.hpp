#pragma once

class utils
{
public:
	auto waitonmodules(std::int32_t timeout, const std::initializer_list<std::wstring>& modules) -> int;
	auto patternscan(const char* dll, const char* signature) -> std::uint8_t*;
};

extern utils g_utils;