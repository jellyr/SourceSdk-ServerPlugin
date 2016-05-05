#ifndef SDK_DATAMAP_H
#define SDK_DATAMAP_H

#include "SdkPreprocessors.h"

#include "../Containers/utlvector.h"

namespace SourceSdk
{
	struct inputdata_t;

	typedef void (CBaseEntity::*inputfunc_t)(inputdata_t &data);

	struct datamap_t;
	struct typedescription_t;
	class ISaveRestoreOps;

	enum
	{
		PC_NON_NETWORKED_ONLY = 0,
		PC_NETWORKED_ONLY,
		PC_COPYTYPE_COUNT,
		PC_EVERYTHING = PC_COPYTYPE_COUNT
	};

	enum
	{
		TD_OFFSET_NORMAL = 0,
		TD_OFFSET_PACKED = 1,
		TD_OFFSET_COUNT
	};
	
	typedef enum _fieldtypes
	{
		FIELD_VOID = 0,
		FIELD_FLOAT,
		FIELD_STRING,
		FIELD_VECTOR,
		FIELD_QUATERNION,
		FIELD_INTEGER,
		FIELD_BOOLEAN,
		FIELD_SHORT,
		FIELD_CHARACTER,
		FIELD_COLOR32,
		FIELD_EMBEDDED,
		FIELD_CUSTOM,
		FIELD_CLASSPTR,	
		FIELD_EHANDLE,
		FIELD_EDICT,
		FIELD_POSITION_VECTOR,
		FIELD_TIME,
		FIELD_TICK,
		FIELD_MODELNAME,
		FIELD_SOUNDNAME,
		FIELD_INPUT,
		FIELD_FUNCTION,
		FIELD_VMATRIX,
		FIELD_VMATRIX_WORLDSPACE,
		FIELD_MATRIX3X4_WORLDSPACE,
		FIELD_INTERVAL,
		FIELD_MODELINDEX,
		FIELD_MATERIALINDEX,
		FIELD_VECTOR2D,
		FIELD_INTEGER64,
		FIELD_VECTOR4D,
		FIELD_TYPECOUNT
	} fieldtype_t;

	struct typedescription_t
	{
		fieldtype_t			fieldType;
		const char			*fieldName;
		int					fieldOffset;
		unsigned short		fieldSize;
		short				flags;
		const char			*externalName;	
		ISaveRestoreOps		*pSaveRestoreOps; 
		inputfunc_t			inputFunc; 
		datamap_t			*td;
		int					fieldSizeInBytes;
		struct typedescription_t *override_field;
		int					override_count;
		float				fieldTolerance;
		int					flatOffset[ TD_OFFSET_COUNT ];
		unsigned short		flatGroup;
	};
	
	struct datarun_t
	{
		int m_nStartFlatField;
		int m_nEndFlatField;
		int m_nStartOffset[ TD_OFFSET_COUNT ];
		int m_nLength;
	};
	
	struct datacopyruns_t 
	{
		CUtlVector< datarun_t > m_vecRuns;
	};
	
	struct flattenedoffsets_t
	{
		CUtlVector< typedescription_t >	m_Flattened;
		int								m_nPackedSize;
		int								m_nPackedStartOffset;
	};
	
	struct datamapinfo_t
	{
		flattenedoffsets_t	m_Flat;
		datacopyruns_t		m_CopyRuns;
	};
	
	struct optimized_datamap_t
	{
		datamapinfo_t	m_Info[ PC_COPYTYPE_COUNT ];
	};
	
	struct datamap_t
	{
		typedescription_t	*dataDesc;
		int					dataNumFields;
		char const			*dataClassName;
		datamap_t			*baseMap;

		int					m_nPackedSize;
		optimized_datamap_t	*m_pOptimizedDataMap;
	};
};

#endif // SDK_DATAMAP_H