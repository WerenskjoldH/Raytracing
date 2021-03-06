#define _CRT_SECURE_NO_WARNINGS

#define AA_SAMPLES 200

// Keep this small for testing as the growth is exponential f(x,y) = x * y
#define IMAGE_WIDTH	 800
#define IMAGE_HEIGHT 400

#include "raycaster.h"

int main()
{
	
	raycaster rayCaster(IMAGE_WIDTH, IMAGE_HEIGHT, AA_SAMPLES);

	rayCaster.render("output.ppm");

    return 0;
}

