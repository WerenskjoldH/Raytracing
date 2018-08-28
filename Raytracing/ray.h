#ifndef _RAY_H_
#define _RAY_H_
#include "vector.h"

class ray
{
public:
	rn::vector3f A, B;

	ray() {}
	ray(const rn::vector3f& a, const rn::vector3f& b)
	{
		A = a;
		B = b;
	}

	rn::vector3f origin() const
	{
		return A;
	}

	rn::vector3f direction() const
	{
		return B;
	}

	rn::vector3f pointAt(float t) const
	{
		return A + t * B;
	}
};


#endif