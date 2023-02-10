#include "miniRT.h"

t_rayon	init_rayon(t_vector origine, t_vector direction)
{
	t_rayon	r;

	r.origine = origine;
	r.direction = direction;
	return (r);
}
