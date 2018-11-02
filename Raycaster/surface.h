#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "ray.h"

class material;

struct collisionData
{
	// Time along ray the collision occurs
	float t;
	// Point the collision occurs at
	rn::vector3f p;
	// Normal to the surface of the collision
	rn::vector3f normal;
	// Material of the surface hit
	material *mat;
};

// This name may be considered vague, but please try to think in terms of "implicit surfaces"
// i.e. a sphere would be: 
///							x^2 + y^2 + z^2 = R^2
class surface
{
public:
	// We create a purely virtual method ( no code of it's own ), this allows us to have classes that inherit and create their own function from this
	// As a note of clarification : If this was not a purely virtual method it would have it's own code
	virtual bool hit(const ray& r, float tMinimum, float tMaximum, collisionData& data) const = 0;
};

#endif