#include "miniRT.h"

double length_squared(t_vector v)
{
	return (v.x*v.x + v.y*v.y + v.z*v.z);
}

double	dot(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vector	get_normalize_vector(t_vector v)
{
	t_vector	new_v;
	float		norm;

	new_v = v;
	norm = sqrt(get_norme_vector(v));
	new_v.x /= norm;
	new_v.y /= norm;
	new_v.z /= norm;
	return (new_v);
}

float	get_norme_vector(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector init_vector(float x, float y, float z)
{
	return ((t_vector){x, y, z});
}

t_rayon	init_rayon(t_vector origine, t_vector direction)
{
	t_rayon	r;

	r.origine = origine;
	r.direction = direction;
	return (r);
}

t_vector	sub_(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vector	add_(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vector	div_(t_vector v, float n)
{
	t_vector	new_v;

	new_v.x = v.x / n;
	new_v.y = v.y / n;
	new_v.z = v.z / n;
	return (new_v);
}

t_vector	mul_(t_vector v, double n)
{
	t_vector	new_v;

	new_v.x = v.x * n;
	new_v.y = v.y * n;
	new_v.z = v.z * n;
	return (new_v);
}


t_color get_rgb(int color)
{
	return ((t_color){get_r(color)/255.0, get_g(color)/255.0, get_b(color)/255.0});
}


double	vec3_length(t_vector a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vector	vec3_unit_vector(t_vector a) 
{
    double length = vec3_length(a);

    return (t_vector) { a.x / length, a.y / length, a.z / length };
}

t_vector vec_random()
{
	return ((t_vector){(double)random_double(), (double)random_double(), (double)random_double()});
}


t_vector vec_random_2(double min, double max)
{
	return ((t_vector){random_double_2(min, max), random_double_2(min, max), random_double_2(min, max)});
}

t_vector random_in_unit_sphere()
{
	while (1)
	{
		t_vector p = vec_random_2(-1, 1);
		double len = length_squared(p);
		if (len <= 1 && len > 0)
			return (get_normalize_vector(p));
	}
}

t_vector random_in_unit_sphere_2()
{
	while (1)
	{
		t_vector p = vec_random_2(-1, 1);
		double len = length_squared(p);
		if (len <= 1 && len > 0)
			return (p);
	}
}