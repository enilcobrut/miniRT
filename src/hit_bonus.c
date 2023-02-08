#include "miniRT_bonus.h"

int	hit(const t_rayon *r, double t_min, double t_max, t_hit_record *rec, t_obj *obj)
{
	t_hit_record temp_rec;
	int	hit_anything = 0;
	double closest_so_far = t_max;
	
	while (obj)
	{

		if (obj->type == SPHERE && hit_sphere(&obj->u.sp, r, &temp_rec, t_min, closest_so_far))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
		}
		else if (obj->type == PLANE && hit_plane(&obj->u.pl, r, &temp_rec, t_min, closest_so_far))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
		}
		else if (obj->type == CYLINDER && hit_cylinder(&obj->u.cy, r, &temp_rec, t_min, closest_so_far))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
		}
		obj = obj->next;
	}
	if (hit_anything)
		rec->normal = vec3_unit_vector(rec->normal);
	return (hit_anything);
}