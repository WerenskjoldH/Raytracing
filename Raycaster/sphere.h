#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "surface.h"

class sphere : public surface {
public:
	rn::vector3f center;
	material *mat;
	float radius;

	sphere() {}
	sphere(rn::vector3f center, float radius, material* matPtr) :center(center), radius(radius), mat(matPtr) {}
	~sphere() {}

	virtual bool hit(const ray& r, float tMinimum, float tMaximum, collisionData& data) const override;
};

// Note: "const" keyword prevents modification to the object who's function is called
bool sphere::hit(const ray& r, float tMinimum, float tMaximum, collisionData& data) const {
	rn::vector3f originToCenter = r.origin() - center;
	float a = rn::dot(r.direction(), r.direction());
	float b = 2.0 * rn::dot(originToCenter, r.direction());
	float c = rn::dot(originToCenter, originToCenter) - radius * radius;
	// If the discriminant ( b^2 - 4ac ) is 0 then we know the polynomial has a double root, and if it is possitive it has two real roots
	float discriminant = b * b - 4 * a*c;
	if (discriminant > 0)
	{
		// We have to check + and - 
		float temp = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (temp < tMaximum && temp > tMinimum)
		{
			// Time along the ray the collision occurs
			data.t = temp;
			// Point of collision
			data.p = r.getPointAt(temp);
			// This ~should~ return a unit vector out of the surface of the sphere
			data.normal = (data.p - center) / radius;
			// Returns the surface material that the ray hit
			data.mat = mat;
			return true;
		}
		temp = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		if (temp < tMaximum && temp > tMinimum)
		{
			data.t = temp;
			data.p = r.getPointAt(temp);
			data.normal = (data.p - center) / radius;
			data.mat = mat;
			return true;
		}
	}
	return false;
}

#endif