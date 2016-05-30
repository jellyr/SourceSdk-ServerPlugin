#ifndef BITBUF_H
#define BITBUF_H

#include "SdkPreprocessors.h"

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
	
	void BfWriteShort(bf_write* buffer, int val);
	void BfWriteByte(bf_write* buffer, int val);
	void BfWriteChar(bf_write* buffer, int val);
	void BfWriteString(bf_write* buffer, const char * val);
	int BfGetNumBitsLeft(bf_write const * buffer);
	inline void BfWriteBit(bf_write * buffer, bool value);
	void BfWriteSBitLong(bf_write * buffer, long const data, size_t const numBits);

};

#endif // BITBUF_H
