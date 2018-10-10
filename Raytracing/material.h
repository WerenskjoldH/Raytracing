#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "hitable.h"

class material {
public:
	virtual bool scatter(const ray& rIn, const hitRecord& rec, rn::vector3f& attenuation, ray& scattered) const = 0;
};

/// Material Definitions

class lambertian : public material {
public:
	rn::vector3f albedo;

	lambertian(const rn::vector3f alb) : albedo(alb) {}
	virtual bool scatter(const ray& r_in, const hitRecord& rec, rn::vector3f& attenuation, ray& scattered) const {
		rn::vector3f target = rec.p + rec.normal + rn::randomInUnitSphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};

class metal : public material {
public:
	rn::vector3f albedo;

	metal(const rn::vector3f alb) : albedo(alb) {}
	virtual bool scatter(const ray& rIn, const hitRecord& rec, rn::vector3f& attenuation, ray& scattered) const {
		rn::vector3f reflected = reflect(rn::unitVector(rIn.direction()), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (rn::dot(scattered.direction(), rec.normal) > 0);
	}
};


#endif