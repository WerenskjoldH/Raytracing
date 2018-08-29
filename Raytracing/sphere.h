#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "hitable.h"

class sphere : public hitable {
public:
	rn::vector3f center;
	float radius;

	sphere() {}
	sphere(rn::vector3f center, float radius) :center(center), radius(radius) {}
	~sphere() {}
	
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const;
};

// Note: "const" keyword prevents modification to the object who's function is called
bool sphere::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const {
	rn::vector3f originToCenter = r.origin() - center;
	float a = rn::dot(r.direction(), r.direction());
	float b = 2.0 * rn::dot(originToCenter, r.direction());
	float c = rn::dot(originToCenter, originToCenter) - radius * radius;
	// If the discriminant ( b^2 - 4ac ) is 0 then we know the polynomial has a double root, and if it is possitive it has two real roots
	float discriminant = b * b - 4 * a*c;
	if (discriminant > 0)
	{
		// We have to check + and - 
		float temp = (-b - sqrt(b * b - 4*a * c)) / (2*a);
		if (temp < tMax && temp > tMin)
		{
			// Time along the ray the collision occurs
			rec.t = temp;
			// Point of collision
			rec.p = r.pointAt(temp);
			// This ~should~ return a unit vector out of the surface of the sphere
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(b * b - 4* a * c)) / (2*a);
		if (temp < tMax && temp > tMin)
		{
			rec.t = temp;
			rec.p = r.pointAt(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}

#endif