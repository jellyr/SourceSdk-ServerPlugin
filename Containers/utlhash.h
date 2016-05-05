#ifndef UTLHASH_H
#define UTLHASH_H

#include <algorithm>

#include "utlvector.h"

typedef unsigned int UtlHashHandle_t;

template<class Data, typename C = bool (*)( Data const&, Data const& ), typename K = unsigned int (*)( Data const& ) >
class CUtlHash
{
public:
	typedef C CompareFunc_t;
	typedef K KeyFunc_t;
	CUtlHash( int bucketCount = 0, int growCount = 0, int initCount = 0,
		      CompareFunc_t compareFunc = 0, KeyFunc_t keyFunc = 0 );
	~CUtlHash();
	static UtlHashHandle_t InvalidHandle( void )  { return ( UtlHashHandle_t )~0; }
	bool IsValidHandle( UtlHashHandle_t handle ) const;
	int Count( void ) const;
	void Purge( void );
	UtlHashHandle_t Insert( Data const &src );
	UtlHashHandle_t Insert( Data const &src, bool *pDidInsert );
	UtlHashHandle_t AllocEntryFromKey( Data const &src );
	void Remove( UtlHashHandle_t handle );
	void RemoveAll();
	UtlHashHandle_t Find( Data const &src ) const;
	Data &Element( UtlHashHandle_t handle );
	Data const &Element( UtlHashHandle_t handle ) const;
	Data &operator[]( UtlHashHandle_t handle );
	Data const &operator[]( UtlHashHandle_t handle ) const;
	UtlHashHandle_t GetFirstHandle() const;
	UtlHashHandle_t GetNextHandle( UtlHashHandle_t h ) const;
protected:
	int GetBucketIndex( UtlHashHandle_t handle ) const;
	int GetKeyDataIndex( UtlHashHandle_t handle ) const;
	UtlHashHandle_t BuildHandle( int ndxBucket, int ndxKeyData ) const;
	bool DoFind( Data const &src, unsigned int *pBucket, int *pIndex ) const;
protected:
	typedef CUtlVector<Data> HashBucketList_t;
	CUtlVector<HashBucketList_t>	m_Buckets;
	CompareFunc_t					m_CompareFunc;
	KeyFunc_t						m_KeyFunc;
	bool							m_bPowerOfTwo;
	unsigned int					m_ModMask;
};

template<class Data, typename C, typename K>
CUtlHash<Data, C, K>::CUtlHash( int bucketCount, int growCount, int initCount,
						  CompareFunc_t compareFunc, KeyFunc_t keyFunc ) :
	m_CompareFunc( compareFunc ),
	m_KeyFunc( keyFunc )
{
	bucketCount = std::min(bucketCount, 65536);
	m_Buckets.SetSize( bucketCount );
	for( int ndxBucket = 0; ndxBucket < bucketCount; ndxBucket++ )
	{
		m_Buckets[ndxBucket].SetSize( initCount );
		m_Buckets[ndxBucket].SetGrowSize( growCount );
	}
	m_bPowerOfTwo = (bucketCount & (bucketCount - 1)) == 0;
	m_ModMask = m_bPowerOfTwo ? (bucketCount-1) : 0;
}

template<class Data, typename C, typename K>
CUtlHash<Data, C, K>::~CUtlHash()
{
	Purge();
}

template<class Data, typename C, typename K>
inline bool CUtlHash<Data, C, K>::IsValidHandle( UtlHashHandle_t handle ) const
{
	int ndxBucket = GetBucketIndex( handle );
	int ndxKeyData = GetKeyDataIndex( handle );
	if( ( ndxBucket < m_Buckets.Count() ) )
	{
		if(  ( ndxKeyData < m_Buckets[ndxBucket].Count() ) )
			return true;
	}
	return false;
}

template<class Data, typename C, typename K>
inline int CUtlHash<Data, C, K>::Count( void ) const
{
	int count = 0;
	int bucketCount = m_Buckets.Count();
	for( int ndxBucket = 0; ndxBucket < bucketCount; ndxBucket++ )
	{
		count += m_Buckets[ndxBucket].Count();
	}
	return count;
}

template<class Data, typename C, typename K>
inline int CUtlHash<Data, C, K>::GetBucketIndex( UtlHashHandle_t handle ) const
{
	return ( ( ( handle >> 16 ) & 0x0000ffff ) );
}

template<class Data, typename C, typename K>
inline int CUtlHash<Data, C, K>::GetKeyDataIndex( UtlHashHandle_t handle ) const
{
	return ( handle & 0x0000ffff );
}

template<class Data, typename C, typename K>
inline UtlHashHandle_t CUtlHash<Data, C, K>::BuildHandle( int ndxBucket, int ndxKeyData ) const
{
	UtlHashHandle_t handle = ndxKeyData;
	handle |= ( ndxBucket << 16 );
	return handle;
}

template<class Data, typename C, typename K>
inline void CUtlHash<Data, C, K>::Purge( void )
{
	int bucketCount = m_Buckets.Count();
	for( int ndxBucket = 0; ndxBucket < bucketCount; ndxBucket++ )
	{
		m_Buckets[ndxBucket].Purge();
	}
}

template<class Data, typename C, typename K>
inline bool CUtlHash<Data, C, K>::DoFind( Data const &src, unsigned int *pBucket, int *pIndex ) const
{
	unsigned int key = m_KeyFunc( src );
	unsigned int ndxBucket;
	if( m_bPowerOfTwo )
	{
		*pBucket = ndxBucket = ( key & m_ModMask );
	}
	else
	{
		int bucketCount = m_Buckets.Count();
		*pBucket = ndxBucket = key % bucketCount;
	}
	int ndxKeyData;
	const CUtlVector<Data> &bucket = m_Buckets[ndxBucket];
	int keyDataCount = bucket.Count();
	for( ndxKeyData = 0; ndxKeyData < keyDataCount; ndxKeyData++ )
	{
		if( m_CompareFunc( bucket.Element( ndxKeyData ), src ) )
			break;
	}
	if( ndxKeyData == keyDataCount )
		return false;
	*pIndex = ndxKeyData;
	return true;
}

template<class Data, typename C, typename K>
inline UtlHashHandle_t CUtlHash<Data, C, K>::Find( Data const &src ) const
{
	unsigned int ndxBucket;
	int ndxKeyData;
	if ( DoFind( src, &ndxBucket, &ndxKeyData ) )
	{
		return ( BuildHandle( ndxBucket, ndxKeyData ) );
	}
	return ( InvalidHandle() );
}

template<class Data, typename C, typename K>
inline UtlHashHandle_t CUtlHash<Data, C, K>::Insert( Data const &src )
{
	unsigned int ndxBucket;
	int ndxKeyData;
	if ( DoFind( src, &ndxBucket, &ndxKeyData ) )
	{
		return ( BuildHandle( ndxBucket, ndxKeyData ) );
	}
	ndxKeyData = m_Buckets[ndxBucket].AddToTail( src );
	return ( BuildHandle( ndxBucket, ndxKeyData ) );
}

template<class Data, typename C, typename K>
inline UtlHashHandle_t CUtlHash<Data, C, K>::Insert( Data const &src, bool *pDidInsert )
{
	unsigned int ndxBucket;
	int ndxKeyData;
	if ( DoFind( src, &ndxBucket, &ndxKeyData ) )
	{
		*pDidInsert = false;
		return ( BuildHandle( ndxBucket, ndxKeyData ) );
	}
	*pDidInsert = true;
	ndxKeyData = m_Buckets[ndxBucket].AddToTail( src );
	return ( BuildHandle( ndxBucket, ndxKeyData ) );
}

template<class Data, typename C, typename K>
inline UtlHashHandle_t CUtlHash<Data, C, K>::AllocEntryFromKey( Data const &src )
{
	unsigned int ndxBucket;
	int ndxKeyData;
	if ( DoFind( src, &ndxBucket, &ndxKeyData ) )
	{
		return ( BuildHandle( ndxBucket, ndxKeyData ) );
	}
	ndxKeyData = m_Buckets[ndxBucket].AddToTail();
	return ( BuildHandle( ndxBucket, ndxKeyData ) );
}

template<class Data, typename C, typename K>
inline void CUtlHash<Data, C, K>::Remove( UtlHashHandle_t handle )
{
	int ndxBucket = GetBucketIndex( handle );
	int ndxKeyData = GetKeyDataIndex( handle );
	if( m_Buckets[ndxBucket].IsValidIndex( ndxKeyData ) )
	{
		m_Buckets[ndxBucket].FastRemove( ndxKeyData );
	}
}

template<class Data, typename C, typename K>
inline void CUtlHash<Data, C, K>::RemoveAll()
{
	int bucketCount = m_Buckets.Count();
	for( int ndxBucket = 0; ndxBucket < bucketCount; ndxBucket++ )
	{
		m_Buckets[ndxBucket].RemoveAll();
	}
}

template<class Data, typename C, typename K>
inline Data &CUtlHash<Data, C, K>::Element( UtlHashHandle_t handle )
{
	int ndxBucket = GetBucketIndex( handle );
	int ndxKeyData = GetKeyDataIndex( handle );
	return ( m_Buckets[ndxBucket].Element( ndxKeyData ) );
}

template<class Data, typename C, typename K>
inline Data const &CUtlHash<Data, C, K>::Element( UtlHashHandle_t handle ) const
{
	int ndxBucket = GetBucketIndex( handle );
	int ndxKeyData = GetKeyDataIndex( handle );
	return ( m_Buckets[ndxBucket].Element( ndxKeyData ) );
}

template<class Data, typename C, typename K>
inline Data &CUtlHash<Data, C, K>::operator[]( UtlHashHandle_t handle )
{
	int ndxBucket = GetBucketIndex( handle );
	int ndxKeyData = GetKeyDataIndex( handle );
	return ( m_Buckets[ndxBucket].Element( ndxKeyData ) );
}

template<class Data, typename C, typename K>
inline Data const &CUtlHash<Data, C, K>::operator[]( UtlHashHandle_t handle ) const
{
	int ndxBucket = GetBucketIndex( handle );
	int ndxKeyData = GetKeyDataIndex( handle );
	return ( m_Buckets[ndxBucket].Element( ndxKeyData ) );
}

template<class Data, typename C, typename K>
inline UtlHashHandle_t CUtlHash<Data, C, K>::GetFirstHandle() const
{
	return GetNextHandle( ( UtlHashHandle_t )-1 );
}

template<class Data, typename C, typename K>
inline UtlHashHandle_t CUtlHash<Data, C, K>::GetNextHandle( UtlHashHandle_t handle ) const
{
	++handle;
	int bi = GetBucketIndex( handle );
	int ki =  GetKeyDataIndex( handle );
	int nBuckets = m_Buckets.Count();
	for ( ; bi < nBuckets; ++bi )
	{
		if ( ki < m_Buckets[ bi ].Count() )
			return BuildHandle( bi, ki );

		ki = 0;
	}
	return InvalidHandle();
}

#endif
