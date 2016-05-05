#ifndef SDK_COLOR
#define SDK_COLOR

#include "SdkPreprocessors.h"

namespace SourceSdk
{
	struct Color
	{
		unsigned char _color[4];

		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
		{
			_color[0] = r;
			_color[1] = g;
			_color[2] = b;
			_color[3] = a;
		}
	};
};

#endif
