#ifndef IPLAYERINFOMANAGER002_H
#define IPLAYERINFOMANAGER002_H

class IPlayerInfo;

namespace SourceSdk
{
	abstract_class IPlayerInfoManager002
	{
	public:
		virtual IPlayerInfo * GetPlayerInfo( edict_t *pEdict ) = 0;
		virtual void *GetGlobalVars() = 0;
	};
};

#endif // IPLAYERINFOMANAGER002_H