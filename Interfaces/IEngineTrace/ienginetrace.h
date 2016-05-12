#ifndef IENGINETRACE_H
#define IENGINETRACE_H

#include <limits>

#include "SdkPreprocessors.h"

#include "../bspflags.h"
#include "../../Maths/Vector.h"
#include "../../Containers/utlvector.h"

namespace SourceSdk
{
	class IHandleEntity;
	class ICollideable;
	class ITraceListData;
	class CPhysCollide;
	class virtualmeshlist_t;
	struct matrix3x4_t;
	class CBaseEntity;

	struct Ray_t
	{
		VectorAligned  m_Start;
		VectorAligned  m_Delta;
		VectorAligned  m_StartOffset;
		VectorAligned  m_Extents;
		const matrix3x4_t *m_pWorldAxisTransform;
		bool	m_IsRay;
		bool	m_IsSwept;

		Ray_t() : m_pWorldAxisTransform( NULL )	{}

		void Init( Vector const& start, Vector const& end )
		{
			VectorSub( end, start, m_Delta );
			m_IsSwept = (VectorMagnitudeSqr(m_Delta) != 0);
			memset(&m_StartOffset, 0, 2 * sizeof(VectorAligned) + sizeof(matrix3x4_t*));
			m_IsRay = true;
			VectorCopy( start, m_Start );
		}

		void Init( Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs )
		{
			VectorSub( end, start, m_Delta );
			m_pWorldAxisTransform = NULL;
			m_IsSwept = (VectorMagnitudeSqr(m_Delta) != 0);
			VectorSub( maxs, mins, m_Extents );
			VectorMultiply(m_Extents, 0.5);
			m_IsRay = (VectorMagnitudeSqr(m_Extents) < 1e-6);
			VectorAdd( mins, maxs, m_StartOffset );
			VectorMultiply(m_StartOffset, 0.5);
			VectorAdd( start, m_StartOffset, m_Start );
			VectorMultiply(m_StartOffset, -1.0);
		}

		Vector InvDelta() const
		{
			Vector vecInvDelta;
			if(m_Delta.x) vecInvDelta.x = 1.0f / m_Delta.x;
			else vecInvDelta.x = std::numeric_limits<vec_t>::max();
			if(m_Delta.y) vecInvDelta.y = 1.0f / m_Delta.y;
			else vecInvDelta.y = std::numeric_limits<vec_t>::max();
			if(m_Delta.z) vecInvDelta.z = 1.0f / m_Delta.z;
			else vecInvDelta.z = std::numeric_limits<vec_t>::max();
			return vecInvDelta;
		}

	private:
	};

	struct cplane_t
	{
		Vector	normal;
		float	dist;
		uint8_t	type;
		uint8_t	signbits;
		uint8_t	pad[2];
		cplane_t() {}
	private:
		cplane_t(const cplane_t& vOther);
	};

	class CBaseTrace
	{
	public:
		bool IsDispSurface( void )				{ return ( ( dispFlags & DISPSURF_FLAG_SURFACE ) != 0 ); }
		bool IsDispSurfaceWalkable( void )		{ return ( ( dispFlags & DISPSURF_FLAG_WALKABLE ) != 0 ); }
		bool IsDispSurfaceBuildable( void )		{ return ( ( dispFlags & DISPSURF_FLAG_BUILDABLE ) != 0 ); }
		bool IsDispSurfaceProp1( void )			{ return ( ( dispFlags & DISPSURF_FLAG_SURFPROP1 ) != 0 ); }
		bool IsDispSurfaceProp2( void )			{ return ( ( dispFlags & DISPSURF_FLAG_SURFPROP2 ) != 0 ); }
	public:
		Vector			startpos;
		Vector			endpos;
		cplane_t		plane;
		float			fraction;
		int				contents;
		unsigned short	dispFlags;
		bool			allsolid;
		bool			startsolid;
		CBaseTrace() {}
	private:
		CBaseTrace(const CBaseTrace& vOther);
	};

	struct csurface_t
	{
		const char	*name;
		short		surfaceProps;
		unsigned short	flags;
	};

	class CGameTrace : public CBaseTrace
	{
	public:
		bool DidHitWorld() const;
		bool DidHitNonWorldEntity() const;
		int GetEntityIndex() const;
		bool DidHit() const;
	public:
		float			fractionleftsolid;
		csurface_t		surface;
		int				hitgroup;
		short			physicsbone;
		unsigned short	worldSurfaceIndex;
		CBaseEntity *m_pEnt;
		int			hitbox;
		CGameTrace() {}
	private:
		CGameTrace(const CGameTrace& vOther);
	};

	inline bool CGameTrace::DidHit() const 
	{ 
		return fraction < 1 || allsolid || startsolid; 
	}

	typedef CGameTrace trace_t;

	enum TraceType_t
	{
		TRACE_EVERYTHING = 0,
		TRACE_WORLD_ONLY,
		TRACE_ENTITIES_ONLY,
		TRACE_EVERYTHING_FILTER_PROPS,
	};

	abstract_class ITraceFilter
	{
	public:
		virtual bool ShouldHitEntity( IHandleEntity *pEntity, int contentsMask ) = 0;
		virtual TraceType_t	GetTraceType() const = 0;
	};

	class CTraceFilter : public ITraceFilter
	{
	public:
		virtual TraceType_t	GetTraceType() const
		{
			return TRACE_EVERYTHING;
		}
	};

	class CTraceFilterEntitiesOnly : public ITraceFilter
	{
	public:
		virtual TraceType_t	GetTraceType() const
		{
			return TRACE_ENTITIES_ONLY;
		}
	};

	class CTraceFilterWorldOnly : public ITraceFilter
	{
	public:
		bool ShouldHitEntity( IHandleEntity *pServerEntity, int contentsMask )
		{
			return false;
		}
		virtual TraceType_t	GetTraceType() const
		{
			return TRACE_WORLD_ONLY;
		}
	};

	class CTraceFilterWorldAndPropsOnly : public ITraceFilter
	{
	public:
		bool ShouldHitEntity( IHandleEntity *pServerEntity, int contentsMask )
		{
			return false;
		}
		virtual TraceType_t	GetTraceType() const
		{
			return TRACE_EVERYTHING;
		}
	};

	class CTraceFilterHitAll : public CTraceFilter
	{
	public:
		virtual bool ShouldHitEntity( IHandleEntity *pServerEntity, int contentsMask )
		{ 
			return true; 
		}
	};

	enum DebugTraceCounterBehavior_t
	{
		kTRACE_COUNTER_SET = 0,
		kTRACE_COUNTER_INC,
	};

	abstract_class IEntityEnumerator
	{
	public:
		virtual bool EnumEntity( IHandleEntity *pHandleEntity ) = 0; 
	};

	struct BrushSideInfo_t
	{
		Vector4D plane;
		unsigned short bevel;
		unsigned short thin;
	};

	enum IterationRetval_t
	{
		ITERATION_CONTINUE = 0,
		ITERATION_STOP,
	};

	class IPartitionEnumerator
	{
	public:
		virtual IterationRetval_t EnumElement(IHandleEntity *pHandleEntity) = 0;
	};

	class CTraceListData : public IPartitionEnumerator
	{
	public:

		CTraceListData(int nLeafMax = TLD_DEF_LEAF_MAX, int nEntityMax = TLD_DEF_ENTITY_MAX)
		{
			m_nLeafCount = 0;
			m_aLeafList.SetSize(nLeafMax);
			m_nEntityCount = 0;
			m_aEntityList.SetSize(nEntityMax);
		}

		~CTraceListData()
		{
			m_nLeafCount = 0;
			m_aLeafList.RemoveAll();
			m_nEntityCount = 0;
			m_aEntityList.RemoveAll();
		}

		void Reset(void)
		{
			m_nLeafCount = 0;
			m_nEntityCount = 0;
		}

		bool	IsEmpty(void) const { return (m_nLeafCount == 0 && m_nEntityCount == 0); }
		int		LeafCount(void) const { return m_nLeafCount; }
		int		LeafCountMax(void) const { return m_aLeafList.Count(); }
		void    LeafCountReset(void) { m_nLeafCount = 0; }
		int		EntityCount(void) const { return m_nEntityCount; }
		int		EntityCountMax(void) const { return m_aEntityList.Count(); }
		void	EntityCountReset(void) { m_nEntityCount = 0; }

		void AddLeaf(int iLeaf)
		{
			if (m_nLeafCount >= m_aLeafList.Count())
			{
				m_aLeafList.AddMultipleToTail(m_aLeafList.Count());
			}
			m_aLeafList[m_nLeafCount] = iLeaf;
			m_nLeafCount++;
		}

		IterationRetval_t EnumElement(IHandleEntity *pHandleEntity)
		{
			if (m_nEntityCount >= m_aEntityList.Count())
			{
				m_aEntityList.AddMultipleToTail(m_aEntityList.Count());
			}
			m_aEntityList[m_nEntityCount] = pHandleEntity;
			m_nEntityCount++;
			return ITERATION_CONTINUE;
		}
	public:
		int							m_nLeafCount;
		CUtlVector<int>				m_aLeafList;
		int							m_nEntityCount;
		CUtlVector<IHandleEntity*>	m_aEntityList;
	};
};

#include "IEngineTrace003.h"
#include "IEngineTrace004.h"

#endif // IENGINETRACE_H
