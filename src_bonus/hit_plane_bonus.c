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