#include "miniRT_bonus.h"
int	hit(const t_rayon *r, double t_max, t_hit_record *rec, t_obj *obj, t_minirt *s)
{
	t_hit_record temp_rec;
	int	hit_anything = 0;
	double closest_so_far = t_max;
	

	while (obj)
	{

		
		if (obj->type == SPHERE && hit_sphere(&obj->u.sp, r, &temp_rec, T_MIN, closest_so_far))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
		}
		else if (obj->type == PLANE && hit_plane(&obj->u.pl, r, &temp_rec, T_MIN, closest_so_far))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
		}
		else if (obj->type == CYLINDER && hit_cylinder(&obj->u.cy, r, &temp_rec, T_MIN, closest_so_far))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
		}
		/*else if (obj->type == CYLINDER && hit_plane(&obj->u.cy, r, &temp_rec, t_min, t_max))*/
		obj = obj->next;
	}
	if (hit_anything)
	{
		rec->normal = vec3_unit_vector(rec->normal);
		//printf("pos x : %lf pos y : %lf\n" ,rec->p.x, rec->p.z);
		// printf("%d %d\n", super_mod((double)rec->p.x * 100.0, s->bump_height), (super_mod((double)rec->p.z * 100.0, s->bump_width)));
		int col = s->bump_map_addr[(super_mod((double)rec->p.x * 100.0, s->bump_height)) * s->bump_width + (super_mod((double)rec->p.z * 100.0, s->bump_width))];
		// printf("col : %x\n", col);
		rec->p = add_(rec->p, mul_(rec->normal, ((double)(col & 0xff) / 255.0 - .5) / 100.0));
		// printf("%lf\n", (double)(col & 0xff) / 1000.0);
	}
	return (hit_anything);
}
