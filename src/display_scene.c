#include "miniRT.h"


/****************************************************************************************************/


t_color color_add_(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_color color_mul(t_color a, t_color b)
{
	return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color init_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}


t_color	color_mul_scalar(t_color a, double b)
{
	return ((t_color){a.r * b, a.g * b, a.b * b});
}
// t_color	ray_color(const t_rayon *r, t_minirt *s, int depth)
// {
// 	//t_vector unit_dir;
// 	t_hit_record rec;
// 	t_hit_record rec2;

// 	if (depth <= 0)
// 		return (init_color(0, 0, 0));


// 	t_color light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
// 	 if (hit(r, 0.001, INF, &rec, s->obj))
// 	 {
// 		t_rayon scattered;
// 		t_color attenuation;
// 		t_rayon	verif;
// 		{
// 			t_vector light_ax = add_(s->light_axis, mul_(random_in_unit_sphere_2(), .4));
// 			t_vector light_dir = sub_(light_ax, rec.p);
// 			t_vector reflect_dir = sub_(mul_(rec.normal, 2 * dot(light_dir, rec.normal)), light_dir);
// 			t_vector view_dir = vec3_unit_vector(sub_(rec.p, s->cam_origin));
// 			verif = init_rayon(rec.p, light_dir);

// 			if (!hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
// 				light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (fmax(0, dot(light_dir, rec.normal)) + pow(fmax(0, dot(reflect_dir, view_dir)), 20))));
// 				//light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal)))));

// 		}
// 		if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
// 			return (color_mul(attenuation, light));
// 		return (color_mul(attenuation, light));
// 	 }
// 	 return (light);
// }





// t_color	ray_color(t_rayon *r, t_minirt *s, int depth)
// {
// 	//t_vector unit_dir;
// 	t_hit_record rec;
// 	t_hit_record rec2;

// 	if (depth <= 0)
// 		return (init_color(0, 0, 0));

// 	r->direction = vec3_unit_vector(r->direction);
// 	t_color light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
// 	 if (hit(r, 0.001, INF, &rec, s->obj))
// 	 {
// 		t_rayon scattered;
// 		t_color attenuation;
// 		t_rayon	verif;
// 		// t_vector light_ax = add_(s->light_axis, mul_(random_in_unit_sphere_2(), .4));

// 		// verif = init_rayon(rec.p, sub_(light_ax, rec.p));

// 		// if (hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
// 		// {

// 		// 	return (init_color(0, 0, 0));
// 		// }
// 		//return (rec.mat_ptr->albedo);
// 		{
// 			t_vector light_ax =s->light_axis; //add_(s->light_axis, mul_(random_in_unit_sphere_2(), .4));
// 			t_vector light_dir = sub_(light_ax, rec.p);

// 			verif = init_rayon(rec.p, light_dir);

// 			if (!hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
// 			{
// 				double speculaire = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(reflect(r->direction, rec.normal))));
// 				double test = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal)));
// 				light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (test + pow(speculaire, 10))));

// 				 // pour toute les lights
// 			}
// 		}
// 		if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
// 			return (/*color_mul(*/color_mul(attenuation, light)/*, ray_color(&scattered, s, depth - 1))*/);
// 		return (color_mul(attenuation, light));
// 	 }
// 	 return (light);
// 	// unit_dir = vec3_unit_vector(r->direction);
// 	// double t = 0.5 * (unit_dir.y + 1.0);
// 	// t_color white = (t_color) {1.0, 1.0, 1.0};
// 	// t_color blue = (t_color) {0.5, 0.7, 1};
// 	// return color_add_(color_mul_scalar(white, 1.0 - t), color_mul_scalar(blue, t));

// 	//return (color_add_(color_mul_scalar(white, 1.0 - t), color_mul_scalar(blue, t)));
// }


t_color		clamp_color(t_color color)
{
	return ((t_color) {clamp(color.r, 0, 1), clamp(color.g, 0, 1), clamp(color.b, 0, 1)});
}

t_color	ray_color(t_rayon *r, t_minirt *s, int depth)
{
	//t_vector unit_dir;
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
		// t_vector light_ax = add_(s->light_axis, mul_(random_in_unit_sphere_2(), .4));

		// verif = init_rayon(rec.p, sub_(light_ax, rec.p));

		// if (hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
		// {

		// 	return (init_color(0, 0, 0));
		// }
		//return (rec.mat_ptr->albedo);
		{
			t_vector light_ax =s->light_axis; //add_(s->light_axis, mul_(random_in_unit_sphere_2(), .4));
			t_vector light_dir = sub_(light_ax, rec.p);

			verif = init_rayon(rec.p, light_dir);

			if (!hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
			{
				double speculaire = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(reflect(r->direction, rec.normal))));
				double test = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal)));
				light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (test + pow(speculaire, 100))));

				 // pour toute les lights
			}
		}
		if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
			return (/*color_mul(*/color_mul(attenuation, clamp_color(light)/*, ray_color(&scattered, s, depth - 1))*/));
		return (color_mul(attenuation, clamp_color(light)));
	 }
	 return (init_color(0,0,0));
	 //return (light);
	// unit_dir = vec3_unit_vector(r->direction);
	// double t = 0.5 * (unit_dir.y + 1.0);
	// t_color white = (t_color) {1.0, 1.0, 1.0};
	// t_color blue = (t_color) {0.5, 0.7, 1};
	// return color_add_(color_mul_scalar(white, 1.0 - t), color_mul_scalar(blue, t));

	//return (color_add_(color_mul_scalar(white, 1.0 - t), color_mul_scalar(blue, t)));
}

// int shadow(t_vector hit_point, t_minirt *s,  t_hit_record *rec)
// {
//     t_vector light_dir = sub_(s->light_axis, hit_point);
//     double light_distance = vec3_length(light_dir);
//     light_dir = vec3_unit_vector(light_dir);

//     t_rayon shadow_ray;
//     shadow_ray.origine = hit_point;
//     shadow_ray.direction = light_dir;

//     if (hit(&shadow_ray, 0.001, light_distance, rec, s->obj))
//     {
//         return (1);
//     }
//     return (0);
// }



// t_color shade_light(t_minirt *s, t_hit_record *rec, t_rayon *r)
// {
//     t_vector l = vec3_unit_vector(sub_(s->light_axis, rec->p));
//     t_vector v = vec3_unit_vector(mul_(r->direction, -1));
//     t_vector h = vec3_unit_vector(add_(l, v));
//     t_color refl_color = init_color(0, 0, 0);

//     if (shadow(rec->p, s, rec))
//         return refl_color;

//     float dot_l = dot(rec->normal, l);
//     if (dot_l > 0) {
//         refl_color = color_add_(refl_color, color_mul_scalar(s->light_color, dot_l));
//     }
//     float dot_h = dot(rec->normal, h);
//     if (dot_h > 0) {
//         refl_color = color_add_(refl_color, color_mul_scalar(s->light_color, pow(dot_h, 50)));
//     }
//     return refl_color;
// }

// t_color	ray_color(const t_rayon *r, t_minirt *s, int depth, t_color background)
// {
// 	//t_vector unit_dir;
// 	t_hit_record rec;

// 	if (depth <= 0)
// 		return (init_color(0, 0, 0));

// 	if (!hit(r, 0.001, INF, &rec, s->obj))
// 		return (background);
// 		t_rayon scattered;
// 		t_color attenuation;
// 	//	t_color refl_color = init_color(0, 0, 0);
// 		t_color emitted = color_mul(map_color(s->amb_light_color), color_mul_scalar(rec.mat_ptr->albedo, s->amb_light_ratio));
// 		if (!rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
// 		return (emitted);

// 		t_color refl_color = init_color(0, 0, 0);
// 		// calculer la couleur réfléchie pour chaque lumière dans la scène
// 		refl_color = color_add_(refl_color, shade_light(s, &rec, r));
// 		// ajouter la couleur réfléchie de la lumière ambiante
// 		refl_color = color_add_(refl_color, s->amb_light_color);
// 		// ajouter la couleur réfléchie pour la lumière zone fix
// 		//refl_color = color_add_(refl_color, shade_area_light(s, &rec));

// 		return color_add_(attenuation, color_mul(ray_color(&scattered, s, depth - 1, background), refl_color));
// 		// if (!rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
// 		// 	return (emitted);
// 		// //printf("CC\n");
// 		// return color_add_(attenuation, color_mul(ray_color(&scattered, s, depth - 1, background), emitted));
// 		//return (color_add_(color_mul_scalar(attenuation, s->amb_light_ratio), color_mul(attenuation, ray_color(&scattered, s, depth - 1, background))));
// }


int hit_cylinder(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	double radius = cyl->diameter / 2;
	t_vector oc = sub_(r->origine, cyl->axis);
	double a = length_squared(r->direction) - pow(dot(r->direction, cyl->axis), 2);
	double half_b = dot(oc, r->direction) - dot(oc, cyl->axis) * dot(r->direction, cyl->axis);
	double c = length_squared(oc) - pow(dot(oc, cyl->axis), 2) - radius * radius;
	double delta = half_b * half_b - a * c;
	if (delta < 0)
	return (0);
	double sqrtd = sqrt(delta);
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
	root = (-half_b + sqrtd) / a;
	if (root < t_min || t_max < root)
	return (0);
	}
	rec->t = root;
	rec->p = add_(r->origine, mul_(r->direction, rec->t));
	t_vector normal = sub_(rec->p, cyl->axis);
	normal = sub_(normal, mul_(cyl->axis, dot(normal, cyl->axis)));
	normal = vec3_unit_vector(normal);
	rec->normal = normal;
	rec->front_face = dot(r->direction, normal) < 0;
	if (!rec->front_face)
	rec->normal = mul_(rec->normal, -1);
	return (1);
}





// int	scatter(t_rayon r, t_hit_record *rec, t_color *attenuation, t_rayon *scat)
// {

// }

void set_face_normal(const t_rayon *r, t_hit_record *rec, t_vector outward_normal)
{
	rec->front_face = dot(r->direction, outward_normal) < 0;
	if (rec->front_face)
	{
		rec->normal = outward_normal;
		rec->front_face = 1;
	}
	else
	{
		rec->normal = mul_(outward_normal, -1);
		rec->front_face = 0;
	}
}


t_color map_color(t_color color)
{
	return ((t_color) {color.r / 255.0, color.g / 255.0, color.b / 255.0});

}

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
		/*else if (obj->type == CYLINDER && hit_plane(&obj->u.cy, r, &temp_rec, t_min, t_max))*/
		obj = obj->next;
	}
	if (hit_anything)
		rec->normal = vec3_unit_vector(rec->normal);
	return (hit_anything);
}

int	hit_sphere(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	t_vector oc = sub_(r->origine, sp->center_axis);
	double a = length_squared(r->direction);
	double half_b = dot(oc, r->direction);
	double c = length_squared(oc) -  sp->radius *  sp->radius;
	double delta = half_b*half_b - a*c;
	if (delta < 0)
		return (0);
	double sqrtd = sqrt(delta);
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (0);
	}
	rec->t = root;
	rec->p = add_(r->origine, mul_(r->direction, rec->t));
	set_face_normal(r, rec, div_(sub_(rec->p, sp->center_axis), sp->radius));
	//rec->normal = div_(sub_(rec->p, sp->center_axis), sp->radius);
	return (1);
}

int scatter_lambertian(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered)
{
	(void)r;
	t_vector scatter_dir = add_(vec3_unit_vector(rec->normal), random_in_unit_sphere());
	if (near_zero(&scatter_dir))
		scatter_dir = rec->normal; 
	*scattered = init_rayon(rec->p, scatter_dir);
	*attenuation = rec->mat_ptr->albedo;
	return (1);
}

int scatter_light(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered)
{
	(void)r;
	t_vector scatter_dir = add_(vec3_unit_vector(rec->normal), random_in_unit_sphere());
	if (near_zero(&scatter_dir))
		scatter_dir = rec->normal; 
	*scattered = init_rayon(rec->p, scatter_dir);
	*attenuation = rec->mat_ptr->albedo;
	return (1);
}




t_vector	refract(const t_vector uv, const t_vector n, double etai_over_etat)
{
	double cos_thtta = fmin(dot(mul_(uv, -1), n), 1.0);
	t_vector r_out_perp = mul_(add_(uv, mul_(n, cos_thtta)),etai_over_etat);
	t_vector r_out_parallel = mul_(n, -1 * sqrt(fabs(1.0 - length_squared(r_out_perp))));
	return (add_(r_out_perp, r_out_parallel));
}

t_vector	reflect(const t_vector v, const t_vector n)
{
	return (sub_(v, mul_(n ,2*dot(v, n))));
}

int scatter_metal(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered)
{
	t_vector reflected = reflect(vec3_unit_vector(r->direction), vec3_unit_vector(rec->normal));
	*scattered = init_rayon(rec->p, add_(reflected, mul_(random_in_unit_sphere(), rec->mat_ptr->fuzz)));
	*attenuation = rec->mat_ptr->albedo;
	return (dot(scattered->direction, rec->normal) > 0);

}

double	reflectance(double cos, double ref_i)
{
	double r0 = (1 - ref_i) / (1 + ref_i);
	r0 = r0*r0;
	return (r0 + (1 - r0) * pow((1 - cos), 5));
}


int scatter_dielectric(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered)
{
	*attenuation = init_color(1.0, 1.0, 1.0);
	double refraction_ratio;

	if (rec->front_face)
		refraction_ratio = 1.0 / rec->mat_ptr->ir;
	else
		refraction_ratio = rec->mat_ptr->ir;
	t_vector unit_dir = vec3_unit_vector(r->direction);
	double cos_theta = fmin(dot(mul_(unit_dir, -1), rec->normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
	int	cannot_refract = refraction_ratio * sin_theta > 1.0;
	t_vector dir;
	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
		dir = reflect(unit_dir, rec->normal);
	else
		dir = refract(unit_dir, rec->normal, refraction_ratio);
	//t_vector refracted = refract(unit_dir, rec->normal, refraction_ratio);
	*scattered = init_rayon(rec->p, dir);
	return (1);
}


int	near_zero(const t_vector *vec)
{
	const double s = 1e-8;
	return ((fabs(vec->x) < s) && (fabs(vec->y) < s) && fabs(vec->z) < s);
}

int	write_color(t_color	 pixel_color, int sample_per_pixel)
{
	double scale = 1.0 / (double)sample_per_pixel;
	t_color new_c;
	new_c.r = pixel_color.r * scale;//sqrt(pixel_color.r * scale);
	new_c.g = pixel_color.g * scale; //sqrt(pixel_color.g * scale);
	new_c.b = pixel_color.b * scale;//sqrt(pixel_color.b * scale);
	return (create_trgb(0, new_c.r  * 255,  new_c.g * 255,  new_c.b*255));
	//return (create_trgb(0, clamp(new_c.r, 0.0, 0.999) * 256,  clamp(new_c.g, 0.0, 0.999) * 256,  clamp(new_c.b, 0.0, 0.999) * 255));
}

void	get_buffer(t_minirt *s, int opt)
{
	(void)opt;
	t_vector horizon;
	t_vector vertical;
	t_vector lower_left_corner;
	t_vector origin;
	const t_vector vup = init_vector(0, 1, 0);
	double	theta = degrees_to_radians(s->cam_fov);
	double h = tan(theta/2);
	double mul_t_u;
	double mul_t_v;
	// Image
	t_rayon		r;
	t_color	 pixel_color;
	double viewport_height = 2.0*h;
	double viewport_width = ((double)WIDTH/HEIGHT) * viewport_height;
	// horizon.x = viewport_width;
	// horizon.y = 0;
	// horizon.z = 0;
	// vertical.x = 0;
	// vertical.y = viewport_height;
	// vertical.z = 0;
	//t_vector lookat = add_(s->cam_origin, s->cam_vec_dir);
	//t_vector lookfrom = s->cam_origin;
	t_vector w = vec3_unit_vector(mul_(s->cam_vec_dir, -1));
	t_vector u = vec3_unit_vector(vec_cross(vup, w));
	t_vector v = vec_cross(w, u);
	origin = s->cam_origin;
	horizon = mul_(u, viewport_width);
	vertical = mul_(v, viewport_height);
	s->samples_per_pixel = 1;
	s->depth = 10;
	// Camera
	//double focal_length = 1.0;
	// origin.x = s->cam_origin.x;
	// origin.y = s->cam_origin.y;
	// origin.z = s->cam_origin.z;
	lower_left_corner = sub_(sub_(sub_(origin, mul_(horizon, 0.5)), mul_(vertical, 0.5)), w);
	//lower_left_corner = sub_(sub_(origin, div_(horizon, 2)), sub_(div_(vertical, 2), s->cam_vec_dir/*init_vector(0, 0, focal_length*/));
	
	// Render
	
	for (int y = HEIGHT - 1; y >= 0; --y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			pixel_color.r = 0;
			pixel_color.g = 0;
			pixel_color.b = 0;
			for (int i = 0; i < s->samples_per_pixel; ++i)
			{
				mul_t_u = 1 - ((double)x + random_double()) / (double)(WIDTH - 1);
				mul_t_v = ((double)y + random_double()) / (double)(HEIGHT - 1);
				r = init_rayon(origin, sub_(add_(add_(lower_left_corner, mul_(horizon, mul_t_u)), mul_(vertical, mul_t_v)), origin));
				pixel_color = color_add_(pixel_color, ray_color(&r, s, s->depth));
			}
			s->buf[HEIGHT - y - 1][x] = write_color(pixel_color, s->samples_per_pixel);
		}
	}
}
