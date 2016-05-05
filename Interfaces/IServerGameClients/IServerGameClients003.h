#ifndef ISERVERGAMECLIENTS003_H
#define ISERVERGAMECLIENTS003_H

namespace SourceSdk
{
	abstract_class IServerGameClients003
	{
	public:
		virtual void			GetPlayerLimits( int& minplayers, int& maxplayers, int &defaultMaxPlayers ) const = 0;
		virtual bool			ClientConnect( edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen ) = 0;
		virtual void			ClientActive( edict_t *pEntity, bool bLoadGame ) = 0;
		virtual void			ClientDisconnect( edict_t *pEntity ) = 0;
		virtual void			ClientPutInServer( edict_t *pEntity, char const *playername ) = 0;
		virtual void			ClientCommand( edict_t *pEntity ) = 0;
		virtual void			SetCommandClient( int index ) = 0;
		virtual void			ClientSettingsChanged( edict_t *pEdict ) = 0;
		virtual void			ClientSetupVisibility( edict_t *pViewEntity, edict_t *pClient, unsigned char *pvs, int pvssize ) = 0;
		virtual float			ProcessUsercmds( edict_t *player, bf_read *buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused ) = 0;
		virtual void			PostClientMessagesSent( void ) = 0;
		virtual CPlayerState	*GetPlayerState( edict_t *player ) = 0;
		virtual void			ClientEarPosition( edict_t *pEntity, Vector *pEarOrigin ) = 0;
		virtual int				GetReplayDelay( edict_t *player, int& entity ) = 0;
		virtual void			GetBugReportInfo( char *buf, int buflen ) = 0;
	};
};

#endif // ISERVERGAMECLIENTS003_H
