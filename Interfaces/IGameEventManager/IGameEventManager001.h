#ifndef IGAMEEVENTMANAGER001_H
#define IGAMEEVENTMANAGER001_H

abstract_class IGameEventListener001
{
public:
	virtual	~IGameEventListener( void ) {};
	virtual void FireGameEvent( KeyValues * event) = 0;
};

abstract_class IGameEventManager001 : public IBaseInterface
{
public:
	virtual	~IGameEventManager( void ) {};
	virtual int LoadEventsFromFile( const char * filename ) = 0;
	virtual void  Reset() = 0;	
	virtual KeyValues *GetEvent(const char * name) = 0;
	virtual bool AddListener( IGameEventListener * listener, const char * event, bool bIsServerSide ) = 0;
	virtual bool AddListener( IGameEventListener * listener, bool bIsServerSide ) = 0; 
	virtual void RemoveListener( IGameEventListener * listener) = 0;
	virtual bool FireEvent( KeyValues * event ) = 0;
	virtual bool FireEventServerOnly( KeyValues * event ) = 0;
	virtual bool FireEventClientOnly( KeyValues * event ) = 0;
	virtual bool SerializeKeyValues( KeyValues *event, bf_write *buf, CGameEvent *eventtype = NULL ) = 0;
	virtual KeyValues *UnserializeKeyValue( bf_read *msg ) = 0;
};

#endif // IGAMEEVENTMANAGER001_H
