#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "surface.h"

class material
{
public:
	virtual bool scatter(const ray& rIn, const collisionData& data, rn::vector3f& attenuation, ray& scattered) const = 0;
};

/// Materials

class lambertian : public material {
public:
	rn::vector3f albedo;

	lambertian(const rn::vector3f alb) : albedo(alb) {}

	virtual bool scatter(const ray& r_in, const collisionData& data, rn::vector3f& attenuation, ray& scattered) const {
		rn::vector3f target = data.p + data.normal + rn::randomInUnitSphere();
		scattered = ray(data.p, target - data.p);
		attenuation = albedo;
		return true;
	}
};

class metal : public material {
public:
	rn::vector3f albedo;

	metal(const rn::vector3f alb) : albedo(alb) {}

	virtual bool scatter(const ray& rIn, const collisionData& data, rn::vector3f& attenuation, ray& scattered) const {
		rn::vector3f reflected = reflect(rn::unitVector(rIn.direction()), data.normal);
		scattered = ray(data.p, reflected);
		attenuation = albedo;
		return (rn::dot(scattered.direction(), data.normal) > 0);
	}
};

class glass : public material {
public:
	rn::vector3f albedo;

	glass(const rn::vector3f alb) : albedo(alb) {}

	virtual bool scatter(const ray& rIn, const collisionData& data, rn::vector3f& attenuation, ray& scattered) const {
		rn::vector3f translated = rn::unitVector(rIn.direction());
		scattered = ray(data.p + (1.1f) * rn::unitVector(rIn.direction()), translated);
		attenuation = albedo;
		return true;
	}
};

#endif