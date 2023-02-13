#include "miniRT.h"

/*
ray_color_next()
{

	
}*/

t_color	ray_color(t_rayon *r, t_minirt *s, int depth)
{
	t_hit	rec;
	t_hit	rec2;
	t_color			light;
	t_rayon			verif;
	t_vector 		light_dir;
	double 			speculaire;
	double 			light_distance;
	double 			test;

	if (depth <= 0)
		return (init_color(0, 0, 0));
	r->direction = vec3_unit_vector(r->direction);
	light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
	if (hit(r, INF, &rec, s->obj))
	{
		light_dir = sub_(s->light_axis, rec.p);
		verif = init_rayon(rec.p, vec3_unit_vector(light_dir));
		if (!hit(&verif, vec3_length(sub_(s->light_axis, rec.p)), &rec2, s->obj))
		{
			speculaire = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(reflect(r->direction, rec.normal))));
			light_distance = vec3_length(light_dir) / 1000;
			test = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal))) / (1 + light_distance * light_distance);
			light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (test + pow(speculaire, 100))));
		}
		return (color_mul(rec.mat_ptr->albedo, clamp_color(light)));
	}
	return (init_color(0, 0, 0));
}
