#ifndef INTERFACE_H
#define INTERFACE_H

#include "SdkPreprocessors.h"

namespace SourceSdk
{
	typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
	typedef void* (*InstantiateInterfaceFn)();

	class IBaseInterface
	{
	public:
		virtual	~IBaseInterface() {}
	};

	class InterfaceReg
	{
	public:
		InterfaceReg(InstantiateInterfaceFn fn, const char *pName);
	public:
		InstantiateInterfaceFn	m_CreateFn;
		const char				*m_pName;
		InterfaceReg			*m_pNext;
		static InterfaceReg		*s_pInterfaceRegs;
	};

	class CSysModule;
	enum 
	{
		IFACE_OK = 0,
		IFACE_FAILED
	};

	DLL_EXPORT void* CreateInterface(const char *pName, int *pReturnCode);
};

#endif
