#ifndef ISERVERPLUGINHELPERS001_H
#define ISERVERPLUGINHELPERS001_H

namespace SourceSdk
{
	abstract_class IServerPluginHelpers001
	{
	public:
		virtual void CreateMessage( edict_t *pEntity, DIALOG_TYPE type, KeyValues *data, IServerPluginCallbacks *plugin ) = 0;
		virtual void ClientCommand( edict_t *pEntity, const char *cmd ) = 0;
		virtual QueryCvarCookie_t StartQueryCvarValue( edict_t *pEntity, const char *pName ) = 0;
	};
};

#endif // ISERVERPLUGINHELPERS001_H
