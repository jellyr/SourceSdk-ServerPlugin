#ifndef INTERFACESPROXY_H
#define INTERFACESPROXY_H

#include "SdkPreprocessors.h"

#include "Interfaces/IEngineTrace/IEngineTrace.h"
#include "Interfaces/IPlayerInfoManager/IPlayerInfoManager.h"
#include "Interfaces/IGameEventManager/IGameEventManager.h"
#include "Interfaces/IServerGameClients/IServerGameClients.h"
#include "Interfaces/IServerGameDLL/IServerGameDLL.h"
#include "Interfaces/IServerGameEnts/IServerGameEnts.h"
#include "Interfaces/IServerPluginHelpers/IServerPluginHelpers.h"
#include "Interfaces/IVEngineServer/IVEngineServer.h"
#include "Console/icvar.h"
#include "Interfaces/iserverplugin.h"
#include "Interfaces/edict.h"
#include "Interfaces/Protobuf/netmessages.pb.h"
#include "Interfaces/server_class.h"

#include "Maths/Vector.h"

#include "Misc/temp_basicstring.h"

//#define WANT_VIRTUAL_TABLES

#ifdef WANT_VIRTUAL_TABLES
#	include <signal.h>
#	define VT_TRAP raise(SIGINT);
#else
#	define VT_TRAP
#endif

typedef unsigned long DWORD;

#define IFACE_PTR(x) (( DWORD* )*( DWORD* )x)

#ifdef WIN32
#	define VFNT __thiscall
#else
#	define VFNT
#endif

#ifdef WIN32
#	define INIT_VIRTUAL_FUNCTION(iface, vfid, fn) CopyVirtualFunction(IFACE_PTR( iface ), vfid , (DWORD*)(& _vfptr_##fn ))
#else
#	define INIT_VIRTUAL_FUNCTION(iface, vfid, fn) CopyVirtualFunction(IFACE_PTR( iface ), vfid, (DWORD*)(& _vfptr_##fn ))
#endif

struct edict_t;
struct bf_write;
class CBaseEntity;
class IRecipientFilter;
struct Vector;
struct CGlobalVars;
class INetChannelInfo;
class ITraceFilter;
struct trace_t;
struct Ray_t;

namespace SourceSdk
{
	void CopyVirtualFunction(DWORD const * copy_from_vtptr, const int vf_id, DWORD * copy_to_fn);
	void GetCommandLineString(basic_string & cmd);
	void GetGameDir(basic_string & dir);

	enum GameId
	{
		CounterStrikeSource = 1,
		CounterStrikeGlobalOffensive,
		CounterStrikePromod,
		TeamFortress2,
		BlackMesa
	};

	namespace InterfacesProxy
	{
		extern GameId m_game;

		extern void* m_enginetrace;
		extern int m_enginetrace_version;

		extern void* m_playerinfomanager;
		extern int m_playerinfomanager_version;

		extern void* m_gameeventmanager;
		extern int m_gameeventmanager_version;

		extern void* m_servergameclients;
		extern int m_servergameclients_version;

		extern void* m_servergamedll;
		extern int m_servergamedll_version;

		extern void* m_servergameents;
		extern int m_servergameents_version;

		extern void* m_serverpluginhelpers;
		extern int m_serverpluginhelpers_version;

		extern void* m_engineserver;
		extern int m_engineserver_version;

		extern void* m_cvar;
		extern int m_enginecvar_version;

		typedef float(VFNT * GetTickInterval_t)(void const * const);
		extern volatile GetTickInterval_t _vfptr_GetTickInterval;

		typedef ServerClass*(VFNT * GetAllServerClasses_t)(void const * const this_ptr);
		extern volatile GetAllServerClasses_t _vfptr_GetAllServerClasses;

		typedef void*(VFNT * GetPlayerInfo_t)(void const * const, edict_t*);
		extern volatile GetPlayerInfo_t _vfptr_GetPlayerInfo;

		typedef void*(VFNT * GetGlobalVars_t)(void const * const);
		extern volatile GetGlobalVars_t _vfptr_GetGlobalVars;

		typedef edict_t*(VFNT * BaseEntityToEdict_t)(void const * const, void*);
		extern volatile BaseEntityToEdict_t _vfptr_BaseEntityToEdict;

		typedef CBaseEntity*(VFNT * EdictToBaseEntity_t)(void const * const, edict_t*);
		extern volatile EdictToBaseEntity_t _vfptr_EdictToBaseEntity;

		typedef void(VFNT * ClientEarPosition_t)(void const * const, edict_t*, Vector*);
		extern volatile ClientEarPosition_t _vfptr_ClientEarPosition;

		typedef int(VFNT * GetPlayerUserid_t)(void const * const, edict_t const * );
		extern volatile GetPlayerUserid_t _vfptr_GetPlayerUserid;

		typedef char const *(VFNT * GetPlayerNetworkIDString_t)(void const * const, edict_t const * );
		extern volatile GetPlayerNetworkIDString_t _vfptr_GetPlayerNetworkIDString;

		typedef int(VFNT * GetEntityCount_t)(void const * const);
		extern volatile GetEntityCount_t _vfptr_GetEntityCount;

		typedef int(VFNT * IndexOfEdict_t)(void const * const, edict_t const *);
		extern volatile IndexOfEdict_t _vfptr_IndexOfEdict;

		typedef edict_t*(VFNT * PEntityOfEntIndex_t)(void const * const, int);
		extern volatile PEntityOfEntIndex_t _vfptr_PEntityOfEntIndex;

		typedef INetChannelInfo*(VFNT * GetPlayerNetInfo_t)(void const * const, int);
		extern volatile GetPlayerNetInfo_t _vfptr_GetPlayerNetInfo;

		typedef void(VFNT * ServerCommand_t)(void const * const, char const *);
		extern volatile ServerCommand_t _vfptr_ServerCommand;

		typedef void(VFNT * ServerExecute_t)(void const * const);
		extern volatile ServerExecute_t _vfptr_ServerExecute;

		typedef bf_write*(VFNT * UserMessageBegin_t)(void const * const, IRecipientFilter*, int);
		extern volatile UserMessageBegin_t _vfptr_UserMessageBegin;

		typedef bf_write*(VFNT * SendUserMessage_t)(void const * const, IRecipientFilter*, int, google::protobuf::Message const &);
		extern volatile SendUserMessage_t _vfptr_SendUserMessage;

		typedef void(VFNT * MessageEnd_t)(void const * const);
		extern volatile MessageEnd_t _vfptr_MessageEnd;

		typedef void(VFNT * LogPrint_t)(void const * const, char const *);
		extern volatile LogPrint_t _vfptr_LogPrint;

		typedef void(VFNT * TraceRay_t)(void const * const, void const *, unsigned int, ITraceFilter*, void*);
		extern volatile TraceRay_t _vfptr_TraceRay;

		float Call_GetTickInterval();

		ServerClass* Call_GetAllServerClasses();
		
		void* Call_GetPlayerInfo(edict_t*);

		void* Call_GetGlobalVars();

		edict_t* Call_BaseEntityToEdict(void * const);

		CBaseEntity* Call_EdictToBaseEntity(edict_t const * const);

		void Call_ClientEarPosition(edict_t*, Vector*);

		int Call_GetPlayerUserid(edict_t const *);

		char const * Call_GetPlayerNetworkIDString(edict_t const *);

		int Call_GetEntityCount();

		int Call_IndexOfEdict(edict_t const *);

		edict_t* Call_PEntityOfEntIndex(int);

		INetChannelInfo* Call_GetPlayerNetInfo(int);

		void Call_ServerCommand(char const *);

		void Call_ServerExecute();

		bf_write* Call_UserMessageBegin(IRecipientFilter*, int);

		bf_write* Call_SendUserMessage(IRecipientFilter*, int, google::protobuf::Message const &);

		void Call_MessageEnd();

		void Call_LogPrint(char const *);

		void Call_TraceRay(void const *, unsigned int, ITraceFilter*, void*);

		void* LoadInterface(CreateInterfaceFn factory, const char * name_no_version, int & loaded_version);
	
		bool Load(CreateInterfaceFn game_factory, CreateInterfaceFn interface_factory);
		GameId GetGameId();
		
		IServerPluginHelpers001* GetServerPluginHelpers();
		IGameEventManager002* GetGameEventManager();
		void* GetCvar();

		void ICvar_RegisterConCommand(ConCommandBase *pCommandBase);
		void ICvar_RegisterConCommand(ConCommandBase_csgo *pCommandBase);
		CVarDLLIdentifier_t ICvar_AllocateDLLIdentifier();
		void ICvar_UnregisterConCommands(CVarDLLIdentifier_t id);
		void ICvar_UnregisterConCommand(ConCommandBase *pCommandBase);
		void ICvar_UnregisterConCommand(ConCommandBase_csgo *pCommandBase);
		void* ICvar_FindVar(const char *var_name);
		bool ConVar_GetBool(void *convar);
		char const * ConCommand_GetName(void const * const command);

		template <typename T>
		void ConVar_SetValue(void *convar, T v);

		char const * ConVar_GetString(void *convar);
		int ConVar_GetInt(void* convar);
		void* ICvar_FindCommand(const char *name);


	}
}

#endif // INTERFACESPROXY_H
