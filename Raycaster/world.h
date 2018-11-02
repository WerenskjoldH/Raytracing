#ifndef _WORLD_H_
#define _WORLD_H_

#include "surface.h"

class world
{
public:
	surface** list;
	int surfacesInList = 0;

	world() {}

	// A list of surface pointers is passed in
	world(surface** l, int n)
	{
		list = l;
		surfacesInList = n;
	}

	// Deconstructor for the world data
	~world()
	{
		int x;
		for (x = 0; x < surfacesInList; x++)
			delete list[x];
	}
	
	// Essentially the hit function from surface class
	bool checkCollision(const ray& r, float tMinimum, float tMaximum, collisionData& data) const;
};

// Essentially the hit function from surface class
bool world::checkCollision(const ray& r, float tMinimum, float tMaximum, collisionData& data) const
{
	collisionData tempData;
	bool hitDetected = 0;
	// Set to the max distance we will look
	float closestSurface = tMaximum;
	// Loop through the list and see if any of the surfaces in the scene are hit by the casted ray, and if so pass back the information
	for (int i = 0; i < surfacesInList; i++)
	{
		if (list[i]->hit(r, tMinimum, closestSurface, tempData)) {
			hitDetected = 1;
			closestSurface = tempData.t;
			data = tempData;
		}
	}
	return hitDetected;
}

#endif