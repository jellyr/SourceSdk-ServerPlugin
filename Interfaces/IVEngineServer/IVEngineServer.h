#ifndef IVENGINESERVER_H
#define IVENGINESERVER_H

#include "SdkPreprocessors.h"

#include "../../Maths/Vector.h"
#include "../../Containers/bitbuf.h"
#include "../../Containers/bitvec.h"
#include "../server_class.h"
#include "../edict.h"
#include "../inetchannelinfo.h"
#include "../Protobuf/netmessages.pb.h"

namespace SourceSdk
{
	struct PVSInfo_t;
	struct player_info_t;
	struct bbox_t;
	struct model_t;
	struct HltvReplayParams_t;
	class KeyValues;
	class CPlayerBitVec;
	class IRecipientFilter;
	class client_textmessage_t;
	class ICollideable;
	class ISpatialPartition;
	class IScratchPad3D;
	class CSharedEdictChangeInfo;
	class IChangeInfoAccessor;
	class IAchievementMgr;
	class ISPSharedMemory;
	class CGamestatsData;
	class CSteamID;
	class CEngineHltvInfo_t;
	class VPlane;
	class IServer;
	typedef int QueryCvarCookie_t;
	enum eFindMapResult {
		eFindMap_Found,
		eFindMap_NotFound,
		eFindMap_FuzzyMatch,
		eFindMap_NonCanonical,
		eFindMap_PossiblyAvailable
	};
	enum CrossPlayPlatform_t
	{
		CROSSPLAYPLATFORM_UNKNOWN,
		CROSSPLAYPLATFORM_PC,
		CROSSPLAYPLATFORM_X360,
		CROSSPLAYPLATFORM_PS3,
		CROSSPLAYPLATFORM_LAST,
	};
	enum soundlevel_t
	{
		SNDLVL_NONE			= 0,
		SNDLVL_20dB			= 20,
		SNDLVL_25dB			= 25,
		SNDLVL_30dB			= 30,
		SNDLVL_35dB			= 35,
		SNDLVL_40dB			= 40,
		SNDLVL_45dB			= 45,
		SNDLVL_50dB			= 50,
		SNDLVL_55dB			= 55,
		SNDLVL_IDLE			= 60,
		SNDLVL_60dB			= 60,
		SNDLVL_65dB			= 65,
		SNDLVL_STATIC		= 66,
		SNDLVL_70dB			= 70,
		SNDLVL_NORM			= 75,
		SNDLVL_75dB			= 75,
		SNDLVL_80dB			= 80,
		SNDLVL_TALKING		= 80,
		SNDLVL_85dB			= 85,
		SNDLVL_90dB			= 90,
		SNDLVL_95dB			= 95,
		SNDLVL_100dB		= 100,
		SNDLVL_105dB		= 105,
		SNDLVL_110dB		= 110,
		SNDLVL_120dB		= 120,
		SNDLVL_130dB		= 130,
		SNDLVL_GUNFIRE		= 140,
		SNDLVL_140dB		= 140,
		SNDLVL_150dB		= 150,
		SNDLVL_180dB		= 180
	};
	enum TerrainModType
	{
		TMod_Sphere = 0,
		TMod_Suck,
		TMod_AABB
	};
	class CTerrainModParams
	{
	public:
		enum
		{
			TMOD_SUCKTONORMAL	   = ( 1 << 0 ),
			TMOD_STAYABOVEORIGINAL = ( 1 << 1 )
		};
		CTerrainModParams() { m_Flags = 0; }
		Vector		m_vCenter;
		Vector		m_vNormal;
		int			m_Flags;
		float		m_flRadius;
		Vector		m_vecMin;
		Vector		m_vecMax;
		float		m_flStrength;
		float		m_flMorphTime;
	};
};

#include "IVEngineServer021.h"
#include "IVEngineServer023.h"

#endif // IVENGINESERVER_H
