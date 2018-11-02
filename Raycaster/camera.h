#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ray.h"

class camera
{
public:
	/// We will leave these publically exposed for now
	// Lower left corner of the viewport
	rn::vector3f lowerLeft;
	// How far do we expand right from the corner
	rn::vector3f horizontalDistance;
	// How far do we expand up from the corner
	rn::vector3f verticalDistance;
	// Position of the camera
	rn::vector3f origin;

	// Constructs our camera
	camera(rn::vector3f _lowerLeft, rn::vector3f _horizontalDistance, rn::vector3f _verticalDistance, rn::vector3f _origin)
	{
		lowerLeft = _lowerLeft;
		horizontalDistance = _horizontalDistance;
		verticalDistance = _verticalDistance;
		origin = _origin;
	}

	// Get the ray requested in the camera's view
	ray getRay(float u, float v)
	{
		// Pass the ray the origin, 
		return ray(origin, lowerLeft + u * horizontalDistance + v * verticalDistance - origin);
	}

};

#endif