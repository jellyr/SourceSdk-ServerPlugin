#ifndef CUSERCMD_H
#define CUSERCMD_H

#include "SdkPreprocessors.h"

#include "../Maths/Vector.h"

namespace SourceSdk
{
	class CEntityGroundContact
	{
	public:
		int					entindex;
		float				minheight;
		float				maxheight;
	};

	class CUserCmd
	{
	public:
		CUserCmd()
		{
		}
		virtual ~CUserCmd() { };
		CUserCmd& operator =(const CUserCmd& src)
		{
			if (this == &src)
				return *this;

			memcpy(this, &src, sizeof(CUserCmd));

			return *this;
		}
		CUserCmd(const CUserCmd& src)
		{
			*this = src;
		}
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
};

 #endif // CUSERCMD_H