#ifndef ISERVERGAMEDLL_H
#define ISERVERGAMEDLL_H

#include <cstdint>

#include "SdkPreprocessors.h"

#include "../iserverplugin.h"
#include "../interface.h"
#include "../edict.h"
#include "../server_class.h"
#include "../datamap.h"

namespace SourceSdk
{
	class CSaveRestoreData;
	class IServerGCLobby;
	class CStandardSendProxies;
	class KeyValues;
	class INetMessage;
	typedef int QueryCvarCookie_t;
	typedef int CRC32_t;
	typedef uint64_t PublishedFileId_t;
};

#include "IServerGameDLL006.h"
#include "IServerGameDLL009.h"
#include "IServerGameDLL005.h"

#endif // ISERVERGAMEDLL_H
