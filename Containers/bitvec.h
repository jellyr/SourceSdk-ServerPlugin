#ifndef BITVEC_H
#define BITVEC_H

class CBitVecAccessor
{
public:
				CBitVecAccessor(unsigned long *pDWords, int iBit);
	void		operator=(int val);
				operator unsigned long();
private:
	unsigned long	*m_pDWords;
	int				m_iBit;
};

template<int NUM_BITS>
class CBitVec
{
public:
					CBitVec();
	unsigned long*	Base();
	void			Init(int val = 0);
	CBitVecAccessor	operator[](int i);
	void			ClearAll( int nBits=NUM_BITS );
	void			SetAll( int nBits=NUM_BITS );
	unsigned long	Get( unsigned long iBit ) const;
	bool			IsBitSet( unsigned long iBit ) const;
	void			Set( unsigned long iBit );
	void			Clear( unsigned long iBit );
	void			Set( unsigned long iBit, int bOn );
	void			Copy( CBitVec<NUM_BITS> const &other, int nBits=NUM_BITS );
	bool			Compare( CBitVec<NUM_BITS> const &other, int nBits=NUM_BITS );
	CBitVec&		operator=(CBitVec<NUM_BITS> const &other);
	bool			operator==(CBitVec<NUM_BITS> const &other);
	bool			operator!=(CBitVec<NUM_BITS> const &other);
	int				GetNumDWords() const;
	unsigned long	GetDWord(int i) const;
	void			SetDWord(int i, unsigned long val);
	int				GetNumBits() const;
	int				FindNextSetBit(int iStartBit) const;
private:
	enum			{NUM_DWORDS = NUM_BITS/32 + !!(NUM_BITS & 31)};
	unsigned long	m_DWords[NUM_DWORDS];
};

inline CBitVecAccessor::CBitVecAccessor(unsigned long *pDWords, int iBit)
{
	m_pDWords = pDWords;
	m_iBit = iBit;
}

inline void CBitVecAccessor::operator=(int val)
{
	if(val)
		m_pDWords[m_iBit >> 5] |= (1 << (m_iBit & 31));
	else
		m_pDWords[m_iBit >> 5] &= ~(unsigned long)(1 << (m_iBit & 31));
}

inline CBitVecAccessor::operator unsigned long()
{
	return m_pDWords[m_iBit >> 5] & (1 << (m_iBit & 31));
}

template<int NUM_BITS>
inline int CBitVec<NUM_BITS>::GetNumBits() const
{
	return NUM_BITS;
}

template<int NUM_BITS>
inline CBitVec<NUM_BITS>::CBitVec()
{
	for(int i=0; i < NUM_DWORDS; i++)
		m_DWords[i] = 0;
}

template<int NUM_BITS>
inline void CBitVec<NUM_BITS>::Init(int val)
{
	unsigned long dwVal = val ? 0xFFFFFFFF : 0;
	for( int i=0; i < NUM_DWORDS; i++ )
		m_DWords[i] = dwVal;
}

template<int NUM_BITS>
inline unsigned long* CBitVec<NUM_BITS>::Base()
{
	return m_DWords;
}

template<int NUM_BITS>
inline CBitVec<NUM_BITS>& CBitVec<NUM_BITS>::operator=(CBitVec<NUM_BITS> const &other)
{
	memcpy(m_DWords, other.m_DWords, sizeof(m_DWords));
	return *this;
}

template<int NUM_BITS>
inline CBitVecAccessor CBitVec<NUM_BITS>::operator[](int i)	
{
	return CBitVecAccessor(m_DWords, i);
}

template< int SIZE >
inline void CBitVec<SIZE>::ClearAll( int nBits )
{
	int nDWords = PAD_NUMBER( nBits, 32 ) >> 5;
	for( int i=0; i < nDWords; i++ )
		m_DWords[i] = 0;
}

template< int SIZE >
inline void CBitVec<SIZE>::SetAll( int nBits )
{
	int nDWords = PAD_NUMBER( nBits, 32 ) >> 5;
	for( int i=0; i < nDWords; i++ )
		m_DWords[i] = 0xFFFFFFFF;
}

template< int SIZE >
inline unsigned long CBitVec<SIZE>::Get( unsigned long iBit ) const
{
	return m_DWords[iBit >> 5] & (1 << (iBit & 31));
}

template< int SIZE >
bool CBitVec<SIZE>::IsBitSet( unsigned long iBit ) const
{
	return ( m_DWords[iBit >> 5] & (1 << (iBit & 31)) ) != 0;
}

template< int SIZE >
inline void CBitVec<SIZE>::Set( unsigned long iBit )
{
	m_DWords[iBit >> 5] |= (1 << (iBit & 31));
}

template< int SIZE >
inline void CBitVec<SIZE>::Clear( unsigned long iBit )
{
	m_DWords[iBit >> 5] &= ~(1 << (iBit & 31));
}

template< int SIZE >
inline void CBitVec<SIZE>::Set( unsigned long iBit, int bOn )
{
	if( bOn )
		Set( iBit );
	else
		Clear( iBit );
}

template< int SIZE >
inline void CBitVec<SIZE>::Copy( CBitVec<SIZE> const &other, int nBits )
{
	int nBytes = PAD_NUMBER( nBits, 8 ) >> 3;
	memcpy( m_DWords, other.m_DWords, nBytes );
}

template< int SIZE >
inline bool CBitVec<SIZE>::Compare( CBitVec<SIZE> const &other, int nBits )
{
	int nBytes = PAD_NUMBER( nBits, 8 ) >> 3;
	return memcmp( m_DWords, other.m_DWords, nBytes ) == 0;
}

template<int NUM_BITS>
inline bool CBitVec<NUM_BITS>::operator==(CBitVec<NUM_BITS> const &other)
{
	for(int i=0; i < NUM_DWORDS; i++)
		if(m_DWords[i] != other.m_DWords[i])
			return false;
	return true;
}

template<int NUM_BITS>
inline bool CBitVec<NUM_BITS>::operator!=(CBitVec<NUM_BITS> const &other)
{
	return !(*this == other);
}

template<int NUM_BITS>
inline int CBitVec<NUM_BITS>::GetNumDWords() const
{
	return NUM_DWORDS;
}

template<int NUM_BITS>
inline unsigned long CBitVec<NUM_BITS>::GetDWord(int i) const
{
	return m_DWords[i];
}

template<int NUM_BITS>
inline void CBitVec<NUM_BITS>::SetDWord(int i, unsigned long val)
{
	m_DWords[i] = val;
}

template<int NUM_BITS>
inline int CBitVec<NUM_BITS>::FindNextSetBit(int iStartBit) const
{
	int currentBit = iStartBit;
	while (currentBit < NUM_BITS)
	{
		if ( (currentBit & 31) == 0)
		{
			if (m_DWords[currentBit>>5] == 0)
			{
				currentBit += 32;
				continue;
			}
		}
		do 
		{
			if( m_DWords[currentBit >> 5] & (1 << (currentBit & 31)) )
				return currentBit; 
			++currentBit;
		} while ( (currentBit & 31) != 0 );
	}
	return -1; 
}

#endif // BITVEC_H
