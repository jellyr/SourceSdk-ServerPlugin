#ifndef UTLHASHDICT_H
#define UTLHASHDICT_H

#include <cctype>

#include "utlhash.h"
/*#include "tier1/generichash.h"
#include "mathlib/mathlib.h"*/

static unsigned g_nRandomValues[256] =
{
	238,	164,	191,	168,	115,	 16,	142,	 11,	213,	214,	 57,	151,	248,	252,	 26,	198,
	13,	105,	102,	 25,	 43,	 42,	227,	107,	210,	251,	 86,	 66,	 83,	193,	126,	108,
	131,	  3,	 64,	186,	192,	 81,	 37,	158,	 39,	244,	 14,	254,	 75,	 30,	  2,	 88,
	172,	176,	255,	 69,	  0,	 45,	116,	139,	 23,	 65,	183,	148,	 33,	 46,	203,	 20,
	143,	205,	 60,	197,	118,	  9,	171,	 51,	233,	135,	220,	 49,	 71,	184,	 82,	109,
	36,	161,	169,	150,	 63,	 96,	173,	125,	113,	 67,	224,	 78,	232,	215,	 35,	219,
	79,	181,	 41,	229,	149,	153,	111,	217,	 21,	 72,	120,	163,	133,	 40,	122,	140,
	208,	231,	211,	200,	160,	182,	104,	110,	178,	237,	 15,	101,	 27,	 50,	 24,	189,
	177,	130,	187,	 92,	253,	136,	100,	212,	 19,	174,	 70,	 22,	170,	206,	162,	 74,
	247,	  5,	 47,	 32,	179,	117,	132,	195,	124,	123,	245,	128,	236,	223,	 12,	 84,
	54,	218,	146,	228,	157,	 94,	106,	 31,	 17,	 29,	194,	 34,	 56,	134,	239,	246,
	241,	216,	127,	 98,	  7,	204,	154,	152,	209,	188,	 48,	 61,	 87,	 97,	225,	 85,
	90,	167,	155,	112,	145,	114,	141,	 93,	250,	  4,	201,	156,	 38,	 89,	226,	196,
	1,	235,	 44,	180,	159,	121,	119,	166,	190,	144,	 10,	 91,	 76,	230,	221,	 80,
	207,	 55,	 58,	 53,	175,	  8,	  6,	 52,	 68,	242,	 18,	222,	103,	249,	147,	129,
	138,	243,	 28,	185,	 62,	 59,	240,	202,	234,	 99,	 77,	 73,	199,	137,	 95,	165,
};

unsigned HashString(const char *pszKey)
{
	const uint8_t *k = (const uint8_t *)pszKey;
	unsigned 	even = 0,
		odd = 0,
		n;

	while ((n = *k++) != 0)
	{
		even = g_nRandomValues[odd ^ n];
		if ((n = *k++) != 0)
			odd = g_nRandomValues[even ^ n];
		else
			break;
	}

	return (even << 8) | odd;
}

unsigned HashStringCaseless(const char *pszKey)
{
	const uint8_t *k = (const uint8_t *)pszKey;
	unsigned	even = 0,
		odd = 0,
		n;

	while ((n = toupper(*k++)) != 0)
	{
		even = g_nRandomValues[odd ^ n];
		if ((n = toupper(*k++)) != 0)
			odd = g_nRandomValues[even ^ n];
		else
			break;
	}

	return (even << 8) | odd;
}

inline unsigned int SmallestPowerOfTwoGreaterOrEqual(unsigned int x)
{
	x -= 1;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
}

template <typename T, bool bCaseInsensitive = true, bool bDupeStrings = true>
class CUtlHashDict
{
public:
	CUtlHashDict(int bucketCount = 16, int growCount = 0, int initCount = 0);
	~CUtlHashDict();
	T&         Element(unsigned i);
	const T&   Element(unsigned i) const;
	T&         operator[](unsigned i);
	const T&   operator[](unsigned i) const;
	char const *GetElementName(unsigned i) const;
	int Count() const;
	bool  IsValidIndex(unsigned i) const;
	static unsigned InvalidHandle();
	unsigned  Insert(const char *pName, const T &element);
	unsigned  Insert(const char *pName);
	unsigned  Find(const char *pName) const;
	void	RemoveAt(unsigned i);
	void	Remove(const char *pName);
	void	RemoveAll();
	void	Purge();
	void	PurgeAndDeleteElements();
	unsigned		First() const;
	unsigned		Next(unsigned i) const;
protected:
	struct Entry_t
	{
		const char *pszSymbol;
		T value;
	};
	template <bool bCaseIgnore>
	class CCompare
	{
	public:
		CCompare(int ignored) {}

		bool operator()(const Entry_t &entry1, const Entry_t &entry2) const
		{
			return !((bCaseIgnore) ? stricmp(entry1.pszSymbol, entry2.pszSymbol) : strcmp(entry1.pszSymbol, entry2.pszSymbol));
		}
	};
	template <bool bCaseIgnore>
	class CHash
	{
	public:
		CHash(int ignored) {}

		unsigned operator()(const Entry_t &entry) const
		{
			return !((bCaseIgnore) ? HashStringCaseless(entry.pszSymbol) : HashString(entry.pszSymbol));
		}
	};
	typedef CUtlHash<Entry_t, CCompare<bCaseInsensitive>, CHash<bCaseInsensitive> > CHashTable;
	CHashTable m_Elements;
	int m_nCount;
};
template <typename T, bool bCaseInsensitive, bool bDupeStrings>
CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::CUtlHashDict(int bucketCount /*= 16*/, int growCount /*= 0*/, int initCount /*= 0*/) :
	m_Elements(SmallestPowerOfTwoGreaterOrEqual(bucketCount), growCount, initCount)
{
}
template <typename T, bool bCaseInsensitive, bool bDupeStrings>
CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::~CUtlHashDict()
{
	Purge();
}
template <typename T, bool bCaseInsensitive, bool bDupeStrings>
inline T& CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Element(unsigned i)
{
	return m_Elements[i].value;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
inline const T& CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Element(unsigned i) const
{
	return m_Elements[i].value;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
inline char const *CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::GetElementName(unsigned i) const
{
	return m_Elements[i].pszSymbol;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
inline T& CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::operator[](unsigned i)
{
	return m_Elements[i].value;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
inline const T & CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::operator[](unsigned i) const
{
	return m_Elements[i].value;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
inline int CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Count() const
{
	return m_nCount;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
inline	bool CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::IsValidIndex(unsigned i) const
{
	return m_Elements.IsValidHandle(i);
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
inline unsigned CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::InvalidHandle()
{
	return CHashTable::InvalidHandle();
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
void CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::RemoveAt(unsigned elem)
{
	if (bDupeStrings)
	{
		free((void *)m_Elements[elem].pszSymbol);
	}
	m_Elements.Remove(elem);
	m_nCount--;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings> void CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Remove(const char *search)
{
	unsigned node = Find(search);
	if (node != InvalidHandle())
	{
		RemoveAt(node);
	}
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
void CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::RemoveAll()
{
	if (bDupeStrings)
	{
		UtlHashHandle_t index = m_Elements.GetFirstHandle();
		while (index != m_Elements.InvalidHandle())
		{
			free((void *)m_Elements[index].pszSymbol);
			index = m_Elements.GetNextHandle(index);
		}
	}

	m_Elements.RemoveAll();
	m_nCount = 0;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
void CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Purge()
{
	if (bDupeStrings)
	{
		UtlHashHandle_t index = m_Elements.GetFirstHandle();
		while (index != m_Elements.InvalidHandle())
		{
			free((void *)m_Elements[index].pszSymbol);
			index = m_Elements.GetNextHandle(index);
		}
	}

	m_Elements.Purge();
	m_nCount = 0;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
void CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::PurgeAndDeleteElements()
{
	unsigned index = m_Elements.GetFirstHandle();
	while (index != m_Elements.InvalidHandle())
	{
		if (bDupeStrings)
		{
			free((void *)m_Elements[index].pszSymbol);
		}
		delete m_Elements[index].value;
		index = m_Elements.GetNextHandle(index);
	}

	m_Elements.RemoveAll();
	m_nCount = 0;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
unsigned CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Insert(const char *pName, const T &element)
{
	m_nCount++;
	Entry_t entry =
	{
		(bDupeStrings) ? strdup(pName) : pName,
		element
	};
	bool bInserted;
	unsigned result = m_Elements.Insert(entry, &bInserted);
	if (bDupeStrings && !bInserted)
	{
		free((void *)entry.pszSymbol);
	}
	return result;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
unsigned CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Insert(const char *pName)
{
	m_nCount++;
	Entry_t entry =
	{
		(bDupeStrings) ? strdup(pName) : pName
	};
	bool bInserted;
	unsigned result = m_Elements.Insert(entry, &bInserted);
	if (bDupeStrings && !bInserted)
	{
		free((void *)entry.pszSymbol);
	}
	return result;
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
unsigned CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Find(const char *pName) const
{
	if (pName)
		return m_Elements.Find(*((Entry_t *)&pName));
	else
		return InvalidHandle();
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
unsigned CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::First() const
{
	return m_Elements.GetFirstHandle();
}

template <typename T, bool bCaseInsensitive, bool bDupeStrings>
unsigned CUtlHashDict<T, bCaseInsensitive, bDupeStrings>::Next(unsigned i) const
{
	return m_Elements.GetNextHandle(i);
}

#endif // UTLHASHDICT_H
