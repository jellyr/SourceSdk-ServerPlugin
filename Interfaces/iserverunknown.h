#ifndef SDK_ISERVERUNKNOWN_H
#define SDK_ISERVERUNKNOWN_H

#include "SdkPreprocessors.h"

namespace SourceSdk
{
	class ICollideable;
	class IServerNetworkable;
	class CBaseEntity;
	
	class CBaseHandle;

	class IHandleEntity
	{
	public:
		virtual ~IHandleEntity() {}
		virtual void SetRefEHandle(const CBaseHandle &handle) = 0;
		virtual const CBaseHandle& GetRefEHandle() const = 0;
	};

	class CBaseHandle
	{
	public:
		CBaseHandle();
		CBaseHandle( const CBaseHandle &other );
		CBaseHandle( unsigned long value );
		CBaseHandle( int iEntry, int iSerialNumber );
		void Init( int iEntry, int iSerialNumber );
		void Term();
		bool IsValid() const;
		int GetEntryIndex() const;
		int GetSerialNumber() const;
		int ToInt() const;
		bool operator !=( const CBaseHandle &other ) const;
		bool operator ==( const CBaseHandle &other ) const;
		bool operator ==( const IHandleEntity* pEnt ) const;
		bool operator !=( const IHandleEntity* pEnt ) const;
		bool operator <( const CBaseHandle &other ) const;
		bool operator <( const IHandleEntity* pEnt ) const;
		const CBaseHandle& operator=( const IHandleEntity *pEntity );
		const CBaseHandle& Set( const IHandleEntity *pEntity );
		IHandleEntity* Get() const;
	protected:
		unsigned long	m_Index;
	};

	inline CBaseHandle::CBaseHandle()
	{
		m_Index = INVALID_EHANDLE_INDEX;
	}

	inline CBaseHandle::CBaseHandle( const CBaseHandle &other )
	{
		m_Index = other.m_Index;
	}

	inline CBaseHandle::CBaseHandle( unsigned long value )
	{
		m_Index = value;
	}

	inline CBaseHandle::CBaseHandle( int iEntry, int iSerialNumber )
	{
		Init( iEntry, iSerialNumber );
	}

	inline void CBaseHandle::Init( int iEntry, int iSerialNumber )
	{
		m_Index = iEntry | (iSerialNumber << NUM_ENT_ENTRY_BITS);
	}

	inline void CBaseHandle::Term()
	{
		m_Index = INVALID_EHANDLE_INDEX;
	}

	inline bool CBaseHandle::IsValid() const
	{
		return m_Index != INVALID_EHANDLE_INDEX;
	}

	inline int CBaseHandle::GetEntryIndex() const
	{
		return m_Index & ENT_ENTRY_MASK;
	}

	inline int CBaseHandle::GetSerialNumber() const
	{
		return m_Index >> NUM_ENT_ENTRY_BITS;
	}

	inline int CBaseHandle::ToInt() const
	{
		return (int)m_Index;
	}

	inline bool CBaseHandle::operator !=( const CBaseHandle &other ) const
	{
		return m_Index != other.m_Index;
	}

	inline bool CBaseHandle::operator ==( const CBaseHandle &other ) const
	{
		return m_Index == other.m_Index;
	}

	inline bool CBaseHandle::operator ==( const IHandleEntity* pEnt ) const
	{
		return Get() == pEnt;
	}

	inline bool CBaseHandle::operator !=( const IHandleEntity* pEnt ) const
	{
		return Get() != pEnt;
	}

	inline bool CBaseHandle::operator <( const CBaseHandle &other ) const
	{
		return m_Index < other.m_Index;
	}

	inline bool CBaseHandle::operator <( const IHandleEntity *pEntity ) const
	{
		unsigned long otherIndex = (pEntity) ? pEntity->GetRefEHandle().m_Index : INVALID_EHANDLE_INDEX;
		return m_Index < otherIndex;
	}

	inline const CBaseHandle& CBaseHandle::operator=( const IHandleEntity *pEntity )
	{
		return Set( pEntity );
	}

	inline const CBaseHandle& CBaseHandle::Set( const IHandleEntity *pEntity ) 
	{ 
		if ( pEntity )
		{
			*this = pEntity->GetRefEHandle();
		}
		else
		{
			m_Index = INVALID_EHANDLE_INDEX;
		}
		
		return *this;
	}

	class IServerUnknown : public IHandleEntity
	{
	public:
		virtual ICollideable*		GetCollideable() = 0;
		virtual IServerNetworkable*	GetNetworkable() = 0;
		virtual CBaseEntity*		GetBaseEntity() = 0;
	};
};

#endif // SDK_ISERVERUNKNOWN_H