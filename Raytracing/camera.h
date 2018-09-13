#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ray.h"

class camera {
public:
	rn::vector3f lowerLeftCorner;
	rn::vector3f horizontal;
	rn::vector3f vertical;
	rn::vector3f origin;

	camera() {
		lowerLeftCorner = rn::vector3f(-2.0, -1.0, -1.0);
		horizontal		= rn::vector3f(4.0, 0.0, 0.0);
		vertical		= rn::vector3f(0.0, 2.0, 0.0);
		origin			= rn::vector3f(0.0, 0.0, 0.0);
	}

	ray getRay(float u, float v)
	{
		return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}
};

#endif