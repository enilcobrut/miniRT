#include "miniRT.h"

	  // Returns a random real in [0,1).
double	random_double(void)
{
	return ((double)rand() / (RAND_MAX + 1.0));
}

	// Returns a random real in [min,max).
double random_double_2(double min, double max)
{

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

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

double ft_sqrt(double number)
{
	long i;
	double x2, y;
	const double threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = * ( long * ) &y;
	i = 0x5f3759df - ( i >> 1 );
	y = * ( double * ) &i;
	y = y * ( threehalfs - ( x2 * y * y ) );
	return y;
}

t_vector vec_cross(const t_vector u, const t_vector v)
{
	return ((t_vector){u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x});
}