#ifndef _HITABLE_LIST_H_
#define _HITABLE_LIST_H_

#include "hitable.h"

class hitableList : public hitable {
public:
	hitableList() {}

	hitableList(hitable **l, int n) {
		list = l;
		listSize = n;
	}

	~hitableList()
	{
		int x;
		for (x = 0; x < listSize; x++)
		{
			delete list[x];
		}
	}

	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const;
	hitable** list;
	int listSize;
};

// Note:: Typically this would belong in a .cpp file, but to keep compression we place it with the header
bool hitableList::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const {
	hitRecord tempRec;
	bool hitDetected = 0;
	// Set to the max distance we will look
	float closestHitable = tMax;
	// Loop through the list and see if any of the objects in the scene are hit by the casted ray, and if so pass back the information
	for (int i = 0; i < listSize; i++)
	{
		if (list[i]->hit(r, tMin, closestHitable, tempRec)) {
			hitDetected = 1;
			closestHitable = tempRec.t;
			rec = tempRec;
		}
	}
	return hitDetected;
}

#endif