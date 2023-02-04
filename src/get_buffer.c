#include "miniRT.h"

/*

t_vector	vector_director(t_minirt *s, int *x, int *y)
{
	t_vector	p;
	int			y2;
	float		a;
	float		b;
	
	// s->cam_vec_dir;
	// s->cam_origin;

	// p.x = *x - (WIDTH) / 2;
	// p.y = *y - (HEIGHT + 32) / 2;
	// p.z = ((WIDTH) / 2);

	x2 = - *x + (WIDTH) / 2;
	y2 = *y - (HEIGHT + 32) / 2;
	a = (WIDTH) / (2 * (tan((s->cam_fov * PI / 180) / 2)));

	p.x = s->cam_origin.x + s->cam_vec_dir.z * x2 + s->cam_vec_dir.x * (a + y2 * s->cam_vec_dir.y);
	p.y = s->cam_origin.y + a * s->cam_vec_dir.y + y2 * \
			(s->cam_vec_dir.z * s->cam_vec_dir.z - s->cam_vec_dir.x * s->cam_vec_dir.x);

	p.z = s->cam_origin.z + x2 * s->cam_vec_dir.x + s->cam_vec_dir.z * (a - y2 * s->cam_vec_dir.y);
	// printf("(%f) - (%f) - (%f)\n", p.x, p.y, p.z);
	// exit (0);
	return (p);
}*/


/*
float	intersection_sphere(t_rayon *r, t_sphere *sp, t_vector *p, t_vector *n)
{
	t_vector	tmp;
	float		a;
	float		b;
	float		delta;
	float		t1;
	float		t2;

	tmp = sub_(r->origine, sp->center_axis);
	a = 1;
	b = 2 * dot(r->direction, tmp);
	delta = b * b - 4 * a * (get_norme_vector(tmp) - sp->radius * sp->radius);
	if (delta < 0)
		return (-1);
	t2 = (-b + sqrt(delta)) / (2 * a);
	if (t2 < 0)
		return (-1);
	t1 = (-b - sqrt(delta)) / (2 * a);
	if (t1 > 0)
		*p = add_(r->origine, mul_(r->direction, t1));
	else
		*p = add_(r->origine, mul_(r->direction, t2));
	*n = get_normalize_vector(sub_(*p, sp->center_axis));
	if (t1 > 0)
		return (t1);
	return (t2);
}

float	intersection_cylinder(t_minirt *s, t_rayon *r, t_cylinder *cy, t_vector *p, t_vector *n)
{
	t_vector	tmp;
	float		a;
	float		b;
	float		delta;
	float		t1;
	float		t2;
	float		rayon = cy->diameter / 2;

	tmp = cy->axis;
	tmp.y = (cy->axis.z - rayon) * (r->direction.y / r->direction.z);
	//printf("%f - %f - %f\n", tmp.x, tmp.y, tmp.z);
	mlx_pixel_put(s->mlx, s->win, tmp.x + (WIDTH) / 2 , tmp.y + 360, 0xff0000);
	return (-1);
	// printf("tmp.y:%f\n", tmp.y);
	// exit (0);
	tmp = sub_(r->origine, tmp);
	a = 1;
	b = 2 * dot(r->direction, tmp);
	delta = b * b - 4 * a * (get_norme_vector(tmp) - rayon * rayon);
	if (delta < 0)
		return (-1);
	t2 = (-b + sqrt(delta)) / (2 * a);
	if (t2 < 0)
		return (-1);
	t1 = (-b - sqrt(delta)) / (2 * a);
	if (t1 > 0)
		*p = add_(r->origine, mul_(r->direction, t1));
	else
		*p = add_(r->origine, mul_(r->direction, t2));
	tmp = cy->axis;
	tmp.y = cy->axis.z * (r->direction.y / r->direction.z);
	*n = get_normalize_vector(sub_(*p, tmp));
	if (t1 > 0)
		return (t1);
	return (t2);
}

float	intersection_plane(t_rayon *r, t_cylinder *pl, t_vector *p, t_vector *n)
{
	float t;

	t = dot(sub_(pl->axis, r->origine), pl->norm_or_vector) 
										/ dot(r->direction, pl->norm_or_vector);
	if (!t || t < 0)
		return (-1);
	*p = add_(r->origine, mul_(r->direction, t));
	*n = get_normalize_vector(sub_(*p, pl->axis));
	return (t);
}

float	intersection_scene(t_minirt *s, t_rayon *r, t_vector *p, t_vector *n)
{
	t_type		obj_type;
	t_vector	p2;
	t_vector	n2;
	float		t1;
	float		t;

	obj_type.sp = s->sp;
	t = FLT_MAX;
	while (obj_type.sp)
	{
		t1 = intersection_sphere(r, obj_type.sp, &p2, &n2);
		if (t1 != -1 && t1 < t)
		{
			s->obj_type.sp = obj_type.sp;
			if (p)
				*p = p2;
			if (n)
				*n = n2;
			t = t1;
		}
		obj_type.sp = obj_type.sp->next;
	}
	obj_type.cy = s->cy;
	while (obj_type.cy)
	{
		t1 = intersection_cylinder(s, r, obj_type.cy, &p2, &n2);
		if (t1 != -1 && t1 < t)
		{
			s->obj_type.cy = obj_type.cy;
			if (p)
				*p = p2;
			if (n)
				*n = n2;
			t = t1;
		}
		obj_type.cy = obj_type.cy->next;
	}
	obj_type.pl = s->pl;
	while (obj_type.pl)
	{
		t1 = intersection_plane(r, obj_type.cy, &p2, &n2);
		if (t1 != -1 && t1 < t)
		{
			s->obj_type.pl = obj_type.pl;
			if (p)
				*p = p2;
			if (n)
				*n = n2;
			t = t1;
		}
		obj_type.pl = obj_type.pl->next;
	}
	if (t == FLT_MAX)
		return (-1);
	return (t);
}

t_vector	show_light(t_minirt *s, t_type obj_type, t_vector *p, t_vector *n)
{
	t_rayon		r;
	t_vector	color_pixel;
	float		d_light;
	float		t_light_scene;
	int 		intensite_lumiere;

	r = init_rayon(add_(*p, mul_(*n, 0.01)), get_normalize_vector(sub_(s->light_axis, *p)));
	d_light = get_norme_vector(sub_(s->light_axis, *p));
	t_vector p2, n2;
	t_light_scene = intersection_scene(s, &r, NULL, NULL);
	if (s->light_brightness_ratio > s->amb_light_ratio && t_light_scene != -1 && t_light_scene * t_light_scene < d_light)
		intensite_lumiere = 100000000 * s->amb_light_ratio;
	else
		intensite_lumiere = 100000000 * s->light_brightness_ratio;
	if (obj_type.sp->id == sphere)
		color_pixel = hexa_to_rgb(obj_type.sp->color, &obj_type.sp->red, &obj_type.sp->green, &obj_type.sp->blue);
	else if (obj_type.pl->id == plane)
		color_pixel = hexa_to_rgb(obj_type.pl->color, &obj_type.pl->red, &obj_type.pl->green, &obj_type.pl->blue);
	else if (obj_type.cy->id == cylinder)
		color_pixel = hexa_to_rgb(obj_type.cy->color, &obj_type.cy->red, &obj_type.cy->green, &obj_type.cy->blue);
	color_pixel = mul_(div_(color_pixel, 255), intensite_lumiere \
		* max(0, dot(get_normalize_vector(sub_(s->light_axis, *p)), *n)) \
		/ d_light);
	// color_pixel = interpolation_color(color_pixel, hexa_to_rgb(s->light_color));
	color_pixel.x = min(255, max(obj_type.sp->red * s->amb_light_ratio, pow(color_pixel.x, 1/2.2)));
	color_pixel.y = min(255, max(obj_type.sp->red * s->amb_light_ratio, pow(color_pixel.y, 1/2.2)));
	color_pixel.z = min(255, max(obj_type.sp->red * s->amb_light_ratio, pow(color_pixel.z, 1/2.2)));

	// unsigned char test, test1, test2;
	// t_vector	min_color = hexa_to_rgb(s->light_color, &test, &test1, &test2);
	// float flow = intensite_lumiere \
		// * max(0, dot(get_normalize_vector(sub_(s->light_axis, *p)), *n)) \
		// / d_light;

	// short delta = 255;
	// d_light /= 1;

	// color_pixel = add_(mul_(color_pixel, min(delta, 0 + d_light) / delta), mul_(min_color, max(0, delta - d_light) / delta));
	return (init_vector(min(255, color_pixel.x), 
						min(255, color_pixel.y), 
						min(255, color_pixel.z)));
}


// hexa_to_rgb(s->light_color, (unsigned char *)&intensite_lumiere, (unsigned char *)&intensite_lumiere, (unsigned char *)&intensite_lumiere)

*/
