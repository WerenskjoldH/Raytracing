#define _CRT_SECURE_NO_WARNINGS

#define NUMBER_OF_SAMPLES 200

#define IMAGE_HEIGHT 100
#define IMAGE_WIDTH  200

#include <stdlib.h>
#include <stdio.h>

#include <fstream>

#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "material.h"

rn::vector3f colorFromRay(const ray& r, hitable *world, int depth)
{
	hitRecord record;
	if (world->hit(r, 0.001, FLT_MAX, record))
	{
		// Recursive approach to bouncing a ray about a scene until it does not make contact with an object in the scene
		ray scattered;
		rn::vector3f attenuation;

		
		if (depth < 50 && record.mat->scatter(r, record, attenuation, scattered)) { 
			rn::vector3f target = record.p + record.normal + rn::randomInUnitSphere();
			return attenuation * colorFromRay(scattered, world, depth+1);
		}
		else {
			return rn::vector3f(0);
		}
	}
	else
	{
		rn::vector3f unitDir = rn::unitVector(r.direction());
		float t = 0.5 * (unitDir.y + 1.0);
		return (1.0 - t) * rn::vector3f(1.0, 1.0, 1.0) + t * rn::vector3f(0.5, 0.7, 1.0);
	}
}

int main()
{

	int nx = IMAGE_WIDTH;
	int ny = IMAGE_HEIGHT;
	/// Image File Rendering & Output

	// Header Information
	std::ofstream file("output.ppm", std::ios::binary);
	file << "P3\n" << nx << " " << ny << "\n255\n";

	// Init variables
	camera cam;

	hitable *list[2];
	list[0] = new sphere(rn::vector3f(0, 0, -1.0), 0.5, new lambertian(rn::vector3f(0.8, 0.3, 0.3)));
	list[1] = new sphere(rn::vector3f(0, -100.5, -1.0), 100, new lambertian(rn::vector3f(0.8, 0.3, 0.4)));
	//list[2] = new sphere(rn::vector3f(1,0,-1), 0.5, new metal(rn::vector3f(0.8, 0.6, 0.2)));
	//list[3] = new sphere(rn::vector3f(-1, 0, -1), 0.5, new metal(rn::vector3f(0.8, 0.8, 0.8)));

	hitable *world = new hitableList(list, 2);

	float prevPercentDone = 0;

	for (int y = ny - 1; y >= 0; y--)
		for (int x = 0; x < nx; x++)
		{
			rn::vector3f col(0);
			
			// Add anti-aliasing ( prevent aliasing or jagged edges where curves are present ) also helps prevents artifacting 
			for (int s = 0; s < NUMBER_OF_SAMPLES; s++)
			{
				float u = float(x + (rand() / (RAND_MAX + 1.0))) / float(nx);
				float v = float(y + (rand() / (RAND_MAX + 1.0))) / float(ny);

				ray r = cam.getRay(u, v);
				rn::vector3f p = r.pointAt(2.0);
				col += colorFromRay(r, world, 0);

				//if (col.y == 0 && col.z == 0)
				//	std::cout << "ERROR FOUND!";
			}

			col /= float(NUMBER_OF_SAMPLES);

			// Gamma correction ( correctly brightening the pixels )
			col = rn::vector3f(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));



			int ir = int(255.99f * col.r());
			int ig = int(255.99f * col.g());
			int ib = int(255.99f * col.b());

			float tempPercentDone = 100.f - (float)int(100.f * (float((y * IMAGE_HEIGHT) + x) / float(IMAGE_HEIGHT * IMAGE_WIDTH)) + 0.5);
			if (tempPercentDone != prevPercentDone)
			{
				printf("Progress: %.0f%%\n", tempPercentDone);
				prevPercentDone = tempPercentDone;
			}
			

			file << ir << " " << ig << " " << ib << "\n";
		}

	file.close();

	return 0;
}

