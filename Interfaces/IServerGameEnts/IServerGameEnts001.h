#ifndef ISERVERGAMEENTS001_H
#define ISERVERGAMEENTS001_H

namespace SourceSdk
{
	abstract_class IServerGameEnts001
	{
	public:
		virtual					~IServerGameEnts001()	{}
		virtual void			MarkEntitiesAsTouching( edict_t *e1, edict_t *e2 ) = 0;
		virtual void			FreeContainingEntity( edict_t * ) = 0; 
		virtual edict_t*		BaseEntityToEdict( CBaseEntity *pEnt ) = 0;
		virtual CBaseEntity*	EdictToBaseEntity( edict_t *pEdict ) = 0;
		virtual void			CheckTransmit( CCheckTransmitInfo *pInfo, const unsigned short *pEdictIndices, int nEdicts ) = 0;
		virtual void			PrepareForFullUpdate( edict_t *pEdict ) = 0;
	};
};

#endif // ISERVERGAMEENTS001_H
