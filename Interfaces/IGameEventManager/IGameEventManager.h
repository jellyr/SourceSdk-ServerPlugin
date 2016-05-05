#ifndef IGAMEEVENTMANAGER_H
#define IGAMEEVENTMANAGER_H

#include "SdkPreprocessors.h"

#include "../interface.h"
#include "../../Containers/bitbuf.h"

namespace SourceSdk
{
	class CGameEvent;
	typedef unsigned long long fuck_u_visual_studio;

	abstract_class IGameEvent
	{
	public:
		virtual ~IGameEvent() {};
		virtual const char *GetName() const = 0;
		virtual bool  IsReliable() const = 0;
		virtual bool  IsLocal() const = 0; 
		virtual bool  IsEmpty(const char *keyName = NULL) = 0;
		virtual bool  GetBool( const char *keyName = NULL, bool defaultValue = false ) = 0;
		virtual int   GetInt( const char *keyName = NULL, int defaultValue = 0 ) = 0;
		virtual fuck_u_visual_studio GetUint64( const char *keyName = NULL, fuck_u_visual_studio defaultValue = 0 ) = 0;
		virtual float GetFloat( const char *keyName = NULL, float defaultValue = 0.0f ) = 0;
		virtual const char *GetString( const char *keyName = NULL, const char *defaultValue = "" ) = 0;
		virtual const wchar_t * GetWString(char const *keyName = NULL, const wchar_t *defaultValue = L"") = 0;
		virtual void SetBool( const char *keyName, bool value ) = 0;
		virtual void SetInt( const char *keyName, int value ) = 0;
		virtual void SetUint64( const char *keyName, fuck_u_visual_studio value ) = 0;
		virtual void SetFloat( const char *keyName, float value ) = 0;
		virtual void SetString( const char *keyName, const char *value ) = 0;
		virtual void SetWString( const char *keyName, const wchar_t *value ) = 0;
	};
};

//#include "IGameEventManager001.h"
#include "IGameEventManager002.h"

#endif // IGAMEEVENTMANAGER_H
