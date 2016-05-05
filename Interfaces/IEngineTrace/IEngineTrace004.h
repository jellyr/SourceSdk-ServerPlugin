#ifndef IENGINETRACE004
#define IENGINETRACE004

namespace SourceSdk
{
	abstract_class IEngineTrace004
	{
	public:
		virtual int		GetPointContents( const Vector &vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = NULL ) = 0;
		virtual int		GetPointContents_WorldOnly( const Vector &vecAbsPosition, int contentsMask = MASK_ALL ) = 0;
		virtual int		GetPointContents_Collideable( ICollideable *pCollide, const Vector &vecAbsPosition ) = 0;
		virtual void	ClipRayToEntity( const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace ) = 0;
		virtual void	ClipRayToCollideable( const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, trace_t *pTrace ) = 0;
		virtual void	TraceRay( const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace ) = 0;
		virtual void	SetupLeafAndEntityListRay( const Ray_t &ray, ITraceListData *pTraceData ) = 0;
		virtual void    SetupLeafAndEntityListBox( const Vector &vecBoxMin, const Vector &vecBoxMax, ITraceListData *pTraceData ) = 0;
		virtual void	TraceRayAgainstLeafAndEntityList( const Ray_t &ray, ITraceListData *pTraceData, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace ) = 0;
		virtual void	SweepCollideable( ICollideable *pCollide, const Vector &vecAbsStart, const Vector &vecAbsEnd, 
			const QAngle &vecAngles, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace ) = 0;
		virtual void	EnumerateEntities( const Ray_t &ray, bool triggers, IEntityEnumerator *pEnumerator ) = 0;
		virtual void	EnumerateEntities( const Vector &vecAbsMins, const Vector &vecAbsMaxs, IEntityEnumerator *pEnumerator ) = 0;
		virtual ICollideable *GetCollideable( IHandleEntity *pEntity ) = 0;
		virtual int GetStatByIndex( int index, bool bClear ) = 0;
		virtual void GetBrushesInAABB( const Vector &vMins, const Vector &vMaxs, CUtlVector<int> *pOutput, int iContentsMask = 0xFFFFFFFF ) = 0;
		virtual CPhysCollide* GetCollidableFromDisplacementsInAABB( const Vector& vMins, const Vector& vMaxs ) = 0;
		virtual int GetNumDisplacements( ) = 0;
		virtual void GetDisplacementMesh( int nIndex, virtualmeshlist_t *pMeshTriList ) = 0;
		virtual bool GetBrushInfo( int iBrush, CUtlVector<BrushSideInfo_t> *pBrushSideInfoOut, int *pContentsOut ) = 0;
		virtual bool PointOutsideWorld( const Vector &ptTest ) = 0;
		virtual int GetLeafContainingPoint( const Vector &ptTest ) = 0;
		virtual ITraceListData *AllocTraceListData() = 0;
		virtual void FreeTraceListData(ITraceListData *) = 0;
		virtual int GetSetDebugTraceCounter( int value, DebugTraceCounterBehavior_t behavior ) = 0;
	};
};

#endif // IENGINETRACE004
