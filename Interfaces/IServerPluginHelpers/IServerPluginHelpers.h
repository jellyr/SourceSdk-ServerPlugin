#ifndef ISERVERPLUGINHELPERS_H
#define ISERVERPLUGINHELPERS_H

#include "SdkPreprocessors.h"

namespace SourceSdk
{
	struct edict_t;
	class KeyValues;
	class IServerPluginCallbacks;
	typedef int QueryCvarCookie_t;
	typedef enum
	{
		DIALOG_MSG = 0,
		DIALOG_MENU,
		DIALOG_TEXT,
		DIALOG_ENTRY,
		DIALOG_ASKCONNECT
	} DIALOG_TYPE;
	
};

#include "IServerPluginHelpers001.h"

#endif // ISERVERPLUGINHELPERS_H
