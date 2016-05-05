#ifndef ICONVAR_H
#define ICONVAR_H

#include "SdkPreprocessors.h"

#include "color.h"

namespace SourceSdk
{
	class CCommand;

	abstract_class IConVar_csgo
	{
	public:
		virtual void SetValue( const char *pValue ) = 0;
		virtual void SetValue( float flValue ) = 0;
		virtual void SetValue( int nValue ) = 0;
		virtual void SetValue( Color value ) = 0;
		virtual const char *GetName( void ) const = 0;
		virtual const char *GetBaseName( void ) const = 0;
		virtual bool IsFlagSet( int nFlag ) const = 0;
		virtual int GetSplitScreenPlayerSlot() const = 0;
	};

	abstract_class IConVar
	{
	public:
		virtual void SetValue(const char *pValue) = 0;
		virtual void SetValue(float flValue) = 0;
		virtual void SetValue(int nValue) = 0;
		virtual bool IsFlagSet(int nFlag) const = 0;
	};
};

#endif // ICONVAR_H
