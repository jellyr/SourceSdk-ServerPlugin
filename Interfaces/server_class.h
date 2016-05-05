#ifndef SDK_SERVERCLASS_H
#define SDK_SERVERCLASS_H

#include "SdkPreprocessors.h"

#include "dt_send.h"

namespace SourceSdk
{
	struct ServerClass
	{
		char						*m_pNetworkName;
		SendTable					*m_pTable;
		ServerClass					*m_pNext;
		int							m_ClassID;
		int							m_InstanceBaselineIndex;
	};
};

#endif // SDK_SERVERCLASS_H