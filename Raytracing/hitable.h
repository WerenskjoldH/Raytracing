#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "ray.h"

struct hitRecord {
	float t;
	rn::vector3f p;
	rn::vector3f normal;
};

class hitable {
public:
	// Create a purely virtual method ( has no code of it's own ), this lets us have dynamic classes that inherit from this
	// Note: If it was not purely virtual it would run code of its own
	virtual bool hit(const ray& ray, float tMin, float tMax, hitRecord& rec) const = 0;

};

#endif