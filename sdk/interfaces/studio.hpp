#pragma once

#include "enums.hpp"
#include "../math/vector.hpp"

namespace sdk
{
	typedef float Quaternion[4];
	typedef float RadianEuler[3];
	typedef unsigned short MDLHandle_t;

	struct mstudiobone_t
	{
		mstudiobone_t() {}

		int                    sznameindex;
		inline char* const     pszName(void) const { return ((char *)this) + sznameindex; }
		int                    parent;
		int                    bonecontroller[6];
		Vector                 pos;
		Quaternion             quat;
		RadianEuler            rot;
		Vector                 posscale;
		Vector                 rotscale;
		matrix3x4_t            poseToBone;
		Quaternion             qAlignment;
		int                    flags;
		int                    proctype;
		int                    procindex;
		mutable int            physicsbone;
		inline void*           pProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((unsigned char*)this) + procindex); };
		int                    surfacepropidx;
		inline char* const     pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
		inline int             GetSurfaceProp(void) const { return surfacepropLookup; }
		int                    contents;
		int                    surfacepropLookup;
		int                    m_iPad01[7];
	private:
		mstudiobone_t(const mstudiobone_t& vOther);
	};

	struct mstudiobbox_t
	{
		int         bone;
		int         group;
		Vector      bbmin;
		Vector      bbmax;
		int         szhitboxnameindex;
		int32_t     m_iPad01[3];
		float       m_flRadius;
		int32_t     m_iPad02[4];

		const char* GetName()
		{
			if (!szhitboxnameindex) return nullptr;
			return (const char*)((uint8_t*)this + szhitboxnameindex);
		}
	};

	struct mstudiohitboxset_t
	{
		int    sznameindex;
		int    numhitboxes;
		int    hitboxindex;

		const char* GetName()
		{
			if (!sznameindex) return nullptr;
			return (const char*)((uint8_t*)this + sznameindex);
		}

		mstudiobbox_t* GetHitbox(int i)
		{
			if (i > numhitboxes) return nullptr;
			return (mstudiobbox_t*)((uint8_t*)this + hitboxindex) + i;
		}
	};

	struct model_t
	{
		void*   fnHandle;
		char    szName[260];
		Vector  vecMins;
		Vector  vecMaxs;
		float   radius;
		char    pad[0x1C];
		__int32 nLoadFlags;
		__int32 nServerCount;
		__int32 type;
		__int32 flags;
	};

	class studiohdr_t
	{
	public:
		__int32 id;
		__int32 version;
		long    checksum;
		char    szName[64];
		__int32 length;
		Vector  vecEyePos;
		Vector  vecIllumPos;
		Vector  vecHullMin;
		Vector  vecHullMax;
		Vector  vecBBMin;
		Vector  vecBBMax;
		__int32 flags;
		__int32 numbones;
		__int32 boneindex;
		__int32 numbonecontrollers;
		__int32 bonecontrollerindex;
		__int32 numhitboxsets;
		__int32 hitboxsetindex;
		__int32 numlocalanim;
		__int32 localanimindex;
		__int32 numlocalseq;
		__int32 localseqindex;
		__int32 activitylistversion;
		__int32 eventsindexed;
		__int32 numtextures;
		__int32 textureindex;

		mstudiohitboxset_t* GetHitboxSet(int i)
		{
			if (i > numhitboxsets) return nullptr;
			return (mstudiohitboxset_t*)((uint8_t*)this + hitboxsetindex) + i;
		}

		mstudiobone_t* GetBone(int i)
		{
			if (i > numbones) return nullptr;
			return (mstudiobone_t*)((uint8_t*)this + boneindex) + i;
		}
	};
}
