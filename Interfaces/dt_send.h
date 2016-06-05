#ifndef SDK_DTSEND_H
#define SDK_DTSEND_H

#include "SdkPreprocessors.h"

namespace SourceSdk
{
	typedef enum
	{
		DPT_Int=0,
		DPT_Float,
		DPT_Vector,
		DPT_VectorXY,
		DPT_String,
		DPT_Array,
		DPT_DataTable,
		DPT_Int64,
		DPT_NUMSendPropTypes
	} SendPropType;

	class SendProp;
	class DVariant;
	class CSendProxyRecipients;

	typedef void (*SendVarProxyFn)( const SendProp *pProp, const void *pStructBase, const void *pData, DVariant *pOut, int iElement, int objectID );
	typedef void* (*SendTableProxyFn)(const SendProp *pProp, const void *pStructBase, const void *pData, CSendProxyRecipients *pRecipients,	int objectID);
	typedef int (*ArrayLengthSendProxyFn)( const void *pStruct, int objectID );

	class RecvProp;
	class SendTable;
	class CSendTablePrecalc;

	class SendProp_csgo
	{
	public:
							SendProp_csgo();
		virtual				~SendProp_csgo();
		void				Clear();
		int					GetOffset() const;
		void				SetOffset( int i );
		SendVarProxyFn		GetProxyFn() const;
		void				SetProxyFn( SendVarProxyFn f );
		SendTableProxyFn	GetDataTableProxyFn() const;
		void				SetDataTableProxyFn( SendTableProxyFn f );
		SendTable*			GetDataTable() const;
		void				SetDataTable( SendTable *pTable );
		char const*			GetExcludeDTName() const;
		const char*			GetParentArrayPropName() const;
		void				SetParentArrayPropName( char *pArrayPropName );
		const char*			GetName() const;
		bool				IsSigned() const;
		bool				IsExcludeProp() const;
		bool				IsInsideArray() const;
		void				SetInsideArray();
		void				SetArrayProp( SendProp_csgo *pProp );
		SendProp_csgo*			GetArrayProp() const;
		void					SetArrayLengthProxy( ArrayLengthSendProxyFn fn );
		ArrayLengthSendProxyFn	GetArrayLengthProxy() const;
		int					GetNumElements() const;
		void				SetNumElements( int nElements );
		int					GetNumArrayLengthBits() const;
		int					GetElementStride() const;
		SendPropType		GetType() const;
		int					GetFlags() const;
		void				SetFlags( int flags );	
		const void*			GetExtraData() const;
		void				SetExtraData( const void *pData );
		uint8_t 			GetPriority() const;
		void				SetPriority( uint8_t priority );
		int					GetNetworkVarFlags() const;
		bool				AreNetworkVarFlagsSet( int nFlags ) const;
		void				SetOffsetAndNetworkVarFlags( int nOffsetAndFlags );
	public:
		RecvProp		*m_pMatchingRecvProp;
		SendPropType	m_Type;
		int				m_nBits;
		float			m_fLowValue;
		float			m_fHighValue;
		SendProp_csgo		*m_pArrayProp;
		ArrayLengthSendProxyFn	m_ArrayLengthProxy;
		int				m_nElements;
		int				m_ElementStride;
		char *m_pExcludeDTName;
		char *m_pParentArrayPropName;
		char			*m_pVarName;
		float			m_fHighLowMul;
		uint8_t			m_priority;
	private:
		int					m_Flags;
		SendVarProxyFn		m_ProxyFn;
		SendTableProxyFn	m_DataTableProxyFn;	
		SendTable			*m_pDataTable;
		int					m_Offset;
		const void			*m_pExtraData;
	};


	inline int SendProp_csgo::GetOffset() const
	{
		return m_Offset & SENDPROP_OFFSET_MASK;
	}

	inline void SendProp_csgo::SetOffset( int nOffset )
	{
		m_Offset = nOffset;
	}

	inline void SendProp_csgo::SetOffsetAndNetworkVarFlags( int nOffset )
	{
		m_Offset = nOffset;
	}

	inline int SendProp_csgo::GetNetworkVarFlags() const
	{ 
		return m_Offset >> SENDPROP_NETWORKVAR_FLAGS_SHIFT; 
	}

	inline bool SendProp_csgo::AreNetworkVarFlagsSet( int nFlags ) const
	{
		return ( GetNetworkVarFlags() & nFlags ) == nFlags;
	}

	inline SendVarProxyFn SendProp_csgo::GetProxyFn() const
	{
		return m_ProxyFn; 
	}

	inline void SendProp_csgo::SetProxyFn( SendVarProxyFn f )
	{
		m_ProxyFn = f; 
	}

	inline SendTableProxyFn SendProp_csgo::GetDataTableProxyFn() const
	{
		return m_DataTableProxyFn; 
	}

	inline void SendProp_csgo::SetDataTableProxyFn( SendTableProxyFn f )
	{
		m_DataTableProxyFn = f; 
	}

	inline SendTable* SendProp_csgo::GetDataTable() const
	{
		return m_pDataTable;
	}

	inline void SendProp_csgo::SetDataTable( SendTable *pTable )
	{
		m_pDataTable = pTable; 
	}

	inline char const* SendProp_csgo::GetExcludeDTName() const
	{
		return m_pExcludeDTName; 
	}

	inline const char* SendProp_csgo::GetParentArrayPropName() const
	{
		return m_pParentArrayPropName;
	}

	inline void	SendProp_csgo::SetParentArrayPropName( char *pArrayPropName )
	{
		m_pParentArrayPropName = pArrayPropName;
	}

	inline const char* SendProp_csgo::GetName() const
	{
		return m_pVarName; 
	}

	inline bool SendProp_csgo::IsSigned() const
	{
		return !(m_Flags & SPROP_UNSIGNED); 
	}

	inline bool SendProp_csgo::IsExcludeProp() const
	{
		return (m_Flags & SPROP_EXCLUDE) != 0;
	}

	inline bool	SendProp_csgo::IsInsideArray() const
	{
		return (m_Flags & SPROP_INSIDEARRAY) != 0;
	}

	inline void SendProp_csgo::SetInsideArray()
	{
		m_Flags |= SPROP_INSIDEARRAY;
	}

	inline void SendProp_csgo::SetArrayProp( SendProp_csgo *pProp )
	{
		m_pArrayProp = pProp;
	}

	inline SendProp_csgo* SendProp_csgo::GetArrayProp() const
	{
		return m_pArrayProp;
	}
		 
	inline void SendProp_csgo::SetArrayLengthProxy( ArrayLengthSendProxyFn fn )
	{
		m_ArrayLengthProxy = fn;
	}

	inline ArrayLengthSendProxyFn SendProp_csgo::GetArrayLengthProxy() const
	{
		return m_ArrayLengthProxy;
	}
		 
	inline int SendProp_csgo::GetNumElements() const
	{
		return m_nElements; 
	}

	inline void SendProp_csgo::SetNumElements( int nElements )
	{
		m_nElements = nElements;
	}

	inline int SendProp_csgo::GetElementStride() const
	{
		return m_ElementStride; 
	}

	inline SendPropType SendProp_csgo::GetType() const
	{
		return m_Type; 
	}

	inline int SendProp_csgo::GetFlags() const
	{
		return m_Flags;
	}

	inline void SendProp_csgo::SetFlags( int flags )
	{
		m_Flags = flags;
	}

	inline const void* SendProp_csgo::GetExtraData() const
	{
		return m_pExtraData;
	}

	inline void SendProp_csgo::SetExtraData( const void *pData )
	{
		m_pExtraData = pData;
	}

	inline uint8_t SendProp_csgo::GetPriority() const
	{
		return m_priority;
	}

	inline void	SendProp_csgo::SetPriority(uint8_t priority )
	{
		m_priority = priority;
	}

	class SendProp
	{
	public:
		SendProp();
		virtual				~SendProp();
		void				Clear();
		int					GetOffset() const;
		void				SetOffset(int i);
		SendVarProxyFn		GetProxyFn() const;
		void				SetProxyFn(SendVarProxyFn f);
		SendTableProxyFn	GetDataTableProxyFn() const;
		void				SetDataTableProxyFn(SendTableProxyFn f);
		SendTable*			GetDataTable() const;
		void				SetDataTable(SendTable *pTable);
		char const*			GetExcludeDTName() const;
		const char*			GetParentArrayPropName();
		void				SetParentArrayPropName(const char *pArrayPropName);
		const char*			GetName() const;
		bool				IsSigned() const;
		bool				IsExcludeProp() const;
		bool				IsInsideArray() const;
		void				SetInsideArray();
		void				SetArrayProp(SendProp *pProp);
		SendProp*			GetArrayProp() const;
		void					SetArrayLengthProxy(ArrayLengthSendProxyFn fn);
		ArrayLengthSendProxyFn	GetArrayLengthProxy() const;
		int					GetNumElements() const;
		void				SetNumElements(int nElements);
		int					GetNumArrayLengthBits() const;
		int					GetElementStride() const;
		SendPropType		GetType() const;
		int					GetFlags() const;
		void				SetFlags(int flags);
		const void*			GetExtraData() const;
		void				SetExtraData(const void *pData);
	public:
		RecvProp		*m_pMatchingRecvProp;
		SendPropType	m_Type;
		int				m_nBits;
		float			m_fLowValue;
		float			m_fHighValue;
		SendProp		*m_pArrayProp;
		ArrayLengthSendProxyFn	m_ArrayLengthProxy;
		int				m_nElements;
		int				m_ElementStride;
		union
		{
			const char *m_pExcludeDTName;
			const char *m_pParentArrayPropName;
		};
		void			*m_pUnknown;
		const char		*m_pVarName;
		float			m_fHighLowMul;
	private:
		int					m_Flags;
		SendVarProxyFn		m_ProxyFn;
		SendTableProxyFn	m_DataTableProxyFn;
		SendTable			*m_pDataTable;
		int					m_Offset;
		const void			*m_pExtraData;
	};

	inline int SendProp::GetOffset() const
	{
		return m_Offset;
	}

	inline void SendProp::SetOffset(int i)
	{
		m_Offset = i;
	}

	inline SendVarProxyFn SendProp::GetProxyFn() const
	{
		return m_ProxyFn;
	}

	inline void SendProp::SetProxyFn(SendVarProxyFn f)
	{
		m_ProxyFn = f;
	}

	inline SendTableProxyFn SendProp::GetDataTableProxyFn() const
	{
		return m_DataTableProxyFn;
	}

	inline void SendProp::SetDataTableProxyFn(SendTableProxyFn f)
	{
		m_DataTableProxyFn = f;
	}

	inline SendTable* SendProp::GetDataTable() const
	{
		return m_pDataTable;
	}

	inline void SendProp::SetDataTable(SendTable *pTable)
	{
		m_pDataTable = pTable;
	}

	inline char const* SendProp::GetExcludeDTName() const
	{
		return m_pExcludeDTName;
	}

	inline const char* SendProp::GetParentArrayPropName()
	{
		return m_pParentArrayPropName;
	}

	inline void	SendProp::SetParentArrayPropName(const char *pArrayPropName)
	{
		m_pParentArrayPropName = pArrayPropName;
	}

	inline const char* SendProp::GetName() const
	{
		return m_pVarName;
	}

	inline bool SendProp::IsSigned() const
	{
		return !(m_Flags & SPROP_UNSIGNED);
	}

	inline bool SendProp::IsExcludeProp() const
	{
		return (m_Flags & SPROP_EXCLUDE) != 0;
	}

	inline bool	SendProp::IsInsideArray() const
	{
		return (m_Flags & SPROP_INSIDEARRAY) != 0;
	}

	inline void SendProp::SetInsideArray()
	{
		m_Flags |= SPROP_INSIDEARRAY;
	}

	inline void SendProp::SetArrayProp(SendProp *pProp)
	{
		m_pArrayProp = pProp;
	}

	inline SendProp* SendProp::GetArrayProp() const
	{
		return m_pArrayProp;
	}

	inline void SendProp::SetArrayLengthProxy(ArrayLengthSendProxyFn fn)
	{
		m_ArrayLengthProxy = fn;
	}

	inline ArrayLengthSendProxyFn SendProp::GetArrayLengthProxy() const
	{
		return m_ArrayLengthProxy;
	}

	inline int SendProp::GetNumElements() const
	{
		return m_nElements;
	}

	inline void SendProp::SetNumElements(int nElements)
	{
		m_nElements = nElements;
	}

	inline int SendProp::GetElementStride() const
	{
		return m_ElementStride;
	}

	inline SendPropType SendProp::GetType() const
	{
		return m_Type;
	}

	inline int SendProp::GetFlags() const
	{
		return m_Flags;
	}

	inline void SendProp::SetFlags(int flags)
	{
		m_Flags = flags;
	}

	inline const void* SendProp::GetExtraData() const
	{
		return m_pExtraData;
	}

	inline void SendProp::SetExtraData(const void *pData)
	{
		m_pExtraData = pData;
	}

	class SendTable
	{
	public:
		typedef SendProp PropType;
					SendTable();
					SendTable(PropType *pProps, int nProps, char *pNetTableName );
					~SendTable();
		void		Construct(PropType *pProps, int nProps, char *pNetTableName );
		const char*	GetName() const;
		int			GetNumProps() const;
#undef GetProp
		PropType*	GetProp( int i );
		bool		IsInitialized() const;
		void		SetInitialized( bool bInitialized );
		void		SetWriteFlag(bool bHasBeenWritten);
		bool		GetWriteFlag() const;
		bool		HasPropsEncodedAgainstTickCount() const;
		void		SetHasPropsEncodedAgainstTickcount( bool bState );
	public:
		PropType	*m_pProps;
		int			m_nProps;
		char		*m_pNetTableName;
		CSendTablePrecalc	*m_pPrecalc;
	protected:		
		bool		m_bInitialized : 1;	
		bool		m_bHasBeenWritten : 1;		
		bool		m_bHasPropsEncodedAgainstCurrentTickCount : 1;
	};


	inline const char* SendTable::GetName() const
	{
		return m_pNetTableName;
	}

	inline int SendTable::GetNumProps() const
	{
		return m_nProps;
	}

	inline SendTable::PropType* SendTable::GetProp( int i )
	{
		return &m_pProps[i];
	}

	inline bool SendTable::IsInitialized() const
	{
		return m_bInitialized;
	}

	inline void SendTable::SetInitialized( bool bInitialized )
	{
		m_bInitialized = bInitialized;
	}

	inline bool SendTable::GetWriteFlag() const
	{
		return m_bHasBeenWritten;
	}

	inline void SendTable::SetWriteFlag(bool bHasBeenWritten)
	{
		m_bHasBeenWritten = bHasBeenWritten;
	}

	inline bool SendTable::HasPropsEncodedAgainstTickCount() const
	{
		return m_bHasPropsEncodedAgainstCurrentTickCount;
	}

	inline void SendTable::SetHasPropsEncodedAgainstTickcount( bool bState )
	{
		m_bHasPropsEncodedAgainstCurrentTickCount = bState;
	}

	class SendTable_csgo
	{
	public:
		typedef SendProp_csgo PropType;
		SendTable_csgo();
		SendTable_csgo(PropType *pProps, int nProps, char *pNetTableName);
		~SendTable_csgo();
		void		Construct(PropType *pProps, int nProps, char *pNetTableName);
		const char*	GetName() const;
		int			GetNumProps() const;
#undef GetProp
		PropType*	GetProp(int i);
		bool		IsInitialized() const;
		void		SetInitialized(bool bInitialized);
		void		SetWriteFlag(bool bHasBeenWritten);
		bool		GetWriteFlag() const;
		bool		HasPropsEncodedAgainstTickCount() const;
		void		SetHasPropsEncodedAgainstTickcount(bool bState);
	public:
		PropType	*m_pProps;
		int			m_nProps;
		char		*m_pNetTableName;
		CSendTablePrecalc	*m_pPrecalc;
	protected:
		bool		m_bInitialized : 1;
		bool		m_bHasBeenWritten : 1;
		bool		m_bHasPropsEncodedAgainstCurrentTickCount : 1;
	};


	inline const char* SendTable_csgo::GetName() const
	{
		return m_pNetTableName;
	}

	inline int SendTable_csgo::GetNumProps() const
	{
		return m_nProps;
	}

	inline SendTable_csgo::PropType* SendTable_csgo::GetProp(int i)
	{
		return &m_pProps[i];
	}

	inline bool SendTable_csgo::IsInitialized() const
	{
		return m_bInitialized;
	}

	inline void SendTable_csgo::SetInitialized(bool bInitialized)
	{
		m_bInitialized = bInitialized;
	}

	inline bool SendTable_csgo::GetWriteFlag() const
	{
		return m_bHasBeenWritten;
	}

	inline void SendTable_csgo::SetWriteFlag(bool bHasBeenWritten)
	{
		m_bHasBeenWritten = bHasBeenWritten;
	}

	inline bool SendTable_csgo::HasPropsEncodedAgainstTickCount() const
	{
		return m_bHasPropsEncodedAgainstCurrentTickCount;
	}

	inline void SendTable_csgo::SetHasPropsEncodedAgainstTickcount(bool bState)
	{
		m_bHasPropsEncodedAgainstCurrentTickCount = bState;
	}
};

#endif // SDK_DTSEND_H