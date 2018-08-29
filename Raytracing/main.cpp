#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

#include <fstream>

#include "sphere.h"
#include "hitableList.h"

rn::vector3f colorFromRay(const ray& r, hitable *world)
{
	hitRecord record;
	if (world->hit(r, 0.0, FLT_MAX, record))
		return 0.5 * rn::vector3f(record.normal.x + 1, record.normal.y + 1, record.normal.z + 1);
	else
	{
		rn::vector3f unitDir = rn::unitVector(r.direction());
		float t = 0.5 * (unitDir.y + 1.0);
		return (1.0 - t) * rn::vector3f(1.0, 1.0, 1.0) + t * rn::vector3f(0.5, 0.7, 1.0);
	}
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
	rn::vector3f lowerLeftCorner(-2.f, 2.f, -1.f);
	rn::vector3f horizontal(4.f, 0.f, 0.f);
	rn::vector3f vertical(0.f, 2.f, 0.f);
	rn::vector3f origin(0.f, 0.f, 0.f);

	hitable *list[2];
	list[0] = new sphere(rn::vector3f(0, 0, -1), 0.5);
	list[1] = new sphere(rn::vector3f(0, -100.5f, -1), 100);
	
	hitable *world = new hitableList(list, 2);

	for (int y = ny-1; y >= 0; y--)
		for (int x = 0; x < nx; x++)
		{
			float u = float(x) / float(nx);
			float v = float(y) / float(ny);
			ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);

			rn::vector3f p = r.pointAt(2.0);
			rn::vector3f col = colorFromRay(r, world);
			
			int ir = int(255.99f * col.r());
			int ig = int(255.99f * col.g());
			int ib = int(255.99f * col.b());

			file << ir << " " << ig << " " << ib << "\n";
		}

	file.close();

    return 0;
}

