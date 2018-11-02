#ifndef _RAY_H_
#define _RAY_H_

#include "vector.h"

class ray
{
public:
	// Should be a point in space
	rn::vector3f o;
	// Should be a unit vector
	rn::vector3f d;
	
	// Initialize the ray
	ray() {}
	ray(const rn::vector3f& _origin, const rn::vector3f& _direction)
	{
		o = _origin;
		d = _direction;
	}

	rn::vector3f origin() const
	{
		return o;
	}

	rn::vector3f direction() const
	{
		return d;
	}

	// Returns the point along the ray given a "time" input
	rn::vector3f getPointAt(float t) const
	{
		return o + t * d;
	}

};

#endif