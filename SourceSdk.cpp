#include "SdkPreprocessors.h"

#include <cstring>
#include "Misc/temp_basicstring.h"
#include <cmath>
#include <limits>
#include <cstdio>
#include <iostream>
#include <stdarg.h>
#ifdef GNUC
#	include <sys/types.h>
#	include <unistd.h>
#	include <alloca.h>
#else
#	include <Windows.h>
#endif
#include <malloc.h>

#include "Console/convar.h"
#include "Console/iconvar.h"
#include "Console/icvar.h"
#include "Maths/asm.h"
#include "Maths/Vector.h"
#include "Interfaces/interface.h"
#include "Containers/bitbuf.h"
#include "Interfaces/InterfacesProxy.h"

namespace SourceSdk
{
	static characterset_t s_BreakSet;
	static bool s_bBuiltBreakSet = false;
	ConCommandBase_csgo			*ConCommandBase_csgo::s_pConCommandBases = nullptr;
	IConCommandBaseAccessor_csgo	*ConCommandBase_csgo::s_pAccessor = nullptr;
	ConCommandBase			*ConCommandBase::s_pConCommandBases = nullptr;
	IConCommandBaseAccessor	*ConCommandBase::s_pAccessor = nullptr;
	static int s_nCVarFlag = 0;
	static bool s_bRegistered = false;
	InterfaceReg *InterfaceReg::s_pInterfaceRegs = nullptr;
	static bool s_bConnected = false;

	int snprintf(char *pDest, int maxLen, char const *pFormat, ...)
	{
		va_list marker;

		va_start(marker, pFormat);
#ifdef _WIN32
		int len = _vsnprintf(pDest, maxLen, pFormat, marker);
#elif POSIX
		int len = vsnprintf(pDest, maxLen, pFormat, marker);
#endif
		va_end(marker);

		if (len < 0 || len >= maxLen)
		{
			len = maxLen;
			pDest[maxLen - 1] = 0;
		}
		return len;
	}

	Vector::Vector(const VectorAligned& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	bool VectorEqual(Vector const & a, Vector const & b)
	{
		if(a.x != b.x) return false;
		else if(a.y != b.y) return false;
		else if(a.z != b.z) return false;
		else return true;
	}

	bool VectorEqual(Vector const * a, Vector const * b)
	{
		if(a->x != b->x) return false;
		else if(a->y != b->y) return false;
		else if(a->z != b->z) return false;
		else return true;
	}
	
	void VectorClear(Vector & a)
	{
		memset(&a, 0, sizeof(Vector));
	}

	void VectorCopy(Vector const & a, Vector & b)
	{
		memcpy(&b, &a, sizeof(Vector));
	}
	
	void VectorCopy(Vector const * a, Vector * b)
	{
		memcpy(b, a, sizeof(Vector));
	}

	void VectorCopy(VectorAligned const & a, VectorAligned & b)
	{
		memcpy(&b, &a, sizeof(VectorAligned));
	}

	void VectorCopy(VectorAligned const * a, VectorAligned * b)
	{
		memcpy(b, a, sizeof(VectorAligned));
	}

	void VectorCopy(VectorAligned const & a, Vector & b)
	{
		b.x = a.x;
		b.y = a.y;
		b.z = a.z;
	}

	void VectorCopy(VectorAligned const * a, Vector * b)
	{
		b->x = a->x;
		b->y = a->y;
		b->z = a->z;
	}

	void VectorCopy(Vector const & a, VectorAligned & b)
	{
		b.x = a.x;
		b.y = a.y;
		b.z = a.z;
	}

	void VectorCopy(Vector const * a, VectorAligned * b)
	{
		b->x = a->x;
		b->y = a->y;
		b->z = a->z;
	}
	
	bool VectorIsZero(Vector const & a, vec_t tolerance /*= 0.01f*/)
	{
		if(std::fabs(a.x) > tolerance) return false;
		else if(std::fabs(a.y) > tolerance) return false;
		else if(std::fabs(a.z) > tolerance) return false;
		else return true;
	}
	
	bool VectorIsZero(Vector const * a, vec_t tolerance /*= 0.01f*/)
	{
		if(std::fabs(a->x) > tolerance) return false;
		else if(std::fabs(a->y) > tolerance) return false;
		else if(std::fabs(a->z) > tolerance) return false;
		else return true;
	}
	
	vec_t VectorMagnitudeSqr(Vector const & a)
	{
		return std::pow(a.x, 2) + std::pow(a.y, 2) + std::pow(a.z, 2);
	}
	
	vec_t VectorMagnitudeSqr(Vector const * a)
	{
		return std::pow(a->x, 2) + std::pow(a->y, 2) + std::pow(a->z, 2);
	}
	
	vec_t VectorMagnitude(Vector const & a)
	{
		return std::sqrt(VectorMagnitudeSqr(a));
	}
	
	vec_t VectorMagnitude(Vector const * a)
	{
		return std::sqrt(VectorMagnitudeSqr(a));
	}
	
	void VectorAdd(Vector const & a, Vector const & b, Vector & c)
	{
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
	}
	
	void VectorAdd(Vector const & a, Vector & b)
	{
		b.x += a.x;
		b.y += a.y;
		b.z += a.z;
	}
	
	void VectorAdd(Vector const * a, Vector const * b, Vector * c)
	{
		c->x = a->x + b->x;
		c->y = a->y + b->y;
		c->z = a->z + b->z;
	}
	
	void VectorAdd(Vector const * a, Vector * b)
	{
		b->x += a->x;
		b->y += a->y;
		b->z += a->z;
	}
	
	void VectorSub(Vector const & a, Vector const & b, Vector & c)
	{
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
	}
	
	void VectorSub(Vector const & a, Vector & b)
	{
		b.x -= a.x;
		b.y -= a.y;
		b.z -= a.z;
	}
	
	void VectorSub(Vector const * a, Vector const * b, Vector * c)
	{
		c->x = a->x - b->x;
		c->y = a->y - b->y;
		c->z = a->z - b->z;
	}
	
	void VectorSub(Vector const * a, Vector * b)
	{
		b->x -= a->x;
		b->y -= a->y;
		b->z -= a->z;
	}
	
	void VectorMultiply(Vector const & a, Vector const & b, Vector & c)
	{
		c.x = a.x * b.x;
		c.y = a.y * b.y;
		c.z = a.z * b.z;
	}
	
	void VectorMultiply(Vector const & a, Vector & b)
	{
		b.x *= a.x;
		b.y *= a.y;
		b.z *= a.z;
	}
	
	void VectorMultiply(Vector const * a, Vector const * b, Vector * c)
	{
		c->x = a->x * b->x;
		c->y = a->y * b->y;
		c->z = a->z * b->z;
	}
	
	void VectorMultiply(Vector const * a, Vector * b)
	{
		b->x *= a->x;
		b->y *= a->y;
		b->z *= a->z;
	}
	
	void VectorMultiply(Vector const & a, vec_t const b, Vector & c)
	{
		c.x = a.x * b;
		c.y = a.y * b;
		c.z = a.z * b;
	}
	
	void VectorMultiply(Vector & a, vec_t const b)
	{
		a.x *= b;
		a.y *= b;
		a.z *= b;
	}
	
	void VectorMultiply(Vector const * a, vec_t const b, Vector * c)
	{
		c->x = a->x * b;
		c->y = a->y * b;
		c->z = a->z * b;
	}
	
	void VectorMultiply(Vector * a, vec_t const b)
	{
		a->x *= b;
		a->y *= b;
		a->z *= b;
	}

	void VectorDistanceSqr(Vector const & a, Vector const & b, Vector & delta, vec_t & dst)
	{
		VectorCopy(a, delta);
		VectorSub(b, delta);
		dst = VectorMagnitudeSqr(delta);
	}

	void VectorDistanceSqr(Vector const & a, Vector const & b, vec_t & dst)
	{
		Vector delta;
		VectorDistanceSqr(a, b, delta, dst);
	}

	void VectorDistanceSqr(Vector const * a, Vector const * b, Vector * delta, vec_t & dst)
	{
		VectorCopy(a, delta);
		VectorSub(b, delta);
		dst = VectorMagnitudeSqr(delta);
	}

	void VectorDistanceSqr(Vector const * a, Vector const * b, vec_t & dst)
	{
		Vector delta;
		VectorDistanceSqr(a, b, &delta, dst);
	}
	
	void VectorAbs(Vector const & a, Vector & b)
	{
		b.x = std::fabs(a.x);
		b.y = std::fabs(a.y);
		b.z = std::fabs(a.z);
	}
	
	void VectorAbs(Vector & a)
	{
		a.x = std::fabs(a.x);
		a.y = std::fabs(a.y);
		a.z = std::fabs(a.z);
	}
	
	void VectorAbs(Vector const * a, Vector * b)
	{
		b->x = std::fabs(a->x);
		b->y = std::fabs(a->y);
		b->z = std::fabs(a->z);
	}
	
	void VectorAbs(Vector * a)
	{
		a->x = std::fabs(a->x);
		a->y = std::fabs(a->y);
		a->z = std::fabs(a->z);
	}
	
	void VectorNorm(Vector const & a, Vector & b)
	{
		vec_t const mag = 1.0f / (VectorMagnitude(a) + std::numeric_limits<vec_t>::epsilon());
		b.x = a.x * mag;
		b.y = a.y * mag;
		b.z = a.z * mag;
	}
	
	void VectorNorm(Vector & a)
	{
		vec_t const mag = 1.0f / (VectorMagnitude(a) + std::numeric_limits<vec_t>::epsilon());
		a.x *= mag;
		a.y *= mag;
		a.z *= mag;
	}
	
	void VectorNorm(Vector const * a, Vector * b)
	{
		vec_t const mag = 1.0f / (VectorMagnitude(a) + std::numeric_limits<vec_t>::epsilon());
		b->x = a->x * mag;
		b->y = a->y * mag;
		b->z = a->z * mag;
	}
	
	void VectorNorm(Vector * a)
	{
		vec_t const mag = 1.0f / (VectorMagnitude(a) + std::numeric_limits<vec_t>::epsilon());
		a->x *= mag;
		a->y *= mag;
		a->z *= mag;
	}
	
	void VectorDotProduct(Vector const & a, Vector const & b, vec_t & c)
	{
		c = a.x*b.x + a.y*b.y + a.z*b.z;
	}
	
	void VectorDotProduct(Vector const * a, Vector const * b, vec_t & c)
	{
		c = a->x*b->x + a->y*b->y + a->z*b->z;
	}
	
	void AngleVectors(QAngle const & angles, Vector * forward, Vector * right, Vector * up)
	{
		vec_t sr, sp, sy, cr, cp, cy, rt;
		
		SinCos( DEG2RAD( angles.y ), &sy, &cy );
		SinCos( DEG2RAD( angles.x ), &sp, &cp );
		SinCos( DEG2RAD( angles.z ), &sr, &cr );
		
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
		
		rt = (-sr)*sp;
		
		right->x = (rt*cy+(-cr)*-sy);
		right->y = (rt*sy+(-cr)*cy);
		right->z = (-sr)*cp;
		
		rt = cr*sp;
		
		up->x = (rt*cy+(-sr)*-sy);
		up->y = (rt*sy+(-sr)*cy);
		up->z = cr*cp;
	}

	void AngleVectors(QAngle const & angles, Vector * forward, Vector * right)
	{
		vec_t sr, sp, sy, cr, cp, cy, rt;

		SinCos(DEG2RAD(angles.y), &sy, &cy);
		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.z), &sr, &cr);

		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;

		rt = (-sr)*sp;

		right->x = (rt*cy + (-cr)*-sy);
		right->y = (rt*sy + (-cr)*cy);
		right->z = (-sr)*cp;
	}
	
	void AngleVectors(QAngle const & angles, Vector * forward)
	{
		vec_t	sp, sy, cp, cy;
	
		SinCos( DEG2RAD( angles.y ), &sy, &cy );
		SinCos( DEG2RAD( angles.x ), &sp, &cp );
		
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}
	
	void VectorAngles(Vector const & forward, QAngle & angles)
	{
		vec_t tmp;
	
		if (forward.x == 0.0f && forward.y == 0.0f)
		{
			angles.y = 0.0f;
			if (forward.z > 0.0f)
				angles.x = 270.0f;
			else
				angles.x = 90.0f;
		}
		else
		{
			angles.y = (std::atan2(forward.y, forward.x) * 180.0f / M_PI);
			if (angles.y < 0.0f)
				angles.y += 360.0f;

			tmp = std::sqrt(forward.x*forward.x + forward.y*forward.y);
			angles.x = (std::atan2(-forward.z, tmp) * 180.0f / M_PI);
			if (angles.x < 0.0f)
				angles.x += 360.0f;
		}
		
		angles.z = 0.0f;
	}
	
	class CDefaultAccessor_csgo : public IConCommandBaseAccessor_csgo
	{
	public:
		virtual bool RegisterConCommandBase( ConCommandBase_csgo *pVar )
		{
			static_cast<ICvar007_csgo*>(InterfacesProxy::m_cvar)->RegisterConCommand(pVar);
			return true;
		}
	};

	static CDefaultAccessor_csgo s_DefaultAccessorCsgo;

	class CDefaultAccessor : public IConCommandBaseAccessor
	{
	public:
		virtual bool RegisterConCommandBase(ConCommandBase *pVar)
		{
			static_cast<ICvar004*>(InterfacesProxy::m_cvar)->RegisterConCommand(pVar);
			return true;
		}
	};

	static CDefaultAccessor s_DefaultAccessor;

	void CharacterSetBuild(characterset_t *pSetBuffer, const char *pszSetString)
	{
		int i = 0;

		// Test our pointers
		if (!pSetBuffer || !pszSetString)
			return;

		memset(pSetBuffer->set, 0, sizeof(pSetBuffer->set));

		while (pszSetString[i])
		{
			pSetBuffer->set[pszSetString[i]] = 1;
			i++;
		}

	}
	
	void ConVar_Register_csgo( int nCVarFlag, IConCommandBaseAccessor_csgo *pAccessor )
	{
		if ( !InterfacesProxy::m_cvar || s_bRegistered )
			return;

		s_bRegistered = true;
		s_nCVarFlag = nCVarFlag;
		s_nDLLIdentifier = InterfacesProxy::ICvar_AllocateDLLIdentifier();

		ConCommandBase_csgo *pCur, *pNext;

		ConCommandBase_csgo::s_pAccessor = pAccessor ? pAccessor : &s_DefaultAccessorCsgo;
		pCur = ConCommandBase_csgo::s_pConCommandBases;
		while ( pCur )
		{
			pNext = pCur->m_pNext;
			pCur->AddFlags( s_nCVarFlag );
			pCur->Init();
			pCur = pNext;
		}

		//static_cast<ICvar004*>(InterfacesProxy::m_cvar)->ProcessQueuedMaterialThreadConVarSets();
		ConCommandBase_csgo::s_pConCommandBases = NULL;
	}

	void ConVar_Register(int nCVarFlag, IConCommandBaseAccessor *pAccessor)
	{
		if (!InterfacesProxy::m_cvar || s_bRegistered)
			return;

		s_bRegistered = true;
		s_nCVarFlag = nCVarFlag;
		s_nDLLIdentifier = InterfacesProxy::ICvar_AllocateDLLIdentifier();

		ConCommandBase *pCur, *pNext;

		ConCommandBase::s_pAccessor = pAccessor ? pAccessor : &s_DefaultAccessor;
		pCur = ConCommandBase::s_pConCommandBases;
		while (pCur)
		{
			pNext = pCur->m_pNext;
			pCur->AddFlags(s_nCVarFlag);
			pCur->Init();
			pCur = pNext;
		}

		//static_cast<ICvar004*>(InterfacesProxy::m_cvar)->ProcessQueuedMaterialThreadConVarSets();
		ConCommandBase::s_pConCommandBases = NULL;
	}

	void ConVar_Unregister( )
	{
		if ( !InterfacesProxy::m_cvar || !s_bRegistered )
			return;

		InterfacesProxy::ICvar_UnregisterConCommands( s_nDLLIdentifier );
		s_nDLLIdentifier = -1;
		s_bRegistered = false;
	}
	
	ConCommandBase_csgo::ConCommandBase_csgo( void )
	{
		m_bRegistered   = false;
		m_pszName       = NULL;
		m_pszHelpString = NULL;

		m_nFlags = 0;
		m_pNext  = NULL;
	}
	
	ConCommandBase_csgo::ConCommandBase_csgo( const char *pName, const char *pHelpString /*=0*/, int flags /*= 0*/ )
	{
		CreateBase( pName, pHelpString, flags );
	}
	
	ConCommandBase_csgo::~ConCommandBase_csgo( void )
	{
	}
	
	bool ConCommandBase_csgo::IsCommand( void ) const
	{ 
		return true;
	}

	void ConCommandBase_csgo::CreateBase( const char *pName, const char *pHelpString /*= 0*/, int flags /*= 0*/ )
	{
		m_bRegistered = false;
		m_pszName = pName;
		m_pszHelpString = pHelpString ? pHelpString : "";
		m_nFlags = flags;
		if ( !( m_nFlags & FCVAR_UNREGISTERED ) )
		{
			m_pNext = s_pConCommandBases;
			s_pConCommandBases = this;
		}
		else
		{
			m_pNext = NULL;
		}
		if ( s_pAccessor )
		{
			Init();
		}
	}

	void ConCommandBase_csgo::Init()
	{
		if ( s_pAccessor )
		{
			s_pAccessor->RegisterConCommandBase( this );
		}
	}

	void ConCommandBase_csgo::Shutdown()
	{
		if ( InterfacesProxy::m_cvar )
		{
			InterfacesProxy::ICvar_UnregisterConCommand( this );
		}
	}

	const char *ConCommandBase_csgo::GetName( void ) const
	{
		return m_pszName;
	}

	bool ConCommandBase_csgo::IsFlagSet( int flag ) const
	{
		return ( flag & m_nFlags ) ? true : false;
	}

	void ConCommandBase_csgo::AddFlags( int flags )
	{
		m_nFlags |= flags;
	}

	void ConCommandBase_csgo::RemoveFlags(int flags)
	{
		m_nFlags &= ~flags;
	}

	int ConCommandBase_csgo::GetFlags(void) const
	{
		return m_nFlags;
	}

	const ConCommandBase_csgo *ConCommandBase_csgo::GetNext( void ) const
	{
		return m_pNext;
	}

	ConCommandBase_csgo *ConCommandBase_csgo::GetNext( void )
	{
		return m_pNext;
	}

	char *ConCommandBase_csgo::CopyString( const char *from )
	{
		int		len;
		char	*to;
		len = strlen( from );
		if ( len <= 0 )
		{
			to = new char[1];
			to[0] = 0;
		}
		else
		{
			to = new char[len+1];
			strncpy( to, from, len+1 );
		}
		return to;
	}

	const char *ConCommandBase_csgo::GetHelpText( void ) const
	{
		return m_pszHelpString;
	}

	bool ConCommandBase_csgo::IsRegistered( void ) const
	{
		return m_bRegistered;
	}

	ConCommandBase::ConCommandBase(void)
	{
		m_bRegistered = false;
		m_pszName = NULL;
		m_pszHelpString = NULL;

		m_nFlags = 0;
		m_pNext = NULL;
	}

	ConCommandBase::ConCommandBase(const char *pName, const char *pHelpString /*=0*/, int flags /*= 0*/)
	{
		Create(pName, pHelpString, flags);
	}

	ConCommandBase::~ConCommandBase(void)
	{
	}

	bool ConCommandBase::IsCommand(void) const
	{
		return true;
	}

	CVarDLLIdentifier_t ConCommandBase::GetDLLIdentifier() const
	{
		return s_nDLLIdentifier;
	}

	void ConCommandBase::Create(const char *pName, const char *pHelpString /*= 0*/, int flags /*= 0*/)
	{
		static const char *empty_string = "";
		m_bRegistered = false;
		m_pszName = pName;
		m_pszHelpString = pHelpString ? pHelpString : empty_string;
		m_nFlags = flags;
		if (!(m_nFlags & FCVAR_UNREGISTERED))
		{
			m_pNext = s_pConCommandBases;
			s_pConCommandBases = this;
		}
		else
		{
			m_pNext = NULL;
		}
		if (s_pAccessor)
		{
			Init();
		}
	}

	void ConCommandBase::Init()
	{
		if (s_pAccessor)
		{
			s_pAccessor->RegisterConCommandBase(this);
		}
	}

	void ConCommandBase::Shutdown()
	{
		InterfacesProxy::ICvar_UnregisterConCommand(this);
	}

	const char *ConCommandBase::GetName(void) const
	{
		return m_pszName;
	}

	bool ConCommandBase::IsFlagSet(int flag) const
	{
		return (flag & m_nFlags) ? true : false;
	}

	void ConCommandBase::AddFlags(int flags)
	{
		m_nFlags |= flags;
	}

	const ConCommandBase *ConCommandBase::GetNext(void) const
	{
		return m_pNext;
	}

	ConCommandBase *ConCommandBase::GetNext(void)
	{
		return m_pNext;
	}

	char *ConCommandBase::CopyString(const char *from)
	{
		int		len;
		char	*to;
		len = strlen(from);
		if (len <= 0)
		{
			to = new char[1];
			to[0] = 0;
		}
		else
		{
			to = new char[len + 1];
			strncpy(to, from, len + 1);
		}
		return to;
	}

	const char *ConCommandBase::GetHelpText(void) const
	{
		return m_pszHelpString;
	}

	bool ConCommandBase::IsRegistered(void) const
	{
		return m_bRegistered;
	}
	
	CCommand::CCommand()
	{
		if ( !s_bBuiltBreakSet )
		{
			s_bBuiltBreakSet = true;
			CharacterSetBuild( &s_BreakSet, "{}()':" );
		}

		Reset();
	}

	CCommand::CCommand( int nArgC, const char **ppArgV )
	{
		if ( !s_bBuiltBreakSet )
		{
			s_bBuiltBreakSet = true;
			CharacterSetBuild( &s_BreakSet, "{}()':" );
		}
		Reset();
		char *pBuf = m_pArgvBuffer;
		char *pSBuf = m_pArgSBuffer;
		m_nArgc = nArgC;
		for ( int i = 0; i < nArgC; ++i )
		{
			m_ppArgv[i] = pBuf;
			int nLen = strlen( ppArgV[i] );
			memcpy( pBuf, ppArgV[i], nLen+1 );
			if ( i == 0 )
			{
				m_nArgv0Size = nLen;
			}
			pBuf += nLen+1;
			bool bContainsSpace = strchr( ppArgV[i], ' ' ) != NULL;
			if ( bContainsSpace )
			{
				*pSBuf++ = '\"';
			}
			memcpy( pSBuf, ppArgV[i], nLen );
			pSBuf += nLen;
			if ( bContainsSpace )
			{
				*pSBuf++ = '\"';
			}

			if ( i != nArgC - 1 )
			{
				*pSBuf++ = ' ';
			}
		}
	}

	void CCommand::Reset()
	{
		m_nArgc = 0;
		m_nArgv0Size = 0;
		m_pArgSBuffer[0] = 0;
	}

	characterset_t* CCommand::DefaultBreakSet()
	{
		return &s_BreakSet;
	}

	bool CCommand::Tokenize( const char *pCommand, characterset_t *pBreakSet )
	{
		return true;
	}

	const char* CCommand::FindArg( const char *pName ) const
	{
		int nArgC = ArgC();
		for ( int i = 1; i < nArgC; i++ )
		{
			if ( !stricmp( Arg(i), pName ) )
				return (i+1) < nArgC ? Arg( i+1 ) : "";
		}
		return 0;
	}

	int CCommand::FindArgInt( const char *pName, int nDefaultVal ) const
	{
		const char *pVal = FindArg( pName );
		if ( pVal )
			return atoi( pVal );
		else
			return nDefaultVal;
	}

	int DefaultCompletionFunc( const char *partial, char commands[ COMMAND_COMPLETION_MAXITEMS ][ COMMAND_COMPLETION_ITEM_LENGTH ] )
	{
		return 0;
	}
	
	ConCommand_csgo::ConCommand_csgo( const char *pName, FnCommandCallbackVoid_t callback, const char *pHelpString /*= 0*/, int flags /*= 0*/, FnCommandCompletionCallback completionFunc /*= 0*/ )
	{
		m_fnCommandCallbackV1 = callback;
		m_bUsingNewCommandCallback = false;
		m_bUsingCommandCallbackInterface = false;
		m_fnCompletionCallback = completionFunc ? completionFunc : DefaultCompletionFunc;
		m_bHasCompletionCallback = completionFunc != 0 ? true : false;
		BaseClass::CreateBase( pName, pHelpString, flags );
	}

	ConCommand_csgo::ConCommand_csgo( const char *pName, FnCommandCallback_t callback, const char *pHelpString /*= 0*/, int flags /*= 0*/, FnCommandCompletionCallback completionFunc /*= 0*/ )
	{
		m_fnCommandCallback = callback;
		m_bUsingNewCommandCallback = true;
		m_fnCompletionCallback = completionFunc ? completionFunc : DefaultCompletionFunc;
		m_bHasCompletionCallback = completionFunc != 0 ? true : false;
		m_bUsingCommandCallbackInterface = false;
		BaseClass::CreateBase( pName, pHelpString, flags );
	}

	ConCommand_csgo::ConCommand_csgo( const char *pName, ICommandCallback *pCallback, const char *pHelpString /*= 0*/, int flags /*= 0*/, ICommandCompletionCallback *pCompletionCallback /*= 0*/ )
	{
		m_pCommandCallback = pCallback;
		m_bUsingNewCommandCallback = false;
		m_pCommandCompletionCallback = pCompletionCallback;
		m_bHasCompletionCallback = ( pCompletionCallback != 0 );
		m_bUsingCommandCallbackInterface = true;
		BaseClass::CreateBase( pName, pHelpString, flags );
	}

	ConCommand_csgo::~ConCommand_csgo( void )
	{
	}

	bool ConCommand_csgo::IsCommand( void ) const
	{ 
		return true;
	}

	void ConCommand_csgo::Dispatch( const CCommand &command )
	{
		if ( m_bUsingNewCommandCallback )
		{
			if ( m_fnCommandCallback )
			{
				( *m_fnCommandCallback )( command );
				return;
			}
		}
		else if ( m_bUsingCommandCallbackInterface )
		{
			if ( m_pCommandCallback )
			{
				m_pCommandCallback->CommandCallback( command );
				return;
			}
		}
		else
		{
			if ( m_fnCommandCallbackV1 )
			{
				( *m_fnCommandCallbackV1 )();
				return;
			}
		}
	}

	int	ConCommand_csgo::AutoCompleteSuggest( const char *partial, CUtlVector< CUtlString > &commands )
	{
		/*if ( m_bUsingCommandCallbackInterface )
		{
			if ( !m_pCommandCompletionCallback )
				return 0;
			return m_pCommandCompletionCallback->CommandCompletionCallback( partial, commands );
		}
		if ( !m_fnCompletionCallback )
			return 0;
		char rgpchCommands[ COMMAND_COMPLETION_MAXITEMS ][ COMMAND_COMPLETION_ITEM_LENGTH ];
		int iret = ( m_fnCompletionCallback )( partial, rgpchCommands );
		for ( int i = 0 ; i < iret; ++i )
		{
			CUtlString str = rgpchCommands[ i ];
			commands.AddToTail( str );
		}
		return iret;*/
		return 0;
	}

	bool ConCommand_csgo::CanAutoComplete( void )
	{
		return false;
	}

	ConCommand::ConCommand(const char *pName, FnCommandCallbackV1_t callback, const char *pHelpString /*= 0*/, int flags /*= 0*/, FnCommandCompletionCallback completionFunc /*= 0*/)
	{
		m_fnCommandCallbackV1 = callback;
		m_bUsingNewCommandCallback = false;
		m_bUsingCommandCallbackInterface = false;
		m_fnCompletionCallback = completionFunc ? completionFunc : DefaultCompletionFunc;
		m_bHasCompletionCallback = completionFunc != 0 ? true : false;
		BaseClass::Create(pName, pHelpString, flags);
	}

	ConCommand::ConCommand(const char *pName, FnCommandCallback_t callback, const char *pHelpString /*= 0*/, int flags /*= 0*/, FnCommandCompletionCallback completionFunc /*= 0*/)
	{
		m_fnCommandCallback = callback;
		m_bUsingNewCommandCallback = true;
		m_fnCompletionCallback = completionFunc ? completionFunc : DefaultCompletionFunc;
		m_bHasCompletionCallback = completionFunc != 0 ? true : false;
		m_bUsingCommandCallbackInterface = false;
		BaseClass::Create(pName, pHelpString, flags);
	}

	ConCommand::ConCommand(const char *pName, ICommandCallback *pCallback, const char *pHelpString /*= 0*/, int flags /*= 0*/, ICommandCompletionCallback *pCompletionCallback /*= 0*/)
	{
		m_pCommandCallback = pCallback;
		m_bUsingNewCommandCallback = false;
		m_pCommandCompletionCallback = pCompletionCallback;
		m_bHasCompletionCallback = (pCompletionCallback != 0);
		m_bUsingCommandCallbackInterface = true;
		BaseClass::Create(pName, pHelpString, flags);
	}

	ConCommand::~ConCommand(void)
	{
	}

	bool ConCommand::IsCommand(void) const
	{
		return true;
	}

	void ConCommand::Dispatch(const CCommand &command)
	{
		if (m_bUsingNewCommandCallback)
		{
			if (m_fnCommandCallback)
			{
				(*m_fnCommandCallback)(command);
				return;
			}
		}
		else if (m_bUsingCommandCallbackInterface)
		{
			if (m_pCommandCallback)
			{
				m_pCommandCallback->CommandCallback(command);
				return;
			}
		}
		else
		{
			if (m_fnCommandCallbackV1)
			{
				(*m_fnCommandCallbackV1)();
				return;
			}
		}
	}

	int	ConCommand::AutoCompleteSuggest(const char *partial, CUtlVector< CUtlString > &commands)
	{
		return 0;
	}

	bool ConCommand::CanAutoComplete(void)
	{
		return false;
	}



	ConVar_csgo::ConVar_csgo( const char *pName, const char *pDefaultValue, int flags /* = 0 */ )
	{
		Create( pName, pDefaultValue, flags );
	}

	ConVar_csgo::ConVar_csgo( const char *pName, const char *pDefaultValue, int flags, const char *pHelpString )
	{
		Create( pName, pDefaultValue, flags, pHelpString );
	}

	ConVar_csgo::ConVar_csgo( const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax )
	{
		Create( pName, pDefaultValue, flags, pHelpString, bMin, fMin, bMax, fMax );
	}

	ConVar_csgo::ConVar_csgo( const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, FnChangeCallback_t callback )
	{
		Create( pName, pDefaultValue, flags, pHelpString, false, 0.0, false, 0.0, callback );
	}

	ConVar_csgo::ConVar_csgo( const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t callback )
	{
		Create( pName, pDefaultValue, flags, pHelpString, bMin, fMin, bMax, fMax, callback );
	}

	ConVar_csgo::~ConVar_csgo( void )
	{
		if (m_Value.m_pszString)
		{
			delete[] m_Value.m_pszString;
			m_Value.m_pszString = NULL;
		}
	}

	void ConVar_csgo::InstallChangeCallback( FnChangeCallback_t callback, bool b )
	{
		/*m_pParent->m_fnChangeCallback = callback;

		if ( m_pParent->m_fnChangeCallback )
		{
			m_pParent->m_fnChangeCallback( this, m_pszString, m_fValue );
		}*/
	}

	bool ConVar_csgo::IsFlagSet( int flag ) const
	{
		return ( flag & m_pParent->m_nFlags ) ? true : false;
	}

	const char *ConVar_csgo::GetHelpText( void ) const
	{
		return m_pParent->m_pszHelpString;
	}

	void ConVar_csgo::AddFlags( int flags )
	{
		m_pParent->m_nFlags |= flags;
	}

	bool ConVar_csgo::IsRegistered( void ) const
	{
		return m_pParent->m_bRegistered;
	}

	const char *ConVar_csgo::GetName( void ) const
	{
		return m_pParent->m_pszName;
	}

	bool ConVar_csgo::IsCommand( void ) const
	{ 
		return false;
	}

	const char *ConVar_csgo::GetBaseName(void) const
	{
		return m_pParent->m_pszName;
	}

	int ConVar_csgo::GetSplitScreenPlayerSlot(void) const
	{
		return 0;
	}

	int ConVar_csgo::GetFlags(void) const
	{
		return m_pParent->m_nFlags;
	}

	void ConVar_csgo::InternalSetColorValue(Color cValue)
	{
	}

	void ConVar_csgo::SetValue(Color value)
	{
		ConVar_csgo *var = (ConVar_csgo *)m_pParent;
		var->InternalSetColorValue(value);
	}


	void ConVar_csgo::Init()
	{
		BaseClass::Init();
	}

	void ConVar_csgo::InternalSetValue( const char *value )
	{
		float fNewValue;
		char  tempVal[ 32 ];
		char  *val;
		float flOldValue = m_Value.m_fValue;
		val = (char *)value;
		if ( !value )
			fNewValue = 0.0f;
		else
			fNewValue = ( float )atof( value );

		if ( ClampValue( fNewValue ) )
		{
			snprintf( tempVal,sizeof(tempVal), "%f", fNewValue );
			val = tempVal;
		}
		m_Value.m_fValue		= fNewValue;
		m_Value.m_nValue		= ( int )(m_Value.m_fValue );
		if ( !( m_nFlags & FCVAR_NEVER_AS_STRING ) )
		{
			ChangeStringValue( val, flOldValue );
		}
	}

	void ConVar_csgo::ChangeStringValue( const char *tempVal, float flOldValue )
	{
		char* pszOldValue = (char*)stackalloc(m_Value.m_StringLength );
		memcpy( pszOldValue, m_Value.m_pszString, m_Value.m_StringLength );
		if ( tempVal )
		{
			int len = strlen(tempVal) + 1;

			if ( len > m_Value.m_StringLength)
			{
				if (m_Value.m_pszString)
				{
					delete[]m_Value. m_pszString;
				}

				m_Value.m_pszString	= new char[len];
				m_Value.m_StringLength = len;
			}

			memcpy(m_Value.m_pszString, tempVal, len );
		}
		else 
		{
			*m_Value.m_pszString = 0;
		}

		/*if ( m_Value.m_fnChangeCallback )
		{
			m_fnChangeCallback( this, pszOldValue, flOldValue );
		}*/

		//g_pCVar->CallGlobalChangeCallbacks( this, pszOldValue, flOldValue );

		stackfree( pszOldValue );
	}

	bool ConVar_csgo::ClampValue( float& value )
	{
		if ( m_bHasMin && ( value < m_fMinVal ) )
		{
			value = m_fMinVal;
			return true;
		}
		
		if ( m_bHasMax && ( value > m_fMaxVal ) )
		{
			value = m_fMaxVal;
			return true;
		}

		return false;
	}

	void ConVar_csgo::InternalSetFloatValue( float fNewValue )
	{
		if ( fNewValue == m_Value.m_fValue )
			return;

		ClampValue( fNewValue );
		float flOldValue = m_Value.m_fValue;
		m_Value.m_fValue		= fNewValue;
		m_Value.m_nValue		= ( int )m_Value.m_fValue;
		if ( !( m_nFlags & FCVAR_NEVER_AS_STRING ) )
		{
			char tempVal[ 32 ];
			snprintf( tempVal, sizeof( tempVal), "%f", m_Value.m_fValue );
			ChangeStringValue( tempVal, flOldValue );
		}
	}

	void ConVar_csgo::InternalSetIntValue( int nValue )
	{
		if ( nValue == m_Value.m_nValue )
			return;
		float fValue = (float)nValue;
		if ( ClampValue( fValue ) )
		{
			nValue = ( int )( fValue );
		}
		float flOldValue = m_Value.m_fValue;
		m_Value.m_fValue		= fValue;
		m_Value.m_nValue		= nValue;
		if ( !( m_nFlags & FCVAR_NEVER_AS_STRING ) )
		{
			char tempVal[ 32 ];
			snprintf( tempVal, sizeof( tempVal ), "%d", m_Value.m_nValue );
			ChangeStringValue( tempVal, flOldValue );
		}
	}

	void ConVar_csgo::Create( const char *pName, const char *pDefaultValue, int flags /*= 0*/, const char *pHelpString /*= NULL*/, bool bMin /*= false*/, float fMin /*= 0.0*/, bool bMax /*= false*/, float fMax /*= false*/, FnChangeCallback_t callback /*= NULL*/ )
	{
		static const char * empty_string = "";
		m_pParent = this;
		m_pszDefaultValue = pDefaultValue;
		if (!m_pszDefaultValue || !*m_pszDefaultValue) m_pszDefaultValue = empty_string;
		m_Value.m_StringLength = strlen( m_pszDefaultValue ) + 1;
		m_Value.m_pszString = new char[m_Value.m_StringLength];
		memcpy(m_Value.m_pszString, m_pszDefaultValue, m_Value.m_StringLength );
		m_bHasMin = bMin;
		m_fMinVal = fMin;
		m_bHasMax = bMax;
		m_fMaxVal = fMax;
		//m_fnChangeCallback = callback;
		m_Value.m_fValue = ( float )atof(m_Value.m_pszString );
		m_Value.m_nValue = atoi(m_Value.m_pszString );
		BaseClass::CreateBase( pName, pHelpString, flags );
	}

	void ConVar_csgo::SetValue(const char *value)
	{
		ConVar_csgo *var = ( ConVar_csgo * )m_pParent;
		var->InternalSetValue( value );
	}

	void ConVar_csgo::SetValue( float value )
	{
		ConVar_csgo *var = ( ConVar_csgo * )m_pParent;
		var->InternalSetFloatValue( value );
	}

	void ConVar_csgo::SetValue( int value )
	{
		ConVar_csgo *var = ( ConVar_csgo * )m_pParent;
		var->InternalSetIntValue( value );
	}

	void ConVar_csgo::Revert( void )
	{
		ConVar_csgo *var = ( ConVar_csgo * )m_pParent;
		var->SetValue( var->m_pszDefaultValue );
	}

	bool ConVar_csgo::GetMin( float& minVal ) const
	{
		minVal = m_pParent->m_fMinVal;
		return m_pParent->m_bHasMin;
	}

	bool ConVar_csgo::GetMax( float& maxVal ) const
	{
		maxVal = m_pParent->m_fMaxVal;
		return m_pParent->m_bHasMax;
	}

	const char *ConVar_csgo::GetDefault( void ) const
	{
		return m_pParent->m_pszDefaultValue;
	}

	ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags /* = 0 */)
	{
		Create(pName, pDefaultValue, flags);
	}

	ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString)
	{
		Create(pName, pDefaultValue, flags, pHelpString);
	}

	ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax)
	{
		Create(pName, pDefaultValue, flags, pHelpString, bMin, fMin, bMax, fMax);
	}

	ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, FnChangeCallback_t callback)
	{
		Create(pName, pDefaultValue, flags, pHelpString, false, 0.0, false, 0.0, callback);
	}

	ConVar::ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t callback)
	{
		Create(pName, pDefaultValue, flags, pHelpString, bMin, fMin, bMax, fMax, callback);
	}

	ConVar::~ConVar(void)
	{
		if (m_pszString)
		{
			delete[] m_pszString;
			m_pszString = NULL;
		}
	}

	void ConVar::InstallChangeCallback(FnChangeCallback_t callback)
	{
		m_pParent->m_fnChangeCallback = callback;
		if (m_pParent->m_fnChangeCallback)
		{
			m_pParent->m_fnChangeCallback(this, m_pszString, m_fValue);
		}
	}

	bool ConVar::IsFlagSet(int flag) const
	{
		return (flag & m_pParent->m_nFlags) ? true : false;
	}

	const char *ConVar::GetHelpText(void) const
	{
		return m_pParent->m_pszHelpString;
	}

	void ConVar::AddFlags(int flags)
	{
		m_pParent->m_nFlags |= flags;
	}

	bool ConVar::IsRegistered(void) const
	{
		return m_pParent->m_bRegistered;
	}

	const char *ConVar::GetName(void) const
	{
		return m_pParent->m_pszName;
	}

	bool ConVar::IsCommand(void) const
	{
		return false;
	}

	void ConVar::Init()
	{
		BaseClass::Init();
	}

	void ConVar::InternalSetValue(const char *value)
	{
		float fNewValue;
		char  tempVal[32];
		char  *val;
		float flOldValue = m_fValue;
		val = (char *)value;
		fNewValue = (float)atof(value);
		if (ClampValue(fNewValue))
		{
			snprintf(tempVal, sizeof(tempVal), "%f", fNewValue);
			val = tempVal;
		}
		m_fValue = fNewValue;
		m_nValue = (int)(m_fValue);
		if (!(m_nFlags & FCVAR_NEVER_AS_STRING))
		{
			ChangeStringValue(val, flOldValue);
		}
	}

	void ConVar::ChangeStringValue(const char *tempVal, float flOldValue)
	{
		char* pszOldValue = (char*)stackalloc(m_StringLength);
		memcpy(pszOldValue, m_pszString, m_StringLength);
		int len = strlen(tempVal) + 1;
		if (len > m_StringLength)
		{
			if (m_pszString)
			{
				delete[] m_pszString;
			}
			m_pszString = new char[len];
			m_StringLength = len;
		}
		memcpy(m_pszString, tempVal, len);
		if (m_fnChangeCallback)
		{
			m_fnChangeCallback(this, pszOldValue, flOldValue);
		}
		//g_pCVar->CallGlobalChangeCallbacks(this, pszOldValue, flOldValue);
		stackfree(pszOldValue);
	}

	bool ConVar::ClampValue(float& value)
	{
		if (m_bHasMin && (value < m_fMinVal))
		{
			value = m_fMinVal;
			return true;
		}
		if (m_bHasMax && (value > m_fMaxVal))
		{
			value = m_fMaxVal;
			return true;
		}
		return false;
	}

	void ConVar::InternalSetFloatValue(float fNewValue)
	{
		if (fNewValue == m_fValue)
			return;
		ClampValue(fNewValue);
		float flOldValue = m_fValue;
		m_fValue = fNewValue;
		m_nValue = (int)m_fValue;
		if (!(m_nFlags & FCVAR_NEVER_AS_STRING))
		{
			char tempVal[32];
			snprintf(tempVal, sizeof(tempVal), "%f", m_fValue);
			ChangeStringValue(tempVal, flOldValue);
		}
	}

	void ConVar::InternalSetIntValue(int nValue)
	{
		if (nValue == m_nValue)
			return;
		float fValue = (float)nValue;
		if (ClampValue(fValue))
		{
			nValue = (int)(fValue);
		}
		float flOldValue = m_fValue;
		m_fValue = fValue;
		m_nValue = nValue;
		if (!(m_nFlags & FCVAR_NEVER_AS_STRING))
		{
			char tempVal[32];
			snprintf(tempVal, sizeof(tempVal), "%d", m_nValue);
			ChangeStringValue(tempVal, flOldValue);
		}
	}

	void ConVar::Create(const char *pName, const char *pDefaultValue, int flags /*= 0*/,
		const char *pHelpString /*= NULL*/, bool bMin /*= false*/, float fMin /*= 0.0*/,
		bool bMax /*= false*/, float fMax /*= false*/, FnChangeCallback_t callback /*= NULL*/)
	{
		static const char *empty_string = "";
		m_pParent = this;
		m_pszDefaultValue = pDefaultValue ? pDefaultValue : empty_string;
		m_StringLength = strlen(m_pszDefaultValue) + 1;
		m_pszString = new char[m_StringLength];
		memcpy(m_pszString, m_pszDefaultValue, m_StringLength);
		m_bHasMin = bMin;
		m_fMinVal = fMin;
		m_bHasMax = bMax;
		m_fMaxVal = fMax;
		m_fnChangeCallback = callback;
		m_fValue = (float)atof(m_pszString);
		m_nValue = (int)m_fValue;
		BaseClass::Create(pName, pHelpString, flags);
	}

	void ConVar::SetValue(const char *value)
	{
		ConVar *var = (ConVar *)m_pParent;
		var->InternalSetValue(value);
	}

	void ConVar::SetValue(float value)
	{
		ConVar *var = (ConVar *)m_pParent;
		var->InternalSetFloatValue(value);
	}

	void ConVar::SetValue(int value)
	{
		ConVar *var = (ConVar *)m_pParent;
		var->InternalSetIntValue(value);
	}

	void ConVar::Revert(void)
	{
		ConVar *var = (ConVar *)m_pParent;
		var->SetValue(var->m_pszDefaultValue);
	}

	bool ConVar::GetMin(float& minVal) const
	{
		minVal = m_pParent->m_fMinVal;
		return m_pParent->m_bHasMin;
	}

	bool ConVar::GetMax(float& maxVal) const
	{
		maxVal = m_pParent->m_fMaxVal;
		return m_pParent->m_bHasMax;
	}

	const char *ConVar::GetDefault(void) const
	{
		return m_pParent->m_pszDefaultValue;
	}

	InterfaceReg::InterfaceReg( InstantiateInterfaceFn fn, const char *pName ) :
	m_pName(pName)
	{
		m_CreateFn = fn;
		m_pNext = s_pInterfaceRegs;
		s_pInterfaceRegs = this;
	}
	
	/*
	
	void* CreateInterfaceInternal( const char *pName, int *pReturnCode )
	{
		InterfaceReg *pCur;
		
		for (pCur=InterfaceReg::s_pInterfaceRegs; pCur; pCur=pCur->m_pNext)
		{
			if (strcmp(pCur->m_pName, pName) == 0)
			{
				if (pReturnCode)
				{
					*pReturnCode = IFACE_OK;
				}
				return pCur->m_CreateFn();
			}
		}
		
		if (pReturnCode)
		{
			*pReturnCode = IFACE_FAILED;
		}
		return NULL;	
	}

	void* CreateInterface( const char *pName, int *pReturnCode )
	{
		return CreateInterfaceInternal( pName, pReturnCode );
	}

	*/
	
	int BfGetNumBitsLeft(bf_write const * buffer)
	{
		return buffer->m_nDataBits - buffer->m_iCurBit;
	}

	class CBitWriteMasksInit
	{
	public:
		static unsigned long g_LittleBits[32];

		CBitWriteMasksInit()
		{
			for (unsigned int littleBit = 0; littleBit < 32; littleBit++)
				(&g_LittleBits[littleBit])[0] = LittleDWord(1u << littleBit);
		}
	};

	static CBitWriteMasksInit g_BitWriteMasksInit;

	unsigned long CBitWriteMasksInit::g_LittleBits[32];

	inline void BfWriteBit(bf_write * buffer, int value)
	{
#if __i386__
		if (value)
			buffer->m_pData[buffer->m_iCurBit >> 5] |= 1u << (buffer->m_iCurBit & 31);
		else
			buffer->m_pData[buffer->m_iCurBit >> 5] &= ~(1u << (buffer->m_iCurBit & 31));
#else
		if (value)
			buffer->m_pData[buffer->m_iCurBit >> 5] |= CBitWriteMasksInit::g_LittleBits[buffer->m_iCurBit & 31];
		else
			buffer->m_pData[buffer->m_iCurBit >> 5] &= ~CBitWriteMasksInit::g_LittleBits[buffer->m_iCurBit & 31];
#endif

		++buffer->m_iCurBit;
	}

	void BfWriteSBitLong(bf_write * buffer, long const data, size_t const numBits)
	{
		for (size_t i = 0; i < numBits; i++)
		{
			BfWriteBit(buffer, !!(data & (1 << i)));
		}
	}

	/*template <typename type>
	void BfWriteNBits(bf_write * buffer, type const data, size_t const numBits)
	{
		static_assert(numBits <= sizeof(type) * 4, "Bits overflow");

		for (size_t i = 0; i < numBits; i++)
		{
			BfWriteBit(buffer, !!(data & (1 << i)));
		}
	}*/
	
	void BfWriteByte(bf_write * buffer, int val)
	{
		int const numbits = sizeof(unsigned char) << 3;
		int const iCurBitMasked = buffer->m_iCurBit & 31;
		int const iuint32_t = buffer->m_iCurBit >> 5;
		buffer->m_iCurBit += numbits;
		unsigned long * pOut = &buffer->m_pData[iuint32_t];
		val = (val << iCurBitMasked) | (val >> (32 - iCurBitMasked));
		unsigned int const temp = 1 << (numbits-1);
		unsigned int const mask1 = (temp*2-1) << iCurBitMasked;
		unsigned int const mask2 = (temp-1) >> (31 - iCurBitMasked);
		int const i = mask2 & 1;
		unsigned long DWord1 = LittleDWord(pOut[0]);
		unsigned long DWord2 = LittleDWord(pOut[i]);
		DWord1 ^= (mask1 & (val ^ DWord1));
		DWord2 ^= (mask2 & (val ^ DWord2));
		pOut[i] = LittleDWord(DWord2);
		pOut[0] = LittleDWord(DWord1);
	}
	
	void BfWriteShort(bf_write * buffer, int val)
	{
		int const numbits = sizeof(short) << 3;
		int const nPreserveBits = ( 0x7FFFFFFF >> ( 32 - numbits ) );
		int const nSignExtension = ( val >> 31 ) & ~nPreserveBits;
		val &= nPreserveBits;
		val |= nSignExtension;
		int const iCurBitMasked = buffer->m_iCurBit & 31;
		int const iuint32_t = buffer->m_iCurBit >> 5;
		buffer->m_iCurBit += numbits;
		unsigned long * pOut = &buffer->m_pData[iuint32_t];
		val = (val << iCurBitMasked) | (val >> (32 - iCurBitMasked));
		unsigned int const temp = 1 << (numbits-1);
		unsigned int const mask1 = (temp*2-1) << iCurBitMasked;
		unsigned int const mask2 = (temp-1) >> (31 - iCurBitMasked);
		int const i = mask2 & 1;
		unsigned long DWord1 = LittleDWord(pOut[0]);
		unsigned long DWord2 = LittleDWord(pOut[i]);
		DWord1 ^= (mask1 & (val ^ DWord1));
		DWord2 ^= (mask2 & (val ^ DWord2));
		pOut[i] = LittleDWord(DWord2);
		pOut[0] = LittleDWord(DWord1);
	}
	
	void BfWriteChar(bf_write * buffer, int val)
	{
		int const numbits = sizeof(char) << 3;
		int const nPreserveBits = ( 0x7FFFFFFF >> ( 32 - numbits ) );
		int const nSignExtension = ( val >> 31 ) & ~nPreserveBits;
		val &= nPreserveBits;
		val |= nSignExtension;
		int const iCurBitMasked = buffer->m_iCurBit & 31;
		int const iuint32_t = buffer->m_iCurBit >> 5;
		buffer->m_iCurBit += numbits;
		unsigned long * pOut = &buffer->m_pData[iuint32_t];
		val = (val << iCurBitMasked) | (val >> (32 - iCurBitMasked));
		unsigned int const temp = 1 << (numbits-1);
		unsigned int const mask1 = (temp*2-1) << iCurBitMasked;
		unsigned int const mask2 = (temp-1) >> (31 - iCurBitMasked);
		int const i = mask2 & 1;
		unsigned long DWord1 = LittleDWord( pOut[0] );
		unsigned long DWord2 = LittleDWord( pOut[i] );
		DWord1 ^= ( mask1 & ( val ^ DWord1) );
		DWord2 ^= ( mask2 & ( val ^ DWord2) );
		pOut[i] = LittleDWord(DWord2);
		pOut[0] = LittleDWord(DWord1);
	}
	
	void BfWriteString(bf_write * buffer, const char* val)
	{
		do
		{
			BfWriteChar( buffer, *val );
		} while( *++val != 0 );
	}

	void GetCommandLineString(basic_string & cmd)
	{
#ifdef GNUC
		char buf[1024];
		pid_t proc_id = getpid();
		sprintf(buf, "/proc/%i/cmdline", proc_id);
		FILE * pFile;
		pFile = fopen(buf, "r");
		size_t pos = 0;
		while (!feof(pFile) && pos < 1023)
		{
			int v = fgetc(pFile);
			buf[pos] = (v == '\0' || v == '\n') ? ' ' : (char)(v);
			++pos;
		}
		buf[pos] = '\0';
		fclose(pFile);
		cmd = basic_string(buf);
#else // WIN32
		cmd = basic_string(GetCommandLineA());
#endif
	}

	void GetGameDir(basic_string & dir)
	{
		dir.clear();
		basic_string cmd;
		GetCommandLineString(cmd);
		size_t dir_start = cmd.find("-game");
		if (dir_start == basic_string::npos) return;
		dir_start += 5;
		while (cmd[dir_start] == ' ') ++dir_start;
		while (cmd[dir_start] != ' ') dir.append(cmd[dir_start++]);
	}

	void * InterfacesProxy::LoadInterface(CreateInterfaceFn factory, const char * name_no_version, int & loaded_version)
	{
		int return_code;
		void* iface;
		loaded_version = 50;
		char s_v[64];
		do
		{
			if (--loaded_version == 0)
			{
				iface = nullptr;
				break;
			}
			sprintf(s_v, "%s%03d", name_no_version, loaded_version);
			iface = (void*)factory(s_v, &return_code);
		} while (iface == nullptr || return_code == IFACE_FAILED);
		return iface;
	}

	std::function<bool(Vector const &, Vector const &, unsigned int, ITraceFilter*)> trace_ray_fn;
	std::function<bool(Vector const &, Vector const &, Vector const &, unsigned int, ITraceFilter*)> trace_hull_fn;

	void SetupTraceFunctions()
	{
		if (InterfacesProxy::m_game == CounterStrikeGlobalOffensive)
		{
			trace_ray_fn = TraceRayCSGO;
			trace_hull_fn = TraceHullCSGO;
		}
		else
		{
			trace_ray_fn = TraceRay;
			trace_hull_fn = TraceHull;
		}
	}

	bool TraceRayCSGO(Vector const & start, Vector const & end, unsigned int mask, ITraceFilter* itracefilter)
	{
		static CGameTrace_csgo trace;
		static Ray_t_csgo ray;
		ray.Init(start, end);
		InterfacesProxy::Call_TraceRay((void*)&ray, mask, itracefilter, (void*)&trace);
		return trace.fraction == 1.0;
	}

	bool TraceRay(Vector const & start, Vector const & end, unsigned int mask, ITraceFilter* itracefilter)
	{
		static CGameTrace trace;
		static Ray_t ray;
		ray.Init(start, end);
		InterfacesProxy::Call_TraceRay((void*)&ray, mask, itracefilter, (void*)&trace);
		return trace.fraction == 1.0;
	}

	bool TraceHullCSGO(Vector const & dot, Vector const & mins, Vector const & maxs, unsigned int mask, ITraceFilter* itracefilter)
	{
		static CGameTrace_csgo trace;
		static Ray_t_csgo ray;
		ray.Init(dot, dot, mins, maxs);
		InterfacesProxy::Call_TraceRay((void*)&ray, mask, itracefilter, (void*)&trace);
		return trace.DidHit();
	}

	bool TraceHull(Vector const & dot, Vector const & mins, Vector const & maxs, unsigned int mask, ITraceFilter* itracefilter)
	{
		static CGameTrace_csgo trace;
		static Ray_t_csgo ray;
		ray.Init(dot, dot, mins, maxs);
		InterfacesProxy::Call_TraceRay((void*)&ray, mask, itracefilter, (void*)&trace);
		return trace.DidHit();
	}

	bool InterfacesProxy::Load(CreateInterfaceFn game_factory, CreateInterfaceFn interface_factory)
	{
		basic_string game_dir;
		GetGameDir(game_dir); // Try to see if this works when the server is launched using GUI
		if (stricmp(game_dir.c_str(), "csgo") == 0)
		{
			m_game = SourceSdk::CounterStrikeGlobalOffensive;
			std::cout << "Detected game CSGO" << std::endl;
		}
		else if (stricmp(game_dir.c_str(), "cstrike") == 0)
		{
			m_game = CounterStrikeSource;
			std::cout << "Detected game CSS" << std::endl;
		}
		// add more here
		else
		{
			// Could not determine, try to get appid in steam.inf
			std::cout << "Undetected game ..." << std::endl;
		}

		m_servergamedll = LoadInterface(game_factory, "ServerGameDLL", m_servergamedll_version);
		if (m_servergamedll == nullptr) return false;
		switch (m_servergamedll_version)
		{
		case 5:
		case 6:
			INIT_VIRTUAL_FUNCTION(m_servergamedll, 9, GetTickInterval);
			INIT_VIRTUAL_FUNCTION(m_servergamedll, 10, GetAllServerClasses);
			break;
		case 9:
		case 10:
			INIT_VIRTUAL_FUNCTION(m_servergamedll, 10, GetTickInterval);
			INIT_VIRTUAL_FUNCTION(m_servergamedll, 11, GetAllServerClasses);
			break;
		default:
			std::cout << "FATAL : Unhandled IServerGameDLL version " << m_servergamedll_version << "\n";
			return false;
		};

		m_playerinfomanager = LoadInterface(game_factory, "PlayerInfoManager", m_playerinfomanager_version);
		if (m_playerinfomanager == nullptr) return false;
		switch (m_playerinfomanager_version)
		{
		case 2:
			INIT_VIRTUAL_FUNCTION(m_playerinfomanager, 0, GetPlayerInfo);
			INIT_VIRTUAL_FUNCTION(m_playerinfomanager, 1, GetGlobalVars);
			break;
		default:
			std::cout << "FATAL : Unhandled PlayerInfoManager version " << m_playerinfomanager_version << "\n";
			return false;
		};

		m_servergameents = LoadInterface(game_factory, "ServerGameEnts", m_servergameents_version);
		VT_TRAP
		if (m_servergameents == nullptr) return false;
		switch (m_servergameents_version)
		{
		case 1:
#ifdef WIN32
			if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
			{
				INIT_VIRTUAL_FUNCTION(m_servergameents, 3, BaseEntityToEdict);
				INIT_VIRTUAL_FUNCTION(m_servergameents, 4, EdictToBaseEntity);
			}
			else
			{
				INIT_VIRTUAL_FUNCTION(m_servergameents, 4, BaseEntityToEdict);
				INIT_VIRTUAL_FUNCTION(m_servergameents, 5, EdictToBaseEntity);
			}
#else
			if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
			{
				INIT_VIRTUAL_FUNCTION(m_servergameents, 4, BaseEntityToEdict);
				INIT_VIRTUAL_FUNCTION(m_servergameents, 5, EdictToBaseEntity);
			}
			else
			{
				INIT_VIRTUAL_FUNCTION(m_servergameents, 5, BaseEntityToEdict);
				INIT_VIRTUAL_FUNCTION(m_servergameents, 6, EdictToBaseEntity);
			}
#endif
			break;
		default:
			std::cout << "FATAL : Unhandled ServerGameEnts version " << m_servergameents_version << "\n";
			return false;
		};

		m_servergameclients = LoadInterface(game_factory, "ServerGameClients", m_servergameclients_version);
		VT_TRAP
		if (m_servergameclients == nullptr) return false;
		switch (m_servergameclients_version)
		{
		case 3:
		case 4:
			if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
			{
				INIT_VIRTUAL_FUNCTION(m_servergameclients, 13, ClientEarPosition);
			}
			else
			{
				INIT_VIRTUAL_FUNCTION(m_servergameclients, 12, ClientEarPosition);
			}
			break;
		default:
			std::cout << "FATAL : Unhandled ServerGameClients version " << m_servergameclients_version << "\n";
			return false;
		};

		m_engineserver = LoadInterface(interface_factory, "VEngineServer", m_engineserver_version);
		VT_TRAP
		if (m_engineserver == nullptr) return false;
		switch (m_engineserver_version)
		{
		case 23:
		{
			if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
			{
				INIT_VIRTUAL_FUNCTION(m_engineserver, 16, GetPlayerUserid);
				INIT_VIRTUAL_FUNCTION(m_engineserver, 17, GetPlayerNetworkIDString);
				INIT_VIRTUAL_FUNCTION(m_engineserver, 20, GetEntityCount);
				// Index of edict
				// PEntityOfEntIndex
				INIT_VIRTUAL_FUNCTION(m_engineserver, 21, GetPlayerNetInfo);
				INIT_VIRTUAL_FUNCTION(m_engineserver, 37, ServerCommand);
				INIT_VIRTUAL_FUNCTION(m_engineserver, 38, ServerExecute);
				// UserMessageBegin
				INIT_VIRTUAL_FUNCTION(m_engineserver, 44, MessageEnd);
				INIT_VIRTUAL_FUNCTION(m_engineserver, 45, SendUserMessage);
				INIT_VIRTUAL_FUNCTION(m_engineserver, 72, LogPrint);
				break;
			}
			// For other games, the interface v23 is retrocompatible until v21
		}
		case 22:
		case 21:
			INIT_VIRTUAL_FUNCTION(m_engineserver, 15, GetPlayerUserid);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 16, GetPlayerNetworkIDString);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 17, GetEntityCount);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 18, IndexOfEdict);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 19, PEntityOfEntIndex);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 20, GetPlayerNetInfo);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 36, ServerCommand);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 37, ServerExecute);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 43, UserMessageBegin);
			// SendUserMessage
			INIT_VIRTUAL_FUNCTION(m_engineserver, 44, MessageEnd);
			INIT_VIRTUAL_FUNCTION(m_engineserver, 72, LogPrint);
			break;
		default:
			std::cout << "FATAL : Unhandled VEngineServer version " << m_engineserver_version << "\n";
			return false;
		};

		m_gameeventmanager = LoadInterface(interface_factory, "GAMEEVENTSMANAGER", m_gameeventmanager_version);
		if (m_gameeventmanager == nullptr) return false;
		switch (m_gameeventmanager_version)
		{
		case 2:
			break;
		default:
			std::cout << "FATAL : Unhandled GAMEEVENTSMANAGER version " << m_gameeventmanager_version << "\n";
			return false;
		};

		m_serverpluginhelpers = LoadInterface(interface_factory, "ISERVERPLUGINHELPERS", m_serverpluginhelpers_version);
		if (m_serverpluginhelpers == nullptr) return false;
		switch (m_serverpluginhelpers_version)
		{
		case 1:
			break;
		default:
			std::cout << "FATAL : Unhandled ISERVERPLUGINHELPERS version " << m_serverpluginhelpers_version << "\n";
			return false;
		};

		m_enginetrace = LoadInterface(interface_factory, "EngineTraceServer", m_enginetrace_version);
		if (m_enginetrace == nullptr) return false;
		switch (m_enginetrace_version)
		{
		case 3:
			INIT_VIRTUAL_FUNCTION(m_enginetrace, 4, TraceRay);
			break;
		case 4:
			INIT_VIRTUAL_FUNCTION(m_enginetrace, 5, TraceRay);
			break;
		default:
			std::cout << "FATAL : Unhandled EngineTraceServer version " << m_enginetrace_version << "\n";
			return false;
		};

		m_cvar = LoadInterface(interface_factory, "VEngineCvar", m_enginecvar_version);
		if (m_cvar == nullptr) return false;

		SetupTraceFunctions();

		return true;
	}

	GameId InterfacesProxy::GetGameId()
	{
		return m_game;
	}

	IServerPluginHelpers001 * InterfacesProxy::GetServerPluginHelpers()
	{
		return (IServerPluginHelpers001 *)m_serverpluginhelpers;
	}

	IGameEventManager002 * InterfacesProxy::GetGameEventManager()
	{
		return (IGameEventManager002 *)m_gameeventmanager;
	}

	void * InterfacesProxy::GetCvar()
	{
		return m_cvar;
	}

	void InterfacesProxy::ICvar_RegisterConCommand(ConCommandBase *pCommandBase)
	{
		static_cast<ICvar004*>(m_cvar)->RegisterConCommand(pCommandBase);
	}

	void InterfacesProxy::ICvar_RegisterConCommand(ConCommandBase_csgo *pCommandBase)
	{
		static_cast<ICvar007_csgo*>(m_cvar)->RegisterConCommand(pCommandBase);
	}

	CVarDLLIdentifier_t InterfacesProxy::ICvar_AllocateDLLIdentifier()
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ICvar007_csgo*>(m_cvar)->AllocateDLLIdentifier();
		}
		else
		{
			return static_cast<ICvar004*>(m_cvar)->AllocateDLLIdentifier();
		}
	}

	void InterfacesProxy::ICvar_UnregisterConCommands(CVarDLLIdentifier_t id)
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			static_cast<ICvar007_csgo*>(m_cvar)->UnregisterConCommands(id);
		}
		else
		{
			static_cast<ICvar004*>(m_cvar)->UnregisterConCommands(id);
		}
	}

	void InterfacesProxy::ICvar_UnregisterConCommand(ConCommandBase *pCommandBase)
	{
		static_cast<ICvar004*>(m_cvar)->UnregisterConCommand(pCommandBase);
	}

	void InterfacesProxy::ICvar_UnregisterConCommand(ConCommandBase_csgo *pCommandBase)
	{
		static_cast<ICvar007_csgo*>(m_cvar)->UnregisterConCommand(pCommandBase);
	}

	void* InterfacesProxy::ICvar_FindVar(const char *var_name)
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ICvar007_csgo*>(m_cvar)->FindVar(var_name);
		}
		else
		{
			return static_cast<ICvar004*>(m_cvar)->FindVar(var_name);
		}
	}

	bool InterfacesProxy::ConVar_GetBool(void *convar)
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ConVar_csgo*>(convar)->GetBool();
		}
		else
		{
			return static_cast<ConVar*>(convar)->GetBool();
		}
	}

	template <typename T>
	void InterfacesProxy::ConVar_SetValue(void *convar, T v)
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ConVar_csgo*>(convar)->SetValue(v);
		}
		else
		{
			return static_cast<ConVar*>(convar)->SetValue(v);
		}
	}

	template <>
	void InterfacesProxy::ConVar_SetValue<bool>(void *convar, bool v)
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ConVar_csgo*>(convar)->SetValue((int)v);
		}
		else
		{
			return static_cast<ConVar*>(convar)->SetValue((int)v);
		}
	}

	char const * InterfacesProxy::ConCommand_GetName(void const * const command)
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ConCommand_csgo const * const>(command)->GetName();
		}
		else
		{
			return static_cast<ConCommand const * const>(command)->GetName();
		}
	}

	int InterfacesProxy::ConVar_GetInt(void* convar)
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ConVar_csgo*>(convar)->GetInt();
		}
		else
		{
			return static_cast<ConVar*>(convar)->GetInt();
		}
	}

	char const * InterfacesProxy::ConVar_GetString(void *convar)
	{
		if (m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ConVar_csgo*>(convar)->GetString();
		}
		else
		{
			return static_cast<ConVar*>(convar)->GetString();
		}
	}

	void* InterfacesProxy::ICvar_FindCommand(const char *name)
	{
		if (InterfacesProxy::m_game == SourceSdk::CounterStrikeGlobalOffensive)
		{
			return static_cast<ICvar007_csgo*>(m_cvar)->FindCommand(name);
		}
		else
		{
			return static_cast<ICvar004*>(m_cvar)->FindCommand(name);
		}
	}

	inline void CopyVirtualFunction(DWORD const * copy_from_vtptr, const int vf_id, DWORD * copy_to_fn)
	{
		(*copy_to_fn) = copy_from_vtptr[vf_id];
	}

	namespace InterfacesProxy
	{
		GameId m_game = CounterStrikeSource;

		void* m_enginetrace = nullptr;
		int m_enginetrace_version = 0;

		void* m_playerinfomanager = nullptr;
		int m_playerinfomanager_version = 0;

		void* m_gameeventmanager = nullptr;
		int m_gameeventmanager_version = 0;

		void* m_servergameclients = nullptr;
		int m_servergameclients_version = 0;

		void* m_servergamedll = nullptr;
		int m_servergamedll_version = 0;

		void* m_servergameents = nullptr;
		int m_servergameents_version = 0;

		void* m_serverpluginhelpers = nullptr;
		int m_serverpluginhelpers_version = 0;

		void* m_engineserver = nullptr;
		int m_engineserver_version = 0;

		void* m_cvar = nullptr;
		int m_enginecvar_version = 0;

		volatile GetTickInterval_t _vfptr_GetTickInterval = nullptr;

		volatile GetAllServerClasses_t _vfptr_GetAllServerClasses = nullptr;

		volatile GetPlayerInfo_t _vfptr_GetPlayerInfo = nullptr;

		volatile GetGlobalVars_t _vfptr_GetGlobalVars = nullptr;

		volatile BaseEntityToEdict_t _vfptr_BaseEntityToEdict = nullptr;

		volatile EdictToBaseEntity_t _vfptr_EdictToBaseEntity = nullptr;

		volatile ClientEarPosition_t _vfptr_ClientEarPosition = nullptr;

		volatile GetPlayerUserid_t _vfptr_GetPlayerUserid = nullptr;

		volatile GetPlayerNetworkIDString_t _vfptr_GetPlayerNetworkIDString = nullptr;

		volatile GetEntityCount_t _vfptr_GetEntityCount = nullptr;

		volatile IndexOfEdict_t _vfptr_IndexOfEdict = nullptr;

		volatile PEntityOfEntIndex_t _vfptr_PEntityOfEntIndex = nullptr;

		volatile GetPlayerNetInfo_t _vfptr_GetPlayerNetInfo = nullptr;

		volatile ServerCommand_t _vfptr_ServerCommand = nullptr;

		volatile ServerExecute_t _vfptr_ServerExecute = nullptr;

		volatile UserMessageBegin_t _vfptr_UserMessageBegin = nullptr;

		volatile SendUserMessage_t _vfptr_SendUserMessage = nullptr;

		volatile MessageEnd_t _vfptr_MessageEnd = nullptr;

		volatile LogPrint_t _vfptr_LogPrint = nullptr;

		volatile TraceRay_t _vfptr_TraceRay = nullptr;

		float Call_GetTickInterval()
		{
			return _vfptr_GetTickInterval(m_servergamedll);
		}

		ServerClass* Call_GetAllServerClasses()
		{
			return _vfptr_GetAllServerClasses(m_servergamedll);
		}

		void* Call_GetPlayerInfo(edict_t* player)
		{
			return _vfptr_GetPlayerInfo(m_playerinfomanager, player);
		}

		void* Call_GetGlobalVars()
		{
			return _vfptr_GetGlobalVars(m_playerinfomanager);
		}

		edict_t* Call_BaseEntityToEdict(void * const entity)
		{
			return _vfptr_BaseEntityToEdict(m_servergameents, const_cast<void*>(entity));
		}

		CBaseEntity* Call_EdictToBaseEntity(edict_t const * const entity)
		{
			return _vfptr_EdictToBaseEntity(m_servergameents, const_cast<edict_t*>(entity));
		}

		void Call_ClientEarPosition(edict_t* player, Vector* position)
		{
			_vfptr_ClientEarPosition(m_servergameclients, player, position);
		}

		int Call_GetPlayerUserid(edict_t const * player)
		{
			return _vfptr_GetPlayerUserid(m_engineserver, player);
		}

		char const * Call_GetPlayerNetworkIDString(edict_t const * player)
		{
			return _vfptr_GetPlayerNetworkIDString(m_engineserver, player);
		}

		int Call_GetEntityCount()
		{
			return _vfptr_GetEntityCount(m_engineserver);
		}

		int Call_IndexOfEdict(edict_t const * edict)
		{
			return _vfptr_IndexOfEdict(m_engineserver, edict);
		}

		edict_t* Call_PEntityOfEntIndex(int index)
		{
			return _vfptr_PEntityOfEntIndex(m_engineserver, index);
		}

		INetChannelInfo* Call_GetPlayerNetInfo(int index)
		{
			return _vfptr_GetPlayerNetInfo(m_engineserver, index);
		}

		void Call_ServerCommand(char const * command)
		{
			_vfptr_ServerCommand(m_engineserver, command);
		}

		void Call_ServerExecute()
		{
			_vfptr_ServerExecute(m_engineserver);
		}

		bf_write* Call_UserMessageBegin(IRecipientFilter* recipient, int message)
		{
			return _vfptr_UserMessageBegin(m_engineserver, recipient, message);
		}

		bf_write* Call_SendUserMessage(IRecipientFilter* recipient, int message, google::protobuf::Message const & msg)
		{
			return _vfptr_SendUserMessage(m_engineserver, recipient, message, msg);
		}

		void Call_MessageEnd()
		{
			_vfptr_MessageEnd(m_engineserver);
		}

		void Call_LogPrint(char const * message)
		{
			_vfptr_LogPrint(m_engineserver, message);
		}

		void Call_TraceRay(void const * ray, unsigned int mask, ITraceFilter* filter, void* trace)
		{
			_vfptr_TraceRay(m_enginetrace, ray, mask, filter, trace);
		}
	}
}

bool SteamGameServer_BSecure(void) { return true; }

