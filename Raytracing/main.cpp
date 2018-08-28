#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

#include <fstream>

#include "ray.h"

float hitCheckSphere(const rn::vector3f& center, float radius, const ray& r)
{
	rn::vector3f originToCenter = r.origin() - center;
	float a = rn::dot(r.direction(), r.direction());
	float b = 2.0 * rn::dot(originToCenter, r.direction());
	float c = rn::dot(originToCenter, originToCenter) - radius * radius;
	// If the discriminant ( b^2 - 4ac ) is 0 then we know the polynomial has a double root, and if it is possitive it has two real roots
	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0)
	{
		return -1;
	}
	else
	{
		return (-b - sqrtf(discriminant)) / (2.0 * a);
	}
}

rn::vector3f colorFromRay(const ray& r)
{
	float t = hitCheckSphere(rn::vector3f(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		rn::vector3f normal = rn::unitVector(r.pointAt(t) + rn::vector3f(0, 0, 1));
		return 0.5 * rn::vector3f(normal.r() + 1, normal.g() + 1, normal.b() + 1);
	}
	rn::vector3f unitDir = rn::unitVector(r.direction());
	t = 0.5 * (unitDir.y + 1.0);
	return (1.0 - t) * rn::vector3f(1.0, 1.0, 1.0) + t * rn::vector3f(0.5, 0.7, 1.0);
}

int main()
{
	
	int nx = 200;
	int ny = 100;
	/// Image File Rendering & Output

	// Header Information
	std::ofstream file("output.ppm", std::ios::binary);
	file << "P3\n" << nx << " " << ny << "\n255\n";

	// Init variables
	rn::vector3f lowerLeftCorner(-2.0, -1.f, -1.f);
	rn::vector3f horizontal(4.0, 0.0, 0.0);
	rn::vector3f vertical(0.f, 2.f, 0.f);
	rn::vector3f origin(0.f, 0.f, 0.f);

	for (int y = ny-1; y >= 0; y--)
		for (int x = 0; x < nx; x++)
		{
			float u = float(x) / float(nx);
			float v = float(y) / float(ny);
			ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);
			rn::vector3f col = colorFromRay(r);
			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());

			file << ir << " " << ig << " " << ib << "\n";
		}

	file.close();

    return 0;
}

