#pragma once

#include <cstdint>

#pragma pack(push, 1)

namespace sdk
{
	class INetChannel
	{
	public:
		char pad_0000[20];
		bool m_bProcessingMessages;
		bool m_bShouldDelete;
		char pad_0016[2];
		int32_t m_nOutSequenceNr;
		int32_t m_nInSequenceNr;
		int32_t m_nOutSequenceNrAck;
		int32_t m_nOutReliableState;
		int32_t m_nInReliableState;
		int32_t m_nChokedPackets;
		char pad_0030[1044];
	};

	class CClockDriftMgr
	{
	public:
		float m_ClockOffsets[16];
		uint32_t m_iCurClockOffset;
		uint32_t m_nServerTick;
		uint32_t m_nClientTick;
	};

	class CClientState
	{
	public:
		char pad_0000[156];
		uint32_t m_NetChannel;
		uint32_t m_nChallengeNr;
		char pad_00A4[100];
		uint32_t m_nSignonState;
		char pad_010C[8];
		float m_flNextCmdTime;
		uint32_t m_nServerCount;
		uint32_t m_nCurrentSequence;
		char pad_0120[8];
		CClockDriftMgr m_ClockDriftMgr;
		uint32_t m_nDeltaTick;
		bool m_bPaused;
		char pad_017D[3];
		uint32_t m_nViewEntity;
		uint32_t m_nPlayerSlot;
		char m_szLevelName[260];
		char m_szLevelNameShort[40];
		char m_szGroupName[40];
		char pad_02DC[56];
		uint32_t m_nMaxClients;
		char pad_0314[18940];
		Vector viewangles;

		void ForceFullUpdate()
		{
			m_nDeltaTick = -1;
		}
	};
}