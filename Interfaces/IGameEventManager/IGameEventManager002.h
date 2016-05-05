#ifndef IGAMEEVENTMANAGER002_H
#define IGAMEEVENTMANAGER002_H

namespace SourceSdk
{
	abstract_class IGameEventListener002_BASE
	{
	public:
		virtual	~IGameEventListener002_BASE( void ) {};
		virtual void FireGameEvent( IGameEvent *event ) = 0;
		virtual int	 GetEventDebugID( void ) = 0;
	};

	class IGameEventListener002 : public IGameEventListener002_BASE
	{
	public:
		IGameEventListener002()
		{
			m_debugid = EVENT_DEBUG_ID_INIT;
		};
		virtual ~IGameEventListener002()
		{
			m_debugid = EVENT_DEBUG_ID_SHUTDOWN;
		};

		virtual void FireGameEvent(IGameEvent* ev) = 0;

		virtual int GetEventDebugID()
		{
			return m_debugid;
		};

	private:
		int m_debugid;
	};

	abstract_class IGameEventManager002 : public IBaseInterface
	{
	public:
		virtual	~IGameEventManager002( void ) {};
		virtual int LoadEventsFromFile( const char *filename ) = 0;
		virtual void  Reset() = 0;	
		virtual bool AddListener( IGameEventListener002 *listener, const char *name, bool bServerSide ) = 0;
		virtual bool FindListener( IGameEventListener002 *listener, const char *name ) = 0;
		virtual void RemoveListener( IGameEventListener002 *listener) = 0;
		virtual IGameEvent *CreateEvent( const char *name, bool bForce = false, int *pCookie = NULL ) = 0;
		virtual bool FireEvent( IGameEvent *event, bool bDontBroadcast = false ) = 0;
		virtual bool FireEventClientSide( IGameEvent *event ) = 0;
		virtual IGameEvent *DuplicateEvent( IGameEvent *event ) = 0;
		virtual void FreeEvent( IGameEvent *event ) = 0;
		virtual bool SerializeEvent( IGameEvent *event, bf_write *buf ) = 0;
		virtual IGameEvent *UnserializeEvent( bf_read *buf ) = 0;
	};
};

#endif // IGAMEEVENTMANAGER002_H
