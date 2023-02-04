#include "miniRT.h"

int hit_plane(t_plane *p, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	t_vector norm = vec3_unit_vector(p->norm_or_vector);
	double t = dot(norm, sub_(p->axis, r->origine)) / dot(norm, r->direction);
	if (t < t_min || t > t_max)
		return (0);
	rec->t = t;
	rec->p = add_(r->origine, mul_(r->direction, t));
	rec->normal = norm;
	rec->front_face = dot(r->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = mul_(rec->normal, -1);
	return (1);
}

// int	hit_plane(t_plane *pl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
// {
// 	(void)rec;
// 	double denom = dot(vec3_unit_vector(pl->norm_or_vector), r->direction);
// 	if (denom > 1e-6)
// 	{
// 		t_vector p = sub_(pl->axis, r->origine);
// 		double t = dot(p, pl->axis);
// 		if (t < t_min || t_max < t)
// 		{
// 			t = dot(p, pl->axis);
// 			if (t < t_min || t_max < t)
// 				return (0);
// 		}
// 		return (t >= 0);
// 	}
// 	return (0);
//       //  t_vector p0l0 = sub_(pl->axis, r->origine);
//         //t = dot(get_normalize_vector(p0l0), get_normalize_vector(pl->norm_or_vector)) / denom;
// }