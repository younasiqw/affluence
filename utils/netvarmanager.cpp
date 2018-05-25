#include "windows_includes.hpp"
#include "netvarmanager.hpp"
#include "../sdk/include/sdk.hpp"
#include "../main/interfaces.hpp"

netvarmanager::netvarmanager()
{
	for (auto clazz = g_interfaces.g_client->GetAllClasses(); clazz; clazz = clazz->m_pNext)
	{
		if (clazz->m_pRecvTable)
			dumprecursive(clazz->m_pNetworkName, clazz->m_pRecvTable, 0);
	}
}

auto netvarmanager::dumprecursive(const char* base_class, sdk::RecvTable* table, const std::uint16_t offset) -> void
{
	for (auto i = 0; i < table->m_nProps; ++i)
	{
		const auto prop_ptr = &table->m_pProps[i];
		char hash_name[256];

		if (!prop_ptr || isdigit(prop_ptr->m_pVarName[0]))
			continue;

		if (strcmp(prop_ptr->m_pVarName, "baseclass") == 0)
			continue;

		if (prop_ptr->m_RecvType == sdk::DPT_DataTable &&
			prop_ptr->m_pDataTable != nullptr &&
			prop_ptr->m_pDataTable->m_pNetTableName[0] == 'D')
		{
			dumprecursive(base_class, prop_ptr->m_pDataTable, std::uint16_t(offset + prop_ptr->m_Offset));
		}

		strcpy_s(hash_name, base_class);
		strcat_s(hash_name, "->");
		strcat_s(hash_name, prop_ptr->m_pVarName);

		const auto hash = fnv::hash_runtime(hash_name);
		const auto total_offset = std::uint16_t(offset + prop_ptr->m_Offset);

		m_props[hash] =
		{
			prop_ptr,
			total_offset
		};
	}
}