#include "miniRT.h"

t_color	ray_color_1(t_rayon *r, t_minirt *s, int depth)
{
	t_hit_record rec;
	
	if (depth <= 0)
		return (init_color(0, 0, 0));

	r->direction = vec3_unit_vector(r->direction);
	if (!hit(r, 0.001, INF, &rec, s->obj))
		return (init_color(0, 0, 0));
	t_rayon	verif;
	t_vector light_ax = s->light_axis;
	t_vector light_dir = sub_(light_ax, rec.p);
	verif = init_rayon(rec.p, light_dir);
	t_hit_record rec2;
	if (hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
		return (init_color(0, 0, 0));
	t_color light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
	double light_distance = vec3_length(light_dir);
	double diffuse = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal)));
	double specular = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(reflect(r->direction, rec.normal))));
	light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (diffuse / (1 + light_distance * light_distance) + pow(specular, 100))));
	t_color	attenuation;
	t_rayon scattered;
	if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
		return (color_mul(attenuation, clamp_color(color_mul(light, ray_color(&scattered, s, depth - 1)))));
	return (color_mul(attenuation, clamp_color(light)));
}

t_color	ray_color(t_rayon *r, t_minirt *s, int depth)
{
	t_hit_record rec;
	t_hit_record rec2;

	if (depth <= 0)
		return (init_color(0, 0, 0));

	r->direction = vec3_unit_vector(r->direction);
	t_color light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
	 if (hit(r, 0.001, INF, &rec, s->obj))
	 {
		t_rayon scattered;
		t_color attenuation;
		t_rayon	verif;
		{
			t_vector light_ax =s->light_axis;
			t_vector light_dir = sub_(light_ax, rec.p);

			verif = init_rayon(rec.p, vec3_unit_vector(light_dir));

			if (!hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
			{
				double speculaire = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(reflect(r->direction, rec.normal))));
				double light_distance = vec3_length(light_dir)/1000;
				double test = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal))) / (1 + light_distance * light_distance);
				light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (test + pow(speculaire, 100))));
			}
		}
		if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
			return (color_mul(attenuation, clamp_color(light)));
		return (color_mul(attenuation, clamp_color(light)));
	 }
	 return (init_color(0,0,0));
}

t_color	ray_color_3(t_rayon *r, t_minirt *s, int depth)
{
	t_hit_record rec;
	t_hit_record rec2;

	if (depth <= 0)
		return (init_color(0, 0, 0));

	r->direction = vec3_unit_vector(r->direction);
	t_color light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
	 if (hit(r, 0.001, INF, &rec, s->obj))
	 {
		t_rayon scattered;
		t_color attenuation;
		t_rayon	verif;
		{
			t_vector light_ax =s->light_axis;
			t_vector light_dir = sub_(light_ax, rec.p);

			verif = init_rayon(rec.p, light_dir);

			if (!hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
			{
				double speculaire = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(reflect(r->direction, rec.normal))));
				double light_distance = vec3_length(light_dir);
				double test = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal))) / (1 + light_distance * light_distance);
				light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (test + pow(speculaire, 100))));

				 // pour toute les lights
			}
		}
		if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
			return (/*color_mul(*/color_mul(attenuation, clamp_color(light)));
		return (color_mul(attenuation, clamp_color(light)));
	 }
	 return (init_color(0,0,0));
}
