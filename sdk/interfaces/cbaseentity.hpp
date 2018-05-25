#pragma once

#include "icliententity.hpp"
#include "../misc/getvfunc.hpp"
#include "../../utils/netvarmanager.hpp"

namespace sdk
{
	class C_BaseEntity : public IClientEntity
	{
	public:
		NETVAR_OFFSET(m_bIsAutoaimTarget, "CBaseEntity", "m_bIsAutoaimTarget", +0x4, int);
		NETVAR(m_nModelIndex, "CBaseEntity", "m_nModelIndex", unsigned);
		NETVAR(m_iTeamNum, "CBaseEntity", "m_iTeamNum", int);
		NETVAR(m_aimPunchAngle, "CBaseEntity", "m_aimPunchAngle", Vector);
		NETVAR(m_flSimulationTime, "CBaseEntity", "m_flSimulationTime", float);
		NETVAR(m_vecOrigin, "CBaseEntity", "m_vecOrigin", Vector);

		void SetModelIndex(const int index)
		{
			vfunc<void(__thiscall*)(C_BaseEntity*, int)>(this, 75)(this, index);
		}

		bool IsPlayer()
		{
			return vfunc<bool(__thiscall*)(C_BaseEntity*)>(this, 152)(this);
		};

		void* Animating()
		{
			return reinterpret_cast<void*>(uintptr_t(this) + 0x4);
		}

		bool SetupBones(matrix* out, int max_bones, int mask, float time)
		{
			using fn = bool(__thiscall*)(void*, matrix*, int, int, float);
			return vfunc<fn>(Animating(), 13)(Animating(), out, max_bones, mask, time);
		}
	};

	class C_BaseCombatCharacter : public C_BaseEntity
	{
	public:
		PNETVAR(m_hActiveWeapon, "CBaseCombatCharacter", "m_hActiveWeapon", CBaseHandle);
		PNETVAR(m_hMyWeapons, "CBaseCombatCharacter", "m_hMyWeapons", CBaseHandle);
		PNETVAR(m_hMyWearables, "CBaseCombatCharacter", "m_hMyWearables", CBaseHandle);
	};

	class C_BasePlayer : public C_BaseCombatCharacter
	{
	public:
		NETVAR(m_lifeState, "CBasePlayer", "m_lifeState", LifeState);
		NETVAR(m_hViewModel, "CBasePlayer", "m_hViewModel[0]", CBaseHandle);
		NETVAR(m_fFlags, "CBasePlayer", "m_fFlags", int);
		NETVAR(m_iHealth, "CBasePlayer", "m_iHealth", int);
		NETVAR(m_vecViewOffset, "CBasePlayer", "m_vecViewOffset[0]", Vector);

		bool IsAlive()
		{
			return m_lifeState() == LIFE_ALIVE;
		};

		Vector GetBonePosition(int bone)
		{
			matrix bonematrix[128];

			if (SetupBones(bonematrix, 128, BoneFlags::BONE_USED_BY_ANYTHING, 0.0f))
				return Vector(bonematrix[bone][0][3], bonematrix[bone][1][3], bonematrix[bone][2][3]);

			return Vector{};
		}

		Vector GetEyePosition()
		{
			return m_vecOrigin() + m_vecViewOffset();
		}
	};

	class C_BaseCombatWeapon : public C_BaseEntity
	{
	public:
		NETVAR(m_iViewModelIndex, "CBaseCombatWeapon", "m_iViewModelIndex", int);
		NETVAR(m_iWorldModelIndex, "CBaseCombatWeapon", "m_iWorldModelIndex", int);
		NETVAR(m_iWorldDroppedModelIndex, "CBaseCombatWeapon", "m_iWorldDroppedModelIndex", int);
		NETVAR(m_hWeaponWorldModel, "CBaseCombatWeapon", "m_hWeaponWorldModel", CBaseHandle);
	};

	class C_BaseAttributableItem : public C_BaseCombatWeapon
	{
	public:
		NETVAR(m_iAccountID, "CBaseAttributableItem", "m_iAccountID", int);
		NETVAR(m_iItemDefinitionIndex, "CBaseAttributableItem", "m_iItemDefinitionIndex", int);
		NETVAR(m_iItemIDHigh, "CBaseAttributableItem", "m_iItemIDHigh", int);
		NETVAR(m_iEntityQuality, "CBaseAttributableItem", "m_iEntityQuality", int);
		NETVAR(m_szCustomName, "CBaseAttributableItem", "m_szCustomName", char[32]);
		NETVAR(m_nFallbackPaintKit, "CBaseAttributableItem", "m_nFallbackPaintKit", unsigned);
		NETVAR(m_nFallbackSeed, "CBaseAttributableItem", "m_nFallbackSeed", unsigned);
		NETVAR(m_flFallbackWear, "CBaseAttributableItem", "m_flFallbackWear", float);
		NETVAR(m_nFallbackStatTrak, "CBaseAttributableItem", "m_nFallbackStatTrak", unsigned);
	};

	class C_BaseViewModel : public C_BaseEntity
	{
	public:
		NETVAR(m_hOwner, "CBaseViewModel", "m_hOwner", CBaseHandle);
		NETVAR(m_hWeapon, "CBaseViewModel", "m_hWeapon", CBaseHandle);
		NETPROP(m_nSequence, "CBaseViewModel", "m_nSequence");
	};

	class C_PlayerResource
	{
	public:
		NETPROP(m_iTeam, "CPlayerResource", "m_iTeam");
	};

	class C_CS_PlayerResource : public C_PlayerResource
	{
	public:
		NETVAR(m_iCompetitiveRanking, "CCSPlayerResource", "m_iCompetitiveRanking", int[65]);
		NETVAR(m_iCompetitiveWins, "CCSPlayerResource", "m_iCompetitiveWins", int[65]);
		NETVAR(m_szClan, "CCSPlayerResource", "m_szClan", char[65][32]);
		NETVAR(m_nActiveCoinRank, "CCSPlayerResource", "m_nActiveCoinRank", unsigned[65]);
		NETVAR(m_nMusicID, "CCSPlayerResource", "m_nMusicID", unsigned[65]);
	};
}