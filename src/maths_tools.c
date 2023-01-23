#include "miniRT.h"

double degrees_to_radians(double degrees)
{
    return (degrees * PI / 180.0);
}

double	random_double()
{
	  // Returns a random real in [0,1).
	return ((double)rand() / (RAND_MAX + 1.0));
}

double random_double_2(double min, double max)
{
	// Returns a random real in [min,max).
	return (min + (max - min) * random_double());
}

double clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}