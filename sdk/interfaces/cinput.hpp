#pragma once

#include "cusercmd.hpp"

namespace sdk
{
	class CInput
	{
	public:
		inline CUserCmd* GetUserCmd(int sequence_number);
		inline CVerifiedUserCmd* GetVerifiedCmd(int sequence_number);
	private:
		void*               pvftable;
	public:
		bool                m_fTrackIRAvailable;
		bool                m_fMouseInitialized;
		bool                m_fMouseActive;
		bool                m_fJoystickAdvancedInit;
	private:
		char                pad_0x08[0x2C];
	public:
		void*               m_pKeys;
	private:
		char                pad_0x38[0x64];
		int					pad_0x41;
		int					pad_0x42;
	public:
		bool                m_fCameraInterceptingMouse;
		bool                m_fCameraInThirdPerson;
		bool                m_fCameraMovingWithMouse;
		Vector				m_vecCameraOffset;
		char				pad_hurensohn[3];
		bool                m_fCameraDistanceMove;
		int                 m_nCameraOldX;
		int                 m_nCameraOldY;
		int                 m_nCameraX;
		int                 m_nCameraY;
		bool                m_CameraIsOrthographic;
		Vector              m_angPreviousViewAngles;
		Vector              m_angPreviousViewAnglesTilt;
		float               m_flLastForwardMove;
		int                 m_nClearInputState;
		CUserCmd*           m_pCommands;
		CVerifiedUserCmd*   m_pVerifiedCommands;
	};

	CUserCmd* CInput::GetUserCmd(int sequence_number)
	{
		return &m_pCommands[sequence_number % 150];
	}

	CVerifiedUserCmd* CInput::GetVerifiedCmd(int sequence_number)
	{
		return &m_pVerifiedCommands[sequence_number % 150];
	}
}