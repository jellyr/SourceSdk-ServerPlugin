#ifndef SDK_PREPROCESSORS
#define SDK_PREPROCESSORS

#include <limits.h>

#define _AssertMsg( _exp, _msg, _executeExp, _bFatal ) do { __analysis_assume( !!(_exp) ); _msg; } while (0)

#ifdef DEBUG
#	define Assert( _exp ) _AssertMsg( _exp, _T("Assertion Failed: ") _T(#_exp), ((void)0), false )
#else
#	define Assert( _exp )
#endif

#define abstract_class class
#define EVENT_DEBUG_ID_INIT			42
#define EVENT_DEBUG_ID_SHUTDOWN		13

#if defined(__i386__) && !defined(VALVE_LITTLE_ENDIAN)
#define VALVE_LITTLE_ENDIAN 1
#endif

#define ABSOLUTE_PLAYER_LIMIT 255

#define TLD_DEF_LEAF_MAX	256
#define TLD_DEF_ENTITY_MAX	1024

#define NUM_ENT_ENTRY_BITS		(MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES			(1 << NUM_ENT_ENTRY_BITS)
#define ENT_ENTRY_MASK			(NUM_ENT_ENTRIES - 1)
#define INVALID_EHANDLE_INDEX	0xFFFFFFFF

#define FL_EDICT_CHANGED	(1<<0)
#define FL_EDICT_FREE		(1<<1)
#define FL_EDICT_FULL		(1<<2)
#define FL_EDICT_FULLCHECK	(0<<0)
#define FL_EDICT_ALWAYS		(1<<3)
#define FL_EDICT_DONTSEND	(1<<4)
#define FL_EDICT_PVSCHECK	(1<<5)
#define FL_FULL_EDICT_CHANGED			(1<<8)

#define PAD_NUMBER(number, boundary) \
	( ((number) + ((boundary)-1)) / (boundary) ) * (boundary)
#define MAX_MAP_CLUSTERS				65536
#define	MAX_EDICT_BITS				11
#define	MAX_EDICTS					(1<<MAX_EDICT_BITS)
#define	MAX_FAST_ENT_CLUSTERS	4
#define	MAX_ENT_CLUSTERS	64
#define MAX_WORLD_AREAS		8

#define FMTFUNCTION( a, b )

#ifndef M_PI
#	define M_PI		3.14159265358979323846f
#endif

#define M_PI_F		((float)(M_PI))

#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

#define DECL_ALIGN(x)			__declspec( align( x ) )

#if defined( GNUC )
#define ALIGN4
#define ALIGN8 
#define ALIGN16
#define ALIGN32
#define ALIGN128

#define ALIGN4_POST DECL_ALIGN(4)
#define ALIGN8_POST DECL_ALIGN(8)
#define ALIGN16_POST DECL_ALIGN(16)
#define ALIGN32_POST DECL_ALIGN(32)
#define ALIGN128_POST DECL_ALIGN(128)
#else
#define ALIGN4 DECL_ALIGN(4)
#define ALIGN8 DECL_ALIGN(8)
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN32 DECL_ALIGN(32)
#define ALIGN128 DECL_ALIGN(128)

#define ALIGN4_POST
#define ALIGN8_POST
#define ALIGN16_POST
#define ALIGN32_POST
#define ALIGN128_POST
#endif

#define FCVAR_NONE				0 
#define FCVAR_UNREGISTERED		(1<<0)
#define FCVAR_DEVELOPMENTONLY	(1<<1)
#define FCVAR_GAMEDLL			(1<<2)
#define FCVAR_CLIENTDLL			(1<<3)
#define FCVAR_HIDDEN			(1<<4)
#define FCVAR_PROTECTED			(1<<5)
#define FCVAR_SPONLY			(1<<6)
#define	FCVAR_ARCHIVE			(1<<7)
#define	FCVAR_NOTIFY			(1<<8)
#define	FCVAR_USERINFO			(1<<9)
#define FCVAR_PRINTABLEONLY		(1<<10)
#define FCVAR_UNLOGGED			(1<<11)
#define FCVAR_NEVER_AS_STRING	(1<<12)
#define FCVAR_REPLICATED		(1<<13)
#define FCVAR_CHEAT				(1<<14)
#define FCVAR_SS				(1<<15)
#define FCVAR_DEMO				(1<<16)
#define FCVAR_DONTRECORD		(1<<17)
#define FCVAR_SS_ADDED			(1<<18)
#define FCVAR_RELEASE			(1<<19)
#define FCVAR_RELOAD_MATERIALS	(1<<20)
#define FCVAR_RELOAD_TEXTURES	(1<<21)
#define FCVAR_NOT_CONNECTED		(1<<22)
#define FCVAR_MATERIAL_SYSTEM_THREAD (1<<23)
#define FCVAR_ARCHIVE_XBOX		(1<<24)
#define FCVAR_SERVER_CAN_EXECUTE	(1<<28)
#define FCVAR_SERVER_CANNOT_QUERY	(1<<29)
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<30)
#define FCVAR_ACCESSIBLE_FROM_THREADS	(1<<25)
#define FCVAR_MATERIAL_THREAD_MASK ( FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD )	
#define SPROP_UNSIGNED			(1<<0)
#define SPROP_COORD				(1<<1)
#define SPROP_NOSCALE			(1<<2)
#define SPROP_ROUNDDOWN			(1<<3)
#define SPROP_ROUNDUP			(1<<4)
#define SPROP_NORMAL			(1<<5)
#define SPROP_EXCLUDE			(1<<6)
#define SPROP_XYZE				(1<<7)
#define SPROP_INSIDEARRAY		(1<<8)
#define SPROP_PROXY_ALWAYS_YES	(1<<9)
#define SPROP_IS_A_VECTOR_ELEM	(1<<10)
#define SPROP_COLLAPSIBLE		(1<<11)
#define SPROP_COORD_MP					(1<<12)
#define SPROP_COORD_MP_LOWPRECISION 	(1<<13)
#define SPROP_COORD_MP_INTEGRAL			(1<<14)
#define SPROP_CELL_COORD				(1<<15)
#define SPROP_CELL_COORD_LOWPRECISION 	(1<<16)
#define SPROP_CELL_COORD_INTEGRAL		(1<<17)
#define SPROP_CHANGES_OFTEN				(1<<18)
#define SPROP_NUMFLAGBITS_NETWORKED		19
#define SPROP_ENCODED_AGAINST_TICKCOUNT	(1<<19)
#define SPROP_NUMFLAGBITS				20
#define SENDPROP_NETWORKVAR_FLAGS_SHIFT 20
#define SENDPROP_OFFSET_MASK			( ( 1 << SENDPROP_NETWORKVAR_FLAGS_SHIFT ) - 1 )

#define INTERFACEVERSION_ISERVERPLUGINCALLBACKS				"ISERVERPLUGINCALLBACKS003"

#define ALIGN_VALUE( val, alignment ) ( ( val + alignment - 1 ) & ~( alignment - 1 ) )
#if defined( GNUC )
#define stackalloc( _size )		alloca( ALIGN_VALUE( _size, 16 ) )
#ifdef _LINUX
#define mallocsize( _p )	( malloc_usable_size( _p ) )
#elif defined(OSX)
#define mallocsize( _p )	( malloc_size( _p ) )
#else
#error
#endif
#elif defined ( _WIN32 )
#define stackalloc( _size )		_alloca( ALIGN_VALUE( _size, 16 ) )
#define mallocsize( _p )		( _msize( _p ) )
#endif

#define  stackfree( _p )			0

#ifdef POSIX
#include <dlfcn.h>
#include <unistd.h>

#define GetProcAddress dlsym

#endif
#define CREATEINTERFACE_PROCNAME	"CreateInterface"
#define EXPOSE_INTERFACE_FN(functionName, interfaceName, versionName) \
	static InterfaceReg __g_Create##interfaceName##_reg(functionName, versionName);
#define EXPOSE_INTERFACE(className, interfaceName, versionName) \
	static void* __Create##className##_interface() {return static_cast<interfaceName *>( new className );} \
	static InterfaceReg __g_Create##className##_reg(__Create##className##_interface, versionName );
#define EXPOSE_SINGLE_INTERFACE_GLOBALVAR(className, interfaceName, versionName, globalVarName) \
	static void* __Create##className##interfaceName##_interface() {return static_cast<interfaceName *>( &globalVarName );} \
	static InterfaceReg __g_Create##className##interfaceName##_reg(__Create##className##interfaceName##_interface, versionName);
#define EXPOSE_SINGLE_INTERFACE(className, interfaceName, versionName) \
	static className __g_##className##_singleton; \
	EXPOSE_SINGLE_INTERFACE_GLOBALVAR(className, interfaceName, versionName, __g_##className##_singleton)

#define DLL_EXPORT				extern "C" __declspec( dllexport )
#define DLL_IMPORT				extern "C" __declspec( dllimport )

#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2

#if defined(__i386__) && !defined(VALVE_LITTLE_ENDIAN)
#define VALVE_LITTLE_ENDIAN 1
#endif

#if defined( _SGI_SOURCE ) || defined( _X360 )
#define	VALVE_BIG_ENDIAN 1
#endif

#if defined( _MSC_VER ) && !defined( PLATFORM_WINDOWS_PC64 )

#define WordSwap  WordSwapAsm
#define DWordSwap DWordSwapAsm

#pragma warning(push)
#pragma warning (disable:4035) 

template <typename T>
inline T WordSwapAsm(T w)
{
	__asm
	{
		mov ax, w
		xchg al, ah
	}
}

template <typename T>
inline T DWordSwapAsm(T dw)
{
	__asm
	{
		mov eax, dw
		bswap eax
	}
}

#pragma warning(pop)

#else

#define WordSwap  WordSwapC
#define DWordSwap DWordSwapC

#endif

template <typename T>
inline T QWordSwapC(T dw)
{
	uint64_t temp;

	temp = *((uint64_t *)&dw) >> 56;
	temp |= ((*((uint64_t *)&dw) & 0x00FF000000000000ull) >> 40);
	temp |= ((*((uint64_t *)&dw) & 0x0000FF0000000000ull) >> 24);
	temp |= ((*((uint64_t *)&dw) & 0x000000FF00000000ull) >> 8);
	temp |= ((*((uint64_t *)&dw) & 0x00000000FF000000ull) << 8);
	temp |= ((*((uint64_t *)&dw) & 0x0000000000FF0000ull) << 24);
	temp |= ((*((uint64_t *)&dw) & 0x000000000000FF00ull) << 40);
	temp |= ((*((uint64_t *)&dw) & 0x00000000000000FFull) << 56);

	return *((T*)&temp);
}

#define QWordSwap QWordSwapC

#define SafeSwapFloat( pOut, pIn )	(*((float*)pOut) = DWordSwap( *((float*)pIn) ))

#if defined(VALVE_LITTLE_ENDIAN)

#define BigShort( val )				WordSwap( val )
#define BigWord( val )				WordSwap( val )
#define BigLong( val )				DWordSwap( val )
#define BigDWord( val )				DWordSwap( val )
#define LittleShort( val )			( val )
#define LittleWord( val )			( val )
#define LittleLong( val )			( val )
#define LittleDWord( val )			( val )
#define LittleQWord( val )			( val )
#define SwapShort( val )			BigShort( val )
#define SwapWord( val )				BigWord( val )
#define SwapLong( val )				BigLong( val )
#define SwapDWord( val )			BigDWord( val )

// Pass floats by pointer for swapping to avoid truncation in the fpu
#define BigFloat( pOut, pIn )		SafeSwapFloat( pOut, pIn )
#define LittleFloat( pOut, pIn )	( *pOut = *pIn )
#define SwapFloat( pOut, pIn )		BigFloat( pOut, pIn )

#elif defined(VALVE_BIG_ENDIAN)

#define BigShort( val )				( val )
#define BigWord( val )				( val )
#define BigLong( val )				( val )
#define BigDWord( val )				( val )
#define LittleShort( val )			WordSwap( val )
#define LittleWord( val )			WordSwap( val )
#define LittleLong( val )			DWordSwap( val )
#define LittleDWord( val )			DWordSwap( val )
#define LittleQWord( val )			QWordSwap( val )
#define SwapShort( val )			LittleShort( val )
#define SwapWord( val )				LittleWord( val )
#define SwapLong( val )				LittleLong( val )
#define SwapDWord( val )			LittleDWord( val )

// Pass floats by pointer for swapping to avoid truncation in the fpu
#define BigFloat( pOut, pIn )		( *pOut = *pIn )
#define LittleFloat( pOut, pIn )	SafeSwapFloat( pOut, pIn )
#define SwapFloat( pOut, pIn )		LittleFloat( pOut, pIn )

#else

// @Note (toml 05-02-02): this technique expects the compiler to
// optimize the expression and eliminate the other path. On any new
// platform/compiler this should be tested.
inline short BigShort( short val )		{ int test = 1; return ( *(char *)&test == 1 ) ? WordSwap( val )  : val; }
inline unsigned short BigWord(unsigned short val )		{ int test = 1; return ( *(char *)&test == 1 ) ? WordSwap( val )  : val; }
inline long BigLong( long val )			{ int test = 1; return ( *(char *)&test == 1 ) ? DWordSwap( val ) : val; }
inline unsigned int BigDWord(unsigned int val )	{ int test = 1; return ( *(char *)&test == 1 ) ? DWordSwap( val ) : val; }
inline short LittleShort( short val )	{ int test = 1; return ( *(char *)&test == 1 ) ? val : WordSwap( val ); }
inline unsigned short LittleWord(unsigned short val )	{ int test = 1; return ( *(char *)&test == 1 ) ? val : WordSwap( val ); }
inline long LittleLong( long val )		{ int test = 1; return ( *(char *)&test == 1 ) ? val : DWordSwap( val ); }
inline unsigned int LittleDWord(unsigned int val )	{ int test = 1; return ( *(char *)&test == 1 ) ? val : DWordSwap( val ); }
inline unsigned long long LittleQWord(unsigned long long val )	{ int test = 1; return ( *(char *)&test == 1 ) ? val : QWordSwap( val ); }
inline short SwapShort( short val )					{ return WordSwap( val ); }
inline unsigned short SwapWord(unsigned short val )				{ return WordSwap( val ); }
inline long SwapLong( long val )					{ return DWordSwap( val ); }
inline unsigned int SwapDWord(unsigned int val )				{ return DWordSwap( val ); }

// Pass floats by pointer for swapping to avoid truncation in the fpu
inline void BigFloat( float *pOut, const float *pIn )		{ int test = 1; ( *(char *)&test == 1 ) ? SafeSwapFloat( pOut, pIn ) : ( *pOut = *pIn ); }
inline void LittleFloat( float *pOut, const float *pIn )	{ int test = 1; ( *(char *)&test == 1 ) ? ( *pOut = *pIn ) : SafeSwapFloat( pOut, pIn ); }
inline void SwapFloat( float *pOut, const float *pIn )		{ SafeSwapFloat( pOut, pIn ); }

#endif

namespace SourceSdk
{
	class IConVar_csgo;
	class IConVar;
	class CCommand;
	typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
	typedef void* (*InstantiateInterfaceFn)();
	typedef void ( *FnChangeCallbackCsgo_t )( IConVar_csgo *var, const char *pOldValue, float flOldValue );
	typedef void(*FnChangeCallback_t)(IConVar *var, const char *pOldValue, float flOldValue);
	typedef void ( *FnCommandCallbackV1_t )( void );
	typedef void ( *FnCommandCallback_t )( const CCommand &command );
	typedef void(*FnCommandCallbackVoid_t)(void);
	#define COMMAND_COMPLETION_MAXITEMS		64
	#define COMMAND_COMPLETION_ITEM_LENGTH	64
	typedef int  ( *FnCommandCompletionCallback )( const char *partial, char commands[ COMMAND_COMPLETION_MAXITEMS ][ COMMAND_COMPLETION_ITEM_LENGTH ] );
	typedef float vec_t;
};

extern bool SteamGameServer_BSecure();

#endif
