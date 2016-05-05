#ifndef IRECIPIENTFILTER_H
#define IRECIPIENTFILTER_H

#include "SdkPreprocessors.h"

namespace SourceSdk
{
	class IRecipientFilter
	{
	public:
		virtual			~IRecipientFilter() {}

		virtual bool	IsReliable(void) const = 0;
		virtual bool	IsInitMessage(void) const = 0;

		virtual int		GetRecipientCount(void) const = 0;
		virtual int		GetRecipientIndex(int slot) const = 0;
	};
};

#endif // IRECIPIENTFILTER_H