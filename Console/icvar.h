#ifndef ICVAR_H
#define ICVAR_H

#include "SdkPreprocessors.h"

#include "../Interfaces/IAppSystem.h"
#include "iconvar.h"

namespace SourceSdk
{
	class ConCommandBase;
	class ConCommand;
	class ConVar;
	class IConsoleDisplayFunc;
	class ICvarQuery;
	typedef int CVarDLLIdentifier_t;

	abstract_class ICvar004_csgo : public IAppSystem_csgo
	{
	public:
		virtual CVarDLLIdentifier_t AllocateDLLIdentifier() = 0;
		virtual void			RegisterConCommand( void *pCommandBase ) = 0;
		virtual void			UnregisterConCommand(void *pCommandBase ) = 0;
		virtual void			UnregisterConCommands( CVarDLLIdentifier_t id ) = 0;
		virtual const char*		GetCommandLineValue( const char *pVariableName ) = 0;
		virtual ConCommandBase *FindCommandBase( const char *name ) = 0;
		virtual const ConCommandBase *FindCommandBase( const char *name ) const = 0;
		virtual ConVar			*FindVar ( const char *var_name ) = 0;
		virtual const ConVar	*FindVar ( const char *var_name ) const = 0;
		virtual ConCommand		*FindCommand( const char *name ) = 0;
		virtual const ConCommand *FindCommand( const char *name ) const = 0;
		virtual void			InstallGlobalChangeCallback( FnChangeCallback_t callback ) = 0;
		virtual void			RemoveGlobalChangeCallback( FnChangeCallback_t callback ) = 0;
		virtual void			CallGlobalChangeCallbacks( ConVar *var, const char *pOldString, float flOldValue ) = 0;
		virtual void			InstallConsoleDisplayFunc( IConsoleDisplayFunc* pDisplayFunc ) = 0;
		virtual void			RemoveConsoleDisplayFunc( IConsoleDisplayFunc* pDisplayFunc ) = 0;
		virtual void			ConsoleColorPrintf( const Color& clr, const char *pFormat, ... ) const = 0;
		virtual void			ConsolePrintf( const char *pFormat, ... ) const = 0;
		virtual void			ConsoleDPrintf( const char *pFormat, ... ) const = 0;
		virtual void			RevertFlaggedConVars( int nFlag ) = 0;
		virtual void			InstallCVarQuery( ICvarQuery *pQuery ) = 0;
		virtual void			SetMaxSplitScreenSlots( int nSlots ) = 0;
		virtual int				GetMaxSplitScreenSlots() const = 0;
		virtual void			AddSplitScreenConVars() = 0;
		virtual void			RemoveSplitScreenConVars( CVarDLLIdentifier_t id ) = 0;
		virtual int				GetConsoleDisplayFuncCount() const = 0;
		virtual void			GetConsoleText( int nDisplayFuncIndex, char *pchText, size_t bufSize ) const = 0;
		virtual bool			IsMaterialThreadSetAllowed( ) const = 0;
		virtual void			QueueMaterialThreadSetValue( ConVar *pConVar, const char *pValue ) = 0;
		virtual void			QueueMaterialThreadSetValue( ConVar *pConVar, int nValue ) = 0;
		virtual void			QueueMaterialThreadSetValue( ConVar *pConVar, float flValue ) = 0;
		virtual bool			HasQueuedMaterialThreadConVarSets() const = 0;
		virtual int				ProcessQueuedMaterialThreadConVarSets() = 0;
	};

	abstract_class ICvar004 : public IAppSystem
	{
	public:
		virtual CVarDLLIdentifier_t AllocateDLLIdentifier() = 0;
		virtual void			RegisterConCommand(ConCommandBase *pCommandBase) = 0;
		virtual void			UnregisterConCommand(ConCommandBase *pCommandBase) = 0;
		virtual void			UnregisterConCommands(CVarDLLIdentifier_t id) = 0;
		virtual const char*		GetCommandLineValue(const char *pVariableName) = 0;
		virtual ConCommandBase *FindCommandBase(const char *name) = 0;
		virtual const ConCommandBase *FindCommandBase(const char *name) const = 0;
		virtual ConVar			*FindVar(const char *var_name) = 0;
		virtual const ConVar	*FindVar(const char *var_name) const = 0;
		virtual ConCommand		*FindCommand(const char *name) = 0;
		virtual const ConCommand *FindCommand(const char *name) const = 0;
		virtual void			InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;
		virtual void			RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;
		virtual void			CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) = 0;
		virtual void			InstallConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
		virtual void			RemoveConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
		virtual void			ConsoleColorPrintf(const Color& clr, const char *pFormat, ...) const = 0;
		virtual void			ConsolePrintf(const char *pFormat, ...) const = 0;
		virtual void			ConsoleDPrintf(const char *pFormat, ...) const = 0;
		virtual void			RevertFlaggedConVars(int nFlag) = 0;
		virtual void			InstallCVarQuery(ICvarQuery *pQuery) = 0;
		virtual void			SetMaxSplitScreenSlots(int nSlots) = 0;
		virtual int				GetMaxSplitScreenSlots() const = 0;
		virtual void			AddSplitScreenConVars() = 0;
		virtual void			RemoveSplitScreenConVars(CVarDLLIdentifier_t id) = 0;
		virtual int				GetConsoleDisplayFuncCount() const = 0;
		virtual void			GetConsoleText(int nDisplayFuncIndex, char *pchText, size_t bufSize) const = 0;
		virtual bool			IsMaterialThreadSetAllowed() const = 0;
		virtual void			QueueMaterialThreadSetValue(ConVar *pConVar, const char *pValue) = 0;
		virtual void			QueueMaterialThreadSetValue(ConVar *pConVar, int nValue) = 0;
		virtual void			QueueMaterialThreadSetValue(ConVar *pConVar, float flValue) = 0;
		virtual bool			HasQueuedMaterialThreadConVarSets() const = 0;
		virtual int				ProcessQueuedMaterialThreadConVarSets() = 0;
	};
};

#endif // ICVAR_H
