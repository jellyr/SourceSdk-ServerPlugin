#ifndef SDK_VECTOR_H
#define SDK_VECTOR_H

#include "SdkPreprocessors.h"

namespace SourceSdk
{
	struct Vector
	{
		vec_t x;
		vec_t y;
		vec_t z;

		vec_t make_me_128bits_struct;
	};
	
	struct Vector4D
	{
		vec_t x;
		vec_t y;
		vec_t z;
		vec_t w;
	};
	
	struct ALIGN16 VectorAligned : Vector
	{
	} ALIGN16_POST;
	
	typedef Vector QAngle;
	typedef VectorAligned QAngleAligned;
	
	bool VectorEqual(Vector const & a, Vector const & b);
	bool VectorEqual(Vector const * a, Vector const * b);
	void VectorClear(Vector & a);
	void VectorCopy(Vector const & a, Vector & b);
	void VectorCopy(Vector const * a, Vector * b);
	bool VectorIsZero(Vector const & a, vec_t tolerance = 0.01f);
	bool VectorIsZero(Vector const * a, vec_t tolerance = 0.01f);
	
	vec_t VectorMagnitudeSqr(Vector const & a);
	vec_t VectorMagnitudeSqr(Vector const * a);
	vec_t VectorMagnitude(Vector const & a);
	vec_t VectorMagnitude(Vector const * a);
	
	void VectorAdd(Vector const & a, Vector const & b, Vector & c);
	void VectorAdd(Vector const & a, Vector & b);
	void VectorAdd(Vector const * a, Vector const * b, Vector * c);
	void VectorAdd(Vector const * a, Vector * b);
	void VectorSub(Vector const & a, Vector const & b, Vector & c);
	void VectorSub(Vector const & a, Vector & b);
	void VectorSub(Vector const * a, Vector const * b, Vector * c);
	void VectorSub(Vector const * a, Vector * b);
	void VectorMultiply(Vector const & a, Vector const & b, Vector & c);
	void VectorMultiply(Vector const & a, Vector & b);
	void VectorMultiply(Vector const * a, Vector const * b, Vector * c);
	void VectorMultiply(Vector const * a, Vector * b);
	void VectorMultiply(Vector const & a, vec_t const b, Vector & c);
	void VectorMultiply(Vector & a, vec_t const b);
	void VectorMultiply(Vector const * a, vec_t const b, Vector * c);
	void VectorMultiply(Vector * a, vec_t const b);
	
	void VectorDistanceSqr(Vector const & a, Vector const & b, Vector & delta, vec_t & dst);
	void VectorDistanceSqr(Vector const & a, Vector const & b, vec_t & dst);
	void VectorDistanceSqr(Vector const * a, Vector const * b, Vector * delta, vec_t & dst);
	void VectorDistanceSqr(Vector const * a, Vector const * b, vec_t & dst);
	
	void VectorAbs(Vector const & a, Vector & b);
	void VectorAbs(Vector & a);
	void VectorAbs(Vector const * a, Vector * b);
	void VectorAbs(Vector * a);
	void VectorNorm(Vector const & a, Vector & b);
	void VectorNorm(Vector & a);
	void VectorNorm(Vector const * a, Vector * b);
	void VectorNorm(Vector * a);
	void VectorDotProduct(Vector const & a, Vector const & b, vec_t & c);
	void VectorDotProduct(Vector const * a, Vector const * b, vec_t & c);
	
	void AngleVectors(QAngle const & angles, Vector * forward, Vector * right, Vector * up);
	void AngleVectors(QAngle const & angles, Vector * forward, Vector * right);
	void AngleVectors(QAngle const & angles, Vector * forward);
	void VectorAngles(Vector const & forward, QAngle & angles);
};

#endif
