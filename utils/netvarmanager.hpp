#pragma once

#include "../sdk/interfaces/datatable.hpp"
#include "../sdk/interfaces/fnvhash.hpp"
#include "windows_includes.hpp"

class netvarmanager
{
private:
	struct stored_data
	{
		sdk::RecvProp* prop_ptr;
		std::uint16_t class_relative_offset;
	};
public:
	static auto get() -> const netvarmanager&
	{
		static netvarmanager instance;
		return instance;
	}

	auto get_offset(const fnv::hash hash) const -> std::uint16_t
	{
		return m_props.at(hash).class_relative_offset;
	}

	auto get_prop(const fnv::hash hash) const -> sdk::RecvProp*
	{
		return m_props.at(hash).prop_ptr;
	}

	__declspec(noinline) static auto get_offset_by_hash(const fnv::hash hash) -> std::uint16_t
	{
		return get().get_offset(hash);
	}

	template<fnv::hash Hash>
	static auto get_offset_by_hash_cached() -> std::uint16_t
	{
		static auto offset = std::uint16_t(0);
		if (!offset)
			offset = get_offset_by_hash(Hash);
		return offset;
	}
private:
	netvarmanager();
	auto dumprecursive(const char* base_class, sdk::RecvTable* table, std::uint16_t offset) -> void;
private:
	std::map<fnv::hash, stored_data> m_props;
};

#define PNETVAR_OFFSET(funcname, class_name, var_name, offset, ...) \
auto funcname() -> std::add_pointer_t<__VA_ARGS__> \
{ \
	constexpr auto hash = fnv::hash_constexpr(class_name "->" var_name); \
	const auto addr = std::uintptr_t(this) + offset + netvarmanager::get_offset_by_hash_cached<hash>(); \
	return reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(addr); \
}

#define PNETVAR(funcname, class_name, var_name, ...) \
	PNETVAR_OFFSET(funcname, class_name, var_name, 0, __VA_ARGS__)

#define NETVAR_OFFSET(funcname, class_name, var_name, offset, ...) \
auto funcname() -> std::add_lvalue_reference_t<__VA_ARGS__> \
{ \
	constexpr auto hash = fnv::hash_constexpr(class_name "->" var_name); \
	const auto addr = std::uintptr_t(this) + offset + netvarmanager::get_offset_by_hash_cached<hash>(); \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(addr); \
}

#define NETVAR(funcname, class_name, var_name, ...) \
	NETVAR_OFFSET(funcname, class_name, var_name, 0, __VA_ARGS__)

#define NETPROP(funcname, class_name, var_name) \
static auto funcname() -> RecvProp* \
{ \
	constexpr auto hash = fnv::hash_constexpr(class_name "->" var_name); \
	static auto prop_ptr = netvarmanager::get().get_prop(hash); \
	return prop_ptr; \
}