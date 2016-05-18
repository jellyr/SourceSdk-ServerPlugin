#ifndef EDICT_H
#define EDICT_H

#include "SdkPreprocessors.h"

#include "server_class.h"
#include "iserverunknown.h"

namespace SourceSdk
{
	class CSaveRestoreData;
	class IServerEntity;
	class IChangeInfoAccessor;
	struct edict_t;
	class CBaseNetworkable;
	class CBaseEntity;
	class ICollideable;
	class IHandleEntity;

	typedef edict_t* CCheckTransmitInfo;

	struct PVSInfo_t
	{
		short		m_nHeadNode;			
		short		m_nClusterCount;		
		unsigned short *m_pClusters;	
		short		m_nAreaNum;
		short		m_nAreaNum2;
		float		m_vCenter[3];
	private:
		unsigned short m_pClustersInline[MAX_FAST_ENT_CLUSTERS];
	};

	class IServerNetworkable
	{
	public:
		virtual IHandleEntity	*GetEntityHandle() = 0;
		virtual ServerClass*	GetServerClass() = 0;
		virtual edict_t			*GetEdict() const = 0;
#undef GetClassName
		virtual const char*		GetClassName() const = 0;
		virtual void			Release() = 0;
		virtual int				AreaNum() const = 0;
		virtual CBaseNetworkable* GetBaseNetworkable() = 0;
		virtual CBaseEntity*	GetBaseEntity() = 0;
		virtual PVSInfo_t*		GetPVSInfo() = 0;
	protected:
		virtual					~IServerNetworkable() {}
	};

	enum MapLoadType_t
	{
		MapLoad_NewGame = 0,
		MapLoad_LoadGame,
		MapLoad_Transition,
		MapLoad_Background,
	};

	class CGlobalVarsBase
	{
	public:
		CGlobalVarsBase(bool bIsClient);
		bool IsClient() const;
		int GetNetworkBase(int nTick, int nEntity);
	public:
		float			realtime;
		int				framecount;
		float			absoluteframetime;
		float			curtime;
		float			frametime;
		int				maxClients;
		int				tickcount;
		float			interval_per_tick;
		float			interpolation_amount;
		int				simTicksThisFrame;
		int				network_protocol;
		CSaveRestoreData *pSaveData;
	private:
		bool			m_bClient;
		int				nTimestampNetworkingBase;
		int				nTimestampRandomizeWindow;
	};

	inline int CGlobalVarsBase::GetNetworkBase(int nTick, int nEntity)
	{
		int nEntityMod = nEntity % nTimestampRandomizeWindow;
		int nBaseTick = nTimestampNetworkingBase * (int)((nTick - nEntityMod) / nTimestampNetworkingBase);
		return nBaseTick;
	}

	inline CGlobalVarsBase::CGlobalVarsBase(bool bIsClient) :
		m_bClient(bIsClient),
		nTimestampNetworkingBase(100),
		nTimestampRandomizeWindow(32)
	{
	}

	inline bool CGlobalVarsBase::IsClient() const
	{
		return m_bClient;
	}

	class CGlobalVarsBase_csgo
	{
	public:
		CGlobalVarsBase_csgo(bool bIsClient);
		bool IsClient() const;
		int GetNetworkBase(int nTick, int nEntity);
	public:
		float			realtime;
		int				framecount;
		float			absoluteframetime;
		float			absoluteframestarttimestddev;
		float			curtime;
		float			frametime;
		int				maxClients;
		int				tickcount;
		float			interval_per_tick;
		float			interpolation_amount;
		int				simTicksThisFrame;
		int				network_protocol;
		CSaveRestoreData *pSaveData;
	private:
		bool			m_bClient;
		bool			m_bRemoteClient;
		int				nTimestampNetworkingBase;
		int				nTimestampRandomizeWindow;
	};

	inline int CGlobalVarsBase_csgo::GetNetworkBase( int nTick, int nEntity )
	{
		int nEntityMod = nEntity % nTimestampRandomizeWindow;
		int nBaseTick = nTimestampNetworkingBase * (int)( ( nTick - nEntityMod ) / nTimestampNetworkingBase );
		return nBaseTick;
	}

	inline CGlobalVarsBase_csgo::CGlobalVarsBase_csgo( bool bIsClient ) :
		m_bClient( bIsClient ),
		nTimestampNetworkingBase( 100 ),
		nTimestampRandomizeWindow( 32 )
	{
	}

	inline bool CGlobalVarsBase_csgo::IsClient() const
	{
		return m_bClient;
	}

	class CGlobalVars : public CGlobalVarsBase
	{	
	public:
		CGlobalVars( bool bIsClient );
	public:
		const char *	mapname;
		int				mapversion;
		const char *	startspot;
		MapLoadType_t	eLoadType;
		bool			bMapLoadFailed;
		bool			deathmatch;
		bool			coop;
		bool			teamplay;
		int				maxEntities;
	};

	inline CGlobalVars::CGlobalVars( bool bIsClient ) : 
		CGlobalVarsBase( bIsClient )
	{
	}

	class CGlobalVars_csgo : public CGlobalVarsBase_csgo
	{
	public:
		CGlobalVars_csgo(bool bIsClient);
	public:
		const char *	mapname;
		const char *	mapGroupName;
		int				mapversion;
		const char *	startspot;
		MapLoadType_t	eLoadType;
		bool			bMapLoadFailed;
		bool			deathmatch;
		bool			coop;
		bool			teamplay;
		int				maxEntities;
		int				serverCount;
		edict_t			*pEdicts;
	};

	inline CGlobalVars_csgo::CGlobalVars_csgo(bool bIsClient) :
		CGlobalVarsBase_csgo(bIsClient)
	{
		serverCount = 0;
	}

	struct edict_t_csgo
	{
		IServerNetworkable*		GetNetworkable();
		IServerUnknown*			GetUnknown();
#undef GetClassName
		const char *		GetClassName() const;
		bool				IsFree() const;
		int	m_fStateFlags;
#if VALVE_LITTLE_ENDIAN
		short m_NetworkSerialNumber;
		short m_EdictIndex;
#else
		short m_EdictIndex;
		short m_NetworkSerialNumber;
#endif
		IServerNetworkable	*m_pNetworkable;
		IServerUnknown		*m_pUnk;
	};

	struct edict_t : edict_t_csgo
	{	
		float		freetime;
	};

	inline bool edict_t_csgo::IsFree() const
	{
		return (m_fStateFlags & FL_EDICT_FREE) != 0;
	}

	inline IServerUnknown* edict_t_csgo::GetUnknown()
	{
		return m_pUnk;
	}

	inline IServerNetworkable* edict_t_csgo::GetNetworkable()
	{
		return m_pNetworkable;
	}

	inline const char *	edict_t_csgo::GetClassName() const
	{
		if ( !m_pUnk )
			return "";
		return m_pNetworkable->GetClassName();
	}
};

#endif // EDICT_H