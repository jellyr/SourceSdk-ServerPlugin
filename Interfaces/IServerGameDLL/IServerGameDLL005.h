#ifndef ISERVERGAMEDLL005_H
#define ISERVERGAMEDLL005_H

namespace SourceSdk
{
	abstract_class IServerGameDLL005
	{
	public:
		virtual bool			DLLInit(	CreateInterfaceFn engineFactory, CreateInterfaceFn physicsFactory, CreateInterfaceFn fileSystemFactory, CGlobalVars *pGlobals) = 0;
		virtual bool			GameInit( void ) = 0;
		virtual bool			LevelInit( char const *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background ) = 0;
		virtual void			ServerActivate( edict_t *pEdictList, int edictCount, int clientMax ) = 0;
		virtual void			GameFrame( bool simulating ) = 0;
		virtual void			PreClientUpdate( bool simulating ) = 0;
		virtual void			LevelShutdown( void ) = 0;
		virtual void			GameShutdown( void ) = 0;
		virtual void			DLLShutdown( void ) = 0;
		virtual float			GetTickInterval( void ) const = 0;
		virtual ServerClass*	GetAllServerClasses( void ) = 0;
		virtual const char     *GetGameDescription( void ) = 0;      
		virtual void			CreateNetworkStringTables( void ) = 0;
		virtual CSaveRestoreData  *SaveInit( int size ) = 0;
		virtual void			SaveWriteFields( CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int ) = 0;
		virtual void			SaveReadFields( CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int ) = 0;
		virtual void			SaveGlobalState( CSaveRestoreData * ) = 0;
		virtual void			RestoreGlobalState( CSaveRestoreData * ) = 0;
		virtual void			PreSave( CSaveRestoreData * ) = 0;
		virtual void			Save( CSaveRestoreData * ) = 0;
		virtual void			GetSaveComment( char *comment, int maxlength, float flMinutes, float flSeconds, bool bNoTime = false ) = 0;
		virtual void			WriteSaveHeaders( CSaveRestoreData * ) = 0;
		virtual void			ReadRestoreHeaders( CSaveRestoreData * ) = 0;
		virtual void			Restore( CSaveRestoreData *, bool ) = 0;
		virtual bool			IsRestoring() = 0;
		virtual bool			SupportsSaveRestore() = 0;
		virtual int				CreateEntityTransitionList( CSaveRestoreData *, int ) = 0;
		virtual void			BuildAdjacentMapList( void ) = 0;
		virtual CStandardSendProxies*	GetStandardSendProxies() = 0;
		virtual void			PostInit() = 0;
		virtual void			Think( bool finalTick ) = 0;
		virtual void			PreSaveGameLoaded( char const *pSaveName, bool bCurrentlyInGame ) = 0;
		virtual bool			ShouldHideServer( void ) = 0;
		virtual void			InvalidateMdlCache() = 0;
		virtual void			OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue ) = 0;
		virtual void			PostToolsInit() = 0;
		virtual void			GameServerSteamAPIActivated( bool bActivated ) = 0;
		virtual void			ApplyGameSettings( KeyValues *pKV ) = 0;
		virtual void			GetMatchmakingTags( char *buf, size_t bufSize ) = 0;
		virtual void			ServerHibernationUpdate( bool bHibernating ) = 0;
		virtual bool			ShouldPreferSteamAuth() = 0;
		virtual bool			ShouldAllowDirectConnect() = 0;
		virtual bool			FriendsReqdForDirectConnect() = 0;
		virtual bool			IsLoadTestServer() = 0;
		virtual bool			IsValveDS() = 0;
		virtual KeyValues		*GetExtendedServerInfoForNewClient() = 0;
		virtual void 			UpdateGCInformation() = 0;
		virtual void 			ReportGCQueuedMatchStart( int32_t iReservationStage, uint32_t *puiConfirmedAccounts, int numConfirmedAccounts ) = 0;
		virtual PublishedFileId_t	GetUGCMapFileID( const char *mapName ) = 0;
		virtual void			GetMatchmakingGameData( char *buf, size_t bufSize ) = 0;
		virtual bool			HasPendingMapDownloads() const = 0;
		virtual void			UpdateUGCMap( PublishedFileId_t file ) = 0;
		virtual int				GetMessageEncryptionKey( INetMessage *msg ) = 0;
		virtual bool			ShouldHoldGameServerReservation( float flTime ) = 0;
		virtual bool			OnPureServerFileValidationFailure( edict_t *pPlayer, const char *pszPathID, const char *pszFileName, CRC32_t crcIOSequence, int eFileHashType, int cbFileLen, int nPackFileNumber, int nPackFileID ) = 0;
		virtual void			PrecacheParticleSystemFile( const char *pszFilename ) = 0;
		virtual void			ClientConnectionValidatePreNetChan( bool, const char *, int, unsigned long long ) = 0;
		virtual void			OnEngineClientNetworkEvent( edict_t *, unsigned long long, int, void * ) = 0;
		virtual void			GetNewestSubscribedFiles() = 0;
		//virtual bool			ValidateAndAddActiveCaster( const CSteamID & ) = 0;
	};
};

#endif // ISERVERGAMEDLL005_H