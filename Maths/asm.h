#ifndef SDK_MATHSASM_H
#define SDK_MATHSASM_H

namespace SourceSdk
{
	void inline SinCos( float radians, float *sine, float *cosine )
	{
	#ifdef WIN32
		_asm
		{
			fld		DWORD PTR [radians]
			fsincos

			mov edx, DWORD PTR [cosine]
			mov eax, DWORD PTR [sine]

			fstp DWORD PTR [edx]
			fstp DWORD PTR [eax]
		}
	#else
		double __cosr, __sinr;
		__asm ("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (radians));

		*sine = __sinr;
		*cosine = __cosr;
	#endif
	}
};

#endif // SDK_MATHSASM_H