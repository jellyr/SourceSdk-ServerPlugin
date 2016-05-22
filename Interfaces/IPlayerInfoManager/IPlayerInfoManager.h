#ifndef IPLAYERINFOMANAGER_H
#define IPLAYERINFOMANAGER_H

#include "SdkPreprocessors.h"

#include "../edict.h"
#include "../../Maths/Vector.h"

namespace SourceSdk
{
	struct CBotCmd
	{
		int		command_number;
		int		tick_count;
		QAngle	viewangles;     
		float	forwardmove;   
		float	sidemove;      
		float	upmove;         
		int		buttons;		
		uint8_t    impulse;        
		int		weaponselect;	
		int		weaponsubtype;
		int		random_seed;
		short	mousedx;
		short	mousedy;
	};

	abstract_class IPlayerInfo
	{
	public:
		virtual const char *GetName() = 0;
		virtual int		GetUserID() = 0;
		virtual const char *GetNetworkIDString() = 0;
		virtual int GetTeamIndex() = 0;
		virtual void ChangeTeam( int iTeamNum ) = 0;
		virtual int	GetFragCount() = 0;
		virtual int	GetDeathCount() = 0;
		virtual bool IsConnected() = 0;
		virtual int	GetArmorValue() = 0;
		virtual bool IsHLTV() = 0;
		virtual bool IsPlayer() = 0;
		virtual bool IsFakeClient() = 0;
		virtual bool IsDead() = 0;
		virtual bool IsInAVehicle() = 0;
		virtual bool IsObserver() = 0;
		virtual const Vector GetAbsOrigin() = 0;
		virtual const QAngle GetAbsAngles() = 0;
		virtual const Vector GetPlayerMins() = 0;
		virtual const Vector GetPlayerMaxs() = 0;
		virtual const char *GetWeaponName() = 0;
		virtual const char *GetModelName() = 0;
		virtual const int GetHealth() = 0;
		virtual const int GetMaxHealth() = 0;
		virtual CBotCmd GetLastUserCommand() = 0;
		virtual bool IsReplay() = 0;
	};

	abstract_class IPlayerInfo_csgo
	{
	public:
		virtual const char *GetName() = 0;
		virtual int		GetUserID() = 0;
		virtual const char *GetNetworkIDString() = 0;
		virtual int GetTeamIndex() = 0;
		virtual void ChangeTeam( int iTeamNum ) = 0;
		virtual int	GetFragCount() = 0;
		virtual int	GetDeathCount() = 0;
		virtual bool IsConnected() = 0;
		virtual int	GetArmorValue() = 0;
		virtual bool IsHLTV() = 0;
		//virtual bool IsReplay() = 0;
		virtual bool IsPlayer() = 0;
		virtual bool IsFakeClient() = 0;
		virtual bool IsDead() = 0;
		virtual bool IsInAVehicle() = 0;
		virtual bool IsObserver() = 0;
		virtual const Vector GetAbsOrigin() = 0;
		virtual const QAngle GetAbsAngles() = 0;
		virtual const Vector GetPlayerMins() = 0;
		virtual const Vector GetPlayerMaxs() = 0;
		virtual const char *GetWeaponName() = 0;
		virtual const char *GetModelName() = 0;
		virtual const int GetHealth() = 0;
		virtual const int GetMaxHealth() = 0;
		virtual CBotCmd GetLastUserCommand() = 0;
	};
};

#include "IPlayerInfoManager002.h"

#endif // IPLAYERINFOMANAGER_H