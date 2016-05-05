#ifndef CONVAR_H
#define CONVAR_H

#include "SdkPreprocessors.h"

#include "../Containers/utlvector.h"
#include "color.h"
#include "icvar.h"

namespace SourceSdk
{
	class ConVar_csgo;
	class ConVar;
	class CCommand;
	class ConCommand_csgo;
	class ConCommandBase_csgo;
	class ConCommand;
	class ConCommandBase;
	struct CUtlString
	{
		char idontcare;
	};
	struct characterset_t
	{
		char set[256];
	};

	static int s_nDLLIdentifier;

	class IConCommandBaseAccessor_csgo
	{
	public:
		virtual bool RegisterConCommandBase( ConCommandBase_csgo *pVar ) = 0;
	};

	class IConCommandBaseAccessor
	{
	public:
		virtual bool RegisterConCommandBase(ConCommandBase *pVar) = 0;
	};

	class ICommandCallback
	{
	public:
		virtual void CommandCallback( const CCommand &command ) = 0;
	};

	class ICommandCompletionCallback
	{
	public:
		virtual int  CommandCompletionCallback( const char *pPartial, CUtlVector< CUtlString > &commands ) = 0;
	};

	class ConCommandBase_csgo
	{
		friend class CCvar;
		friend class ConVar_csgo;
		friend class ConCommand_csgo;
		friend void ConVar_Register_csgo(int nCVarFlag, IConCommandBaseAccessor_csgo *pAccessor);
		friend class CDefaultCvar;

	public:
		ConCommandBase_csgo(void);
		ConCommandBase_csgo(const char *pName, const char *pHelpString = 0, int flags = 0);
		virtual						~ConCommandBase_csgo(void);
		virtual	bool				IsCommand(void) const;
		virtual bool				IsFlagSet(int flag) const;
		virtual void				AddFlags(int flags);
		virtual void				RemoveFlags(int flags);
		virtual int					GetFlags() const;
		virtual const char			*GetName(void) const;
		virtual const char			*GetHelpText(void) const;
		const ConCommandBase_csgo		*GetNext(void) const;
		ConCommandBase_csgo				*GetNext(void);
		virtual bool				IsRegistered(void) const;
		virtual CVarDLLIdentifier_t	GetDLLIdentifier() const {return s_nDLLIdentifier;};
	protected:
		virtual void				CreateBase( const char *pName, const char *pHelpString = 0, int flags = 0);
		virtual void				Init();
		void						Shutdown();
		char						*CopyString( const char *from );
	private:
		ConCommandBase_csgo				*m_pNext;
		bool						m_bRegistered;
		const char 					*m_pszName;
		const char 					*m_pszHelpString;
		int							m_nFlags;
	protected:
		static ConCommandBase_csgo		*s_pConCommandBases;
		static IConCommandBaseAccessor_csgo	*s_pAccessor;
	};

	class ConCommandBase
	{
		friend class CCvar;
		friend class ConVar;
		friend class ConCommand;
		friend void ConVar_Register(int nCVarFlag, IConCommandBaseAccessor *pAccessor);
		friend class CDefaultCvar;
	public:
		ConCommandBase(void);
		ConCommandBase(const char *pName, const char *pHelpString = 0, int flags = 0);
		virtual						~ConCommandBase(void);
		virtual	bool				IsCommand(void) const;
		virtual bool				IsFlagSet(int flag) const;
		virtual void				AddFlags(int flags);
		virtual const char			*GetName(void) const;
		virtual const char			*GetHelpText(void) const;
		const ConCommandBase		*GetNext(void) const;
		ConCommandBase				*GetNext(void);
		inline void SetNext(ConCommandBase *pBase)
		{
			m_pNext = pBase;
		}
		virtual bool				IsRegistered(void) const;
		virtual CVarDLLIdentifier_t	GetDLLIdentifier() const;
	protected:
		virtual void				Create(const char *pName, const char *pHelpString = 0,	int flags = 0);
		virtual void				Init();
		void						Shutdown();
		char						*CopyString(const char *from);
	private:
		ConCommandBase				*m_pNext;
		bool						m_bRegistered;
		const char 					*m_pszName;
		const char 					*m_pszHelpString;
		int							m_nFlags;
	protected:
		static ConCommandBase		*s_pConCommandBases;
		static IConCommandBaseAccessor	*s_pAccessor;
	};

	class CCommand
	{
	public:
		CCommand();
		CCommand( int nArgC, const char **ppArgV );
		bool Tokenize( const char *pCommand, characterset_t *pBreakSet = NULL );
		void Reset();
		int ArgC() const;
		const char **ArgV() const;
		const char *ArgS() const;
		const char *GetCommandString() const;
		const char *operator[]( int nIndex ) const;
		const char *Arg( int nIndex ) const;
		const char* FindArg( const char *pName ) const;
		int FindArgInt( const char *pName, int nDefaultVal ) const;
		static int MaxCommandLength();
		static characterset_t* DefaultBreakSet();
	private:
		enum
		{
			COMMAND_MAX_ARGC = 64,
			COMMAND_MAX_LENGTH = 512,
		};
		int		m_nArgc;
		int		m_nArgv0Size;
		char	m_pArgSBuffer[ COMMAND_MAX_LENGTH ];
		char	m_pArgvBuffer[ COMMAND_MAX_LENGTH ];
		const char*	m_ppArgv[ COMMAND_MAX_ARGC ];
	};

	inline int CCommand::MaxCommandLength()
	{
		return COMMAND_MAX_LENGTH - 1;
	}

	inline int CCommand::ArgC() const
	{
		return m_nArgc;
	}

	inline const char **CCommand::ArgV() const
	{
		return m_nArgc ? (const char**)m_ppArgv : NULL;
	}

	inline const char *CCommand::ArgS() const
	{
		return m_nArgv0Size ? &m_pArgSBuffer[m_nArgv0Size] : "";
	}

	inline const char *CCommand::GetCommandString() const
	{
		return m_nArgc ? m_pArgSBuffer : "";
	}

	inline const char *CCommand::Arg( int nIndex ) const
	{
		if ( nIndex < 0 || nIndex >= m_nArgc )
			return "";
		return m_ppArgv[nIndex];
	}

	inline const char *CCommand::operator[]( int nIndex ) const
	{
		return Arg( nIndex );
	}

	class ConCommand_csgo : public ConCommandBase_csgo
	{
	friend class CCvar;
	public:
		typedef ConCommandBase_csgo BaseClass;
		ConCommand_csgo( const char *pName, FnCommandCallbackV1_t callback, const char *pHelpString = 0, int flags = 0, FnCommandCompletionCallback completionFunc = 0 );
		ConCommand_csgo( const char *pName, FnCommandCallback_t callback, const char *pHelpString = 0, int flags = 0, FnCommandCompletionCallback completionFunc = 0 );
		ConCommand_csgo( const char *pName, ICommandCallback *pCallback, const char *pHelpString = 0, int flags = 0, ICommandCompletionCallback *pCommandCompletionCallback = 0 );
		virtual ~ConCommand_csgo( void );
		virtual	bool IsCommand( void ) const;
		virtual int AutoCompleteSuggest( const char *partial, CUtlVector< CUtlString > &commands );
		virtual bool CanAutoComplete( void );
		virtual void Dispatch( const CCommand &command );
	private:
		union
		{
			FnCommandCallbackV1_t m_fnCommandCallbackV1;
			FnCommandCallback_t m_fnCommandCallback;
			ICommandCallback *m_pCommandCallback; 
		};
		union
		{
			FnCommandCompletionCallback	m_fnCompletionCallback;
			ICommandCompletionCallback *m_pCommandCompletionCallback;
		};
		bool m_bHasCompletionCallback : 1;
		bool m_bUsingNewCommandCallback : 1;
		bool m_bUsingCommandCallbackInterface : 1;
	};

	class ConCommand : public ConCommandBase
	{
		friend class CCvar;
	public:
		typedef ConCommandBase BaseClass;
		ConCommand(const char *pName, FnCommandCallbackV1_t callback, const char *pHelpString = 0, int flags = 0, FnCommandCompletionCallback completionFunc = 0);
		ConCommand(const char *pName, FnCommandCallback_t callback,	const char *pHelpString = 0, int flags = 0, FnCommandCompletionCallback completionFunc = 0);
		ConCommand(const char *pName, ICommandCallback *pCallback, const char *pHelpString = 0, int flags = 0, ICommandCompletionCallback *pCommandCompletionCallback = 0);
		virtual ~ConCommand(void);
		virtual	bool IsCommand(void) const;
		virtual int AutoCompleteSuggest(const char *partial, CUtlVector< CUtlString > &commands);
		virtual bool CanAutoComplete(void);
		virtual void Dispatch(const CCommand &command);
	private:
		union
		{
			FnCommandCallbackV1_t m_fnCommandCallbackV1;
			FnCommandCallback_t m_fnCommandCallback;
			ICommandCallback *m_pCommandCallback;
		};
		union
		{
			FnCommandCompletionCallback	m_fnCompletionCallback;
			ICommandCompletionCallback *m_pCommandCompletionCallback;
		};
		bool m_bHasCompletionCallback : 1;
		bool m_bUsingNewCommandCallback : 1;
		bool m_bUsingCommandCallbackInterface : 1;
	};

	class ConVar_csgo : public ConCommandBase_csgo, public IConVar_csgo
	{
	friend class CCvar;
	friend class ConVarRef;
	friend class SplitScreenConVarRef;
	public:
		typedef ConCommandBase_csgo BaseClass;
									ConVar_csgo( const char *pName, const char *pDefaultValue, int flags = 0);
									ConVar_csgo( const char *pName, const char *pDefaultValue, int flags, const char *pHelpString );
									ConVar_csgo( const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax );
									ConVar_csgo( const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, FnChangeCallback_t callback );
									ConVar_csgo( const char *pName, const char *pDefaultValue, int flags, const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t callback );
		virtual						~ConVar_csgo( void );
		virtual bool				IsFlagSet( int flag ) const;
		virtual const char*			GetHelpText( void ) const;
		virtual bool				IsRegistered( void ) const;
		virtual const char			*GetName( void ) const;
		virtual const char			*GetBaseName( void ) const;
		virtual int					GetSplitScreenPlayerSlot() const;
		virtual void				AddFlags( int flags );
		virtual int					GetFlags() const;
		virtual	bool				IsCommand( void ) const;
		void InstallChangeCallback( FnChangeCallback_t callback, bool bInvoke = true );
		void RemoveChangeCallback( FnChangeCallback_t callbackToRemove );
		int GetChangeCallbackCount() const { return 0; }
		FnChangeCallback_t GetChangeCallback( int slot ) const { return NULL; }
		virtual float				GetFloat( void ) const;
		virtual int				GetInt( void ) const;
		inline Color			GetColor( void ) const;
		inline bool			GetBool() const {  return !!GetInt(); }
		inline char const	   *GetString( void ) const;
		template <typename T> T Get( void ) const;
		template <typename T> T Get( T * ) const;
		virtual void				SetValue( const char *value );
		virtual void				SetValue( float value );
		virtual void				SetValue( int value );
		virtual void				SetValue( Color value );
		void						Revert( void );
		bool						HasMin() const;
		bool						HasMax() const;
		bool						GetMin( float& minVal ) const;
		bool						GetMax( float& maxVal ) const;
		float						GetMinValue() const;
		float						GetMaxValue() const;
		const char					*GetDefault( void ) const;
		struct CVValue_t
		{
			char						*m_pszString;
			int							m_StringLength;
			float						m_fValue;
			int							m_nValue;
		};
		inline CVValue_t &GetRawValue()
		{
			return m_Value;
		}
		inline const CVValue_t &GetRawValue() const
		{
			return m_Value;
		}
	private:
		bool						InternalSetColorFromString( const char *value );
		virtual void				InternalSetValue(const char *value);
		virtual void				InternalSetFloatValue( float fNewValue );
		virtual void				InternalSetIntValue( int nValue );
		virtual void				InternalSetColorValue( Color value );
		virtual bool				ClampValue( float& value );
		virtual void				ChangeStringValue( const char *tempVal, float flOldValue );
		virtual void				Create( const char *pName, const char *pDefaultValue, int flags = 0, const char *pHelpString = 0, bool bMin = false, float fMin = 0.0, bool bMax = false, float fMax = false, FnChangeCallback_t callback = 0 );
		virtual void				Init();
	protected:
		ConVar_csgo						*m_pParent;
		const char					*m_pszDefaultValue;
		CVValue_t					m_Value;
		bool						m_bHasMin;
		float						m_fMinVal;
		bool						m_bHasMax;
		float						m_fMaxVal;
		CUtlVector< FnChangeCallbackCsgo_t > m_fnChangeCallbacks;
	};

	inline float ConVar_csgo::GetFloat( void ) const
	{
		return m_pParent->m_Value.m_fValue;
	}

	inline int ConVar_csgo::GetInt( void ) const
	{
		return m_pParent->m_Value.m_nValue;
	}

	inline Color ConVar_csgo::GetColor( void ) const
	{
		unsigned char *pColorElement = ((unsigned char *)&m_pParent->m_Value.m_nValue);
		return Color( pColorElement[0], pColorElement[1], pColorElement[2], pColorElement[3] );
	}

	template <> inline float			ConVar_csgo::Get<float>( void ) const		{ return GetFloat(); }
	template <> inline int			ConVar_csgo::Get<int>( void ) const			{ return GetInt(); }
	template <> inline bool			ConVar_csgo::Get<bool>( void ) const			{ return GetBool(); }
	template <> inline const char *	ConVar_csgo::Get<const char *>( void ) const	{ return GetString(); }
	template <> inline float			ConVar_csgo::Get<float>( float *p ) const				{ return ( *p = GetFloat() ); }
	template <> inline int			ConVar_csgo::Get<int>( int *p ) const					{ return ( *p = GetInt() ); }
	template <> inline bool			ConVar_csgo::Get<bool>( bool *p ) const					{ return ( *p = GetBool() ); }
	template <> inline const char *	ConVar_csgo::Get<const char *>( char const **p ) const	{ return ( *p = GetString() ); }

	inline const char *ConVar_csgo::GetString( void ) const
	{
		if ( m_nFlags & FCVAR_NEVER_AS_STRING )
			return "FCVAR_NEVER_AS_STRING";
		char const *str = m_pParent->m_Value.m_pszString;
		return str ? str : "";
	}

	class ConVar : public ConCommandBase, public IConVar
	{
		friend class CCvar;
		friend class ConVarRef;
	public:
		typedef ConCommandBase BaseClass;
		ConVar(const char *pName, const char *pDefaultValue, int flags = 0);
		ConVar(const char *pName, const char *pDefaultValue, int flags, const char *pHelpString);
		ConVar(const char *pName, const char *pDefaultValue, int flags,	const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax);
		ConVar(const char *pName, const char *pDefaultValue, int flags,	const char *pHelpString, FnChangeCallback_t callback);
		ConVar(const char *pName, const char *pDefaultValue, int flags,	const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t callback);
		virtual						~ConVar(void);
		virtual bool				IsFlagSet(int flag) const;
		virtual const char*			GetHelpText(void) const;
		virtual bool				IsRegistered(void) const;
		virtual const char			*GetName(void) const;
		virtual void				AddFlags(int flags);
		virtual	bool				IsCommand(void) const;
		void InstallChangeCallback(FnChangeCallback_t callback);
		inline float			GetFloat(void) const;
		inline int			GetInt(void) const;
		inline bool			GetBool() const { return !!GetInt(); }
		inline char const	   *GetString(void) const;
		virtual void				SetValue(const char *value);
		virtual void				SetValue(float value);
		virtual void				SetValue(int value);
		void						Revert(void);
		bool						GetMin(float& minVal) const;
		bool						GetMax(float& maxVal) const;
		const char					*GetDefault(void) const;
	private:
		virtual void				InternalSetValue(const char *value);
		virtual void				InternalSetFloatValue(float fNewValue);
		virtual void				InternalSetIntValue(int nValue);
		virtual bool				ClampValue(float& value);
		virtual void				ChangeStringValue(const char *tempVal, float flOldValue);
		virtual void				Create(const char *pName, const char *pDefaultValue, int flags = 0,	const char *pHelpString = 0, bool bMin = false, float fMin = 0.0, bool bMax = false, float fMax = false, FnChangeCallback_t callback = 0);
		virtual void				Init();
	private:
		ConVar						*m_pParent;
		const char					*m_pszDefaultValue;
		char						*m_pszString;
		int							m_StringLength;
		float						m_fValue;
		int							m_nValue;
		bool						m_bHasMin;
		float						m_fMinVal;
		bool						m_bHasMax;
		float						m_fMaxVal;
		FnChangeCallback_t			m_fnChangeCallback;
	};

	inline float ConVar::GetFloat(void) const
	{
		return m_pParent->m_fValue;
	}

	inline int ConVar::GetInt(void) const
	{
		return m_pParent->m_nValue;
	}

	inline const char *ConVar::GetString(void) const
	{
		if (m_nFlags & FCVAR_NEVER_AS_STRING)
			return "FCVAR_NEVER_AS_STRING";

		return (m_pParent->m_pszString) ? m_pParent->m_pszString : "";
	}

	void ConVar_Register_csgo( int nCVarFlag = 0, IConCommandBaseAccessor_csgo *pAccessor = nullptr );
	void ConVar_Register(int nCVarFlag = 0, IConCommandBaseAccessor *pAccessor = nullptr);
	void ConVar_Unregister( );
};

#endif // CONVAR_H
