#include "miniRT.h"

double	random_double(void)
{
	  // Returns a random real in [0,1).
	return ((double)rand() / (RAND_MAX + 1.0));
}

double random_double_2(double min, double max)
{
	// Returns a random real in [min,max).
	return (min + (max - min) * random_double());
}