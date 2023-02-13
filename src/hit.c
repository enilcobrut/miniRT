#include "miniRT.h"

int	hit(const t_rayon *r, double t_max, t_hit_record *rec, t_obj *obj)
{
	t_hit_record	temp_rec;
	int				hit_anything;
	double			closest_so_far;
	
	hit_anything = 0;
	closest_so_far = t_max;
	while (obj)
	{
		if (obj->type == SPHERE && hit_sphere(&obj->u_.sp, r, &temp_rec,
			closest_so_far))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
			rec->hit_obj = obj;
		}
		else if (obj->type == PLANE && hit_plane(&obj->u_.pl, r, &temp_rec,
			closest_so_far))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
			rec->hit_obj = obj;
		}
		else if (obj->type == CYLINDER && hit_cylinder(&obj->u_.cy, r,
			&temp_rec, closest_so_far))
		{	
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
			rec->hit_obj = obj;
		}
		obj = obj->next;
	}
	if (hit_anything)
		rec->normal = vec3_unit_vector(rec->normal);
	return (hit_anything);
}
