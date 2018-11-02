#ifndef _RAYCASTER_H_
#define _RAYCASTER_H_

#include <stdlib.h>
#include <stdio.h>

#include <fstream>

#include "world.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

class raycaster
{
public:
	raycaster(int _imageWidth, int _imageHeight, int _aaSamples);
	void render(const char* fileName);

private:
	int imageWidth, imageHeight, aaSamples;

	rn::vector3f colorFromRay(const ray& r, world* w, int depth);

};

/// Function Definitions

raycaster::raycaster(int _imageWidth, int _imageHeight, int _aaSamples)
{
	imageWidth = _imageWidth;
	imageHeight = _imageHeight;
	aaSamples = _aaSamples;
}

rn::vector3f raycaster::colorFromRay(const ray & r, world* w, int depth)
{
	collisionData data;
	if (w->checkCollision(r, 0.001, FLT_MAX, data))
	{
		// Recursive approach to bouncing a ray about a scene until it does not make contact with an object in the scene
		ray scattered;
		rn::vector3f attenuation;


		if (depth < 50 && data.mat->scatter(r, data, attenuation, scattered)) {
			rn::vector3f target = data.p + data.normal + rn::randomInUnitSphere();
			return attenuation * colorFromRay(scattered, w, depth + 1);
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

void raycaster::render(const char* fileName)
{
	// We are going to be outputing a PPM file so... yeah
	std::ofstream outputFile(fileName, std::ios::binary);
	outputFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	camera cam(rn::vector3f(-2.0, -1.0, -1.0), rn::vector3f(4.0, 0.0, 0.0), rn::vector3f(0.0, 2.0, 0.0), rn::vector3f(0.0, 0.0, 0.0));

	// We will automate this later on don't worry
	surface *list[4];
	list[0] = new sphere(rn::vector3f(-1.0, 0, -1.0), 0.5, new lambertian(rn::vector3f(0.3, 0.3, 0.8)));
	list[1] = new sphere(rn::vector3f(0, 0, -1.0), 0.5, new metal(rn::vector3f(0.3, 0.8, 0.3)));
	list[2] = new sphere(rn::vector3f(1.0, 0, -1.0), 0.5, new glass(rn::vector3f(0.8, 0.3, 0.3)));
	list[3] = new sphere(rn::vector3f(0, -100.5, -1.0), 100, new lambertian(rn::vector3f(0.8, 0.3, 0.4)));

	world* surfaceScene = new world(list, 4);

	float prevPercentDone = 0;

	for (int y = imageHeight - 1; y >= 0; y--)
		for (int x = 0; x < imageWidth; x++)
		{
			rn::vector3f col(0);

			// Add anti-aliasing ( prevent aliasing or jagged edges where curves are present ) also helps prevents artifacting 
			for (int s = 0; s < aaSamples; s++)
			{
				float u = float(x + (rand() / (RAND_MAX + 1.0))) / float(imageWidth);
				float v = float(y + (rand() / (RAND_MAX + 1.0))) / float(imageHeight);

				ray r = cam.getRay(u, v);
				rn::vector3f p = r.getPointAt(2.0);
				col += colorFromRay(r, surfaceScene, 0);
			}

			col /= float(aaSamples);

			// Gamma correction ( correctly brightening the pixels )
			col = rn::vector3f(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));

			int ir = int(255.99f * col.r());
			int ig = int(255.99f * col.g());
			int ib = int(255.99f * col.b());

			float tempPercentDone = 100.f - (float)int(100.f * (float((y * imageHeight) + x) / float(imageHeight * imageWidth)) + 0.5);
			if (tempPercentDone != prevPercentDone)
			{
				printf("Progress: %.0f%%\n", tempPercentDone);
				prevPercentDone = tempPercentDone;
			}


			outputFile << ir << " " << ig << " " << ib << "\n";
		}

	outputFile.close();

}

#endif