#ifndef BITBUF_H
#define BITBUF_H

#include "SdkPreprocessors.h"

#ifdef GNUC
//#	include <bitops.h>
#else
#include <intrin.h>
#endif

namespace SourceSdk
{
	struct bf_write
	{
		unsigned long*  m_pData;
		int				m_nDataBytes;
		int				m_nDataBits;
		int				m_iCurBit;
		bool			m_bOverflow;
		bool			m_bAssertOnOverflow;
		const char		*m_pDebugName;
	};
	
	typedef bf_write bf_read;

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

	extern CBitWriteMasksInit g_BitWriteMasksInit;
	
	void BfWriteShort(bf_write* buffer, int val);
	void BfWriteByte(bf_write* buffer, int val);
	void BfWriteChar(bf_write* buffer, int val);
	void BfWriteString(bf_write* buffer, const char * val);
	int BfGetNumBitsLeft(bf_write const * buffer);
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
	void BfWriteSBitLong(bf_write * buffer, long const data, size_t const numBits);

	template <typename type>
	union to_bits
	{
		static_assert(sizeof(long) >= sizeof(type), "Bits overflow");

		type origin;
		long bits;

		to_bits(type o) : origin(o)
		{
		}
	};

	template <typename type, size_t numBits>
	void BfWriteNBits(bf_write * buffer, type const data)
	{
		static_assert(numBits <= sizeof(type) * 4, "Bits overflow");
		static_assert(numBits > 0, "No bits to write");

		to_bits<type> const v(data);

		size_t i = 0;
		do
		{
#ifdef GNUC
			BfWriteBit(buffer, !!(v.bits & (1 << i)));
			//BfWriteBit(buffer, constant_test_bit(i, &(v.bits)));
#else
			BfWriteBit(buffer, _bittest(&(v.bits), i));
#endif
		} while (++i < numBits);
	}

};

#endif // BITBUF_H
