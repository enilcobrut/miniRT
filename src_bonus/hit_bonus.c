#include "miniRT_bonus.h"

int	hit(const t_rayon *r, double t_max, t_hit_record *rec, t_obj *obj)
{
	t_hit_record	temp_rec;
	int				hit_anything;
	double			closest_so_far;
	//int				col;

	hit_anything = 0;
	closest_so_far = t_max;
	while (obj)
	{
		if ((obj->type == SPHERE && hit_sphere(&obj->u_.sp, r, &temp_rec, T_MIN, closest_so_far))
			|| (obj->type == PLANE && hit_plane(&obj->u_.pl, r, &temp_rec, T_MIN, closest_so_far))
			|| (obj->type == CYLINDER && hit_cylinder(&obj->u_.cy, r, &temp_rec, T_MIN, closest_so_far))
			|| (obj->type == CONE && hit_cone(&obj->u_.co, r, &temp_rec, T_MIN, closest_so_far)))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->mat_ptr = &obj->mat;
			rec->hit_obj = obj;
		}
		obj = obj->next;
	}
	 if (hit_anything && (rec->hit_obj->bump_map /*|| (s->hit_obj && rec->hit_obj->n == s->hit_obj->n)*/))
	 {

	 	rec->normal = vec3_unit_vector(rec->normal);
	// 	//printf("pos x : %lf pos y : %lf\n" ,rec->p.x, rec->p.z);
	// 	// printf("%d %d\n", super_mod((double)rec->p.x * 100.0, s->bump_height), (super_mod((double)rec->p.z * 100.0, s->bump_width)));
	 	int col = rec->hit_obj->bump_map_addr[(super_mod((double)rec->p.x * 100.0, rec->hit_obj->bump_height)) * rec->hit_obj->bump_width + (super_mod((double)rec->p.z * 100.0, rec->hit_obj->bump_width))];
	// 	// printf("col : %x\n", col);
	 	rec->p = add_(rec->p, mul_(rec->normal, ((double)(col & 0xff) / 255.0 - .5) / 100.0));
	// 	// printf("%lf\n", (double)(col & 0xff) / 1000.0);
	}
	// if (hit_anything)
	// {
	// 	double size = 20;
	// 	if (rec->hit_obj->type == CYLINDER)
	// 		size = rec->hit_obj->u_.cy.radius / 20.0;
	// 	else if (rec->hit_obj->type == SPHERE)
	// 		size = rec->hit_obj->u_.sp.radius /  20.0;
	// 	else if (rec->hit_obj->type == CONE)
	// 		size = rec->hit_obj->u_.co.radius / 20.0;
	// //	printf("%lf\n", size);
	// 		if (sin((PI/size)*rec->p.x)*sin((PI/size)*rec->p.z) >= 0)
	// 		{
	// 			rec->mat_ptr->albedo = rec->mat_ptr->albedo1;
	// 		}
	// 		else
	// 			rec->mat_ptr->albedo = init_color(0,0,0);
	// }
	return (hit_anything);
}
