#pragma once

#include <string.h>
#include "checksum_crc.hpp"
#include "checksum_md5.hpp"
#include "../math/qangle.hpp"
#include "../math/vector.hpp"

namespace sdk
{
	class CUserCmd
	{
	public:
		CUserCmd()
		{
			memset(this, 0, sizeof(*this));
		};

		virtual ~CUserCmd() {};

		CRC32_t GetChecksum(void) const
		{
			CRC32_t crc;
			CRC32_Init(&crc);

			CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
			CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
			CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
			CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
			CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
			CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
			CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
			CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
			CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
			CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
			CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
			CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
			CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
			CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));

			CRC32_Final(&crc);
			return crc;
		}

		int     command_number;    
		int     tick_count;       
		QAngle  viewangles;       
		Vector  aimdirection;      
		float   forwardmove;      
		float   sidemove;        
		float   upmove;           
		int     buttons;          
		char    impulse;          
		int     weaponselect;     
		int     weaponsubtype;     
		int     random_seed;      
		short   mousedx;           
		short   mousedy;          
		bool    hasbeenpredicted; 
		char    pad_0x4C[0x18];  
	};

	class CVerifiedUserCmd
	{
	public:
		CUserCmd m_cmd;
		CRC32_t  m_crc;
	};
}