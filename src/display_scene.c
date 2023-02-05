#include "miniRT.h"

void display_scene(t_minirt *s)
{
	get_buffer(s);
	get_pixels_to_img(s, HEIGHT, SCENE);
	push_img_to_win(s, SCENE);
	if (s->cam_param_display == 1)
		display_param_cam(s);
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
// t_color ray_color(t_rayon *r, t_minirt *s, int depth)
// {
//     t_hit_record rec;
//     t_color light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);

//     if (depth <= 0)
//         return (init_color(0, 0, 0));

//     if (hit(r, 0.001, INF, &rec, s->obj))
//     {
//         t_vector light_dir = sub_(s->light_axis, rec.p);
//         double light_distance = vec3_length(light_dir);
//         light_dir = vec3_unit_vector(light_dir);

//         t_rayon shadow_ray = init_rayon(rec.p, light_dir);
//         t_hit_record shadow_rec;

//         if (!hit(&shadow_ray, 0.001, light_distance, &shadow_rec, s->obj))
//         {
//             double specular = fmax(0, dot(light_dir, vec3_unit_vector(reflect(r->direction, rec.normal))));
//             double diffuse = fmax(0, dot(light_dir, vec3_unit_vector(rec.normal)));
//             light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (diffuse + pow(specular, 100))));
//         }

//         t_rayon scattered;
//         t_color attenuation;

//         if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
//             return (color_mul(attenuation, ray_color(&scattered, s, depth - 1)));
//         return (attenuation);
//     }
//     return (light);
// }

// t_color ray_color_2(t_rayon *r, t_minirt *s, int depth)
// {
// 	t_hit_record rec;

// 	if (!hit(r, 0.001, INF, &rec, s->obj))
// 		return (init_color(0,0,0));
// }

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


// t_color	ray_color(t_rayon *r, t_minirt *s, int depth)
// {
// 	t_hit_record rec;
// 	t_hit_record rec2;

// 	if (depth <= 0)
// 		return (init_color(0, 0, 0));

// 	r->direction = vec3_unit_vector(r->direction);
// 	t_color light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
// 	if (hit(r, 0.001, INF, &rec, s->obj))
// 	{
// 		t_rayon scattered;
// 		t_color attenuation;
// 		t_rayon	verif;
// 		{
// 			t_vector light_ax =s->light_axis; //add_(s->light_axis, mul_(random_in_unit_sphere_2(), .4));
// 			t_vector light_dir = sub_(light_ax, rec.p);

// 			verif = init_rayon(rec.p, vec3_unit_vector(light_dir));

// 			if (!hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
// 			{
// 				double diffuse = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal)));
// 				light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * diffuse));

// 				// pour toutes les lumières
// 			}
// 			else
// 				printf("brbrbr\n");
// 		}
// 		if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
// 			return (color_mul(attenuation, light));
// 		return (color_mul(attenuation, light));
// 	}
// 	return (init_color(0,0,0));
// }


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
			t_vector light_ax =s->light_axis; //add_(s->light_axis, mul_(random_in_unit_sphere_2(), .4));
			t_vector light_dir = sub_(light_ax, rec.p);

			verif = init_rayon(rec.p, vec3_unit_vector(light_dir));

			if (!hit(&verif, 0.001, vec3_length(sub_(light_ax, rec.p)), &rec2, s->obj))
			{
				double speculaire = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(reflect(r->direction, rec.normal))));
				double light_distance = vec3_length(light_dir)/1000;
				//double test = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal)));
				double test = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal))) / (1 + light_distance * light_distance);
				light = color_add_(light, color_mul_scalar(s->light_color, s->light_brightness_ratio * (test + pow(speculaire, 100))));

				 // pour toute les lights
			}
		}
		if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
			return (/*color_mul(*/color_mul(attenuation, clamp_color(light)/*, ray_color(&scattered, s, depth - 1))*/));
		return (color_mul(attenuation, clamp_color(light)));
	 }
	 return (init_color(0,0,0));
}



t_color	ray_color_3(t_rayon *r, t_minirt *s, int depth)
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
				double light_distance = vec3_length(light_dir);
				double test = fmax(0, dot(vec3_unit_vector(light_dir), vec3_unit_vector(rec.normal))) / (1 + light_distance * light_distance);
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

void	get_multi_threading(t_minirt *s)
{
	pthread_mutex_init(&s->count, NULL);
	s->on = 0;
	pthread_t *t = ft_calloc(s->nt, sizeof(pthread_t));
	int i = 0;
	while (i < s->nt)
	{
		while (pthread_create(&t[i], NULL, &dispatch_thread, s));
		i++;
	}
	i = 0;
	while (i < s->nt)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&s->count);
	free (t);
}

void get_no_multi_threading(t_minirt *s)
{
	int y = HEIGHT - 1;
	int x = 0;
	int i = 0;
	while (y >= 0)
	{
		x = 0;
		while (x < WIDTH)
		{
			s->r.pixel_color.r = 0;
			s->r.pixel_color.g = 0;
			s->r.pixel_color.b = 0;
			i = 0;
			while (i < s->samples_per_pixel)
			{
				s->r.mul_t_u = 1 - ((double)x + random_double()) / (double)(WIDTH - 1);
				s->r.mul_t_v = ((double)y + random_double()) / (double)(HEIGHT - 1);
				s->r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.lower_left_corner, mul_(s->r.horizon, s->r.mul_t_u)), mul_(s->r.vertical, s->r.mul_t_v)), s->cam_origin));
				s->r.pixel_color = color_add_(s->r.pixel_color, ray_color(&s->r.r, s, s->depth));
				i++;
			}
			s->buf[HEIGHT - y - 1][x] = write_color(s->r.pixel_color, s->samples_per_pixel);
			x++;
		}
		y--;
	}
}

int	get_buffer(t_minirt *s)
{

	const t_vector vup = init_vector(0, 1, 0);
	s->r.w = vec3_unit_vector(mul_(s->cam_vec_dir, -1));
	s->r.u = vec3_unit_vector(vec_cross(vup, s->r.w));
	s->r.v = vec_cross(s->r.w, s->r.u);
	s->r.theta = degrees_to_radians(s->cam_fov);
	s->r.h = tan(s->r.theta/2);
	s->r.viewport_height = 2.0 * s->r.h;
	s->r.viewport_width = ((double)WIDTH/HEIGHT) * s->r.viewport_height;
	s->r.horizon = mul_(s->r.u, s->r.viewport_width);
	s->r.vertical = mul_(s->r.v, s->r.viewport_height);
	s->r.lower_left_corner = sub_(sub_(sub_(s->cam_origin, mul_(s->r.horizon, 0.5)), mul_(s->r.vertical, 0.5)), s->r.w);
	get_multi_threading(s);
	//get_no_multi_threading(s); //sans thread pour la mandatory	
	return (0);
}

/* TEST AVEC DES LISTES CHAINEES

//t_buf *b = s->b;
// b = lst_add_buf(&s->b, lst_new_buf(x, (HEIGHT - y - 1), write_color(pixel_color, s->samples_per_pixel), 0));
// printf("%d-%d ", b->hexa, b->n_object);

*/

/* BAZAR CELINE

	//t_vector origin;
		//origin = s->cam_origin;
	// horizon.x = viewport_width;
	// horizon.y = 0;
	// horizon.z = 0;
	// vertical.x = 0;
	// vertical.y = viewport_height;
	// vertical.z = 0;
	//t_vector lookat = add_(s->cam_origin, s->cam_vec_dir);
	//t_vector lookfrom = s->cam_origin;

	// Camera
	//double focal_length = 1.0;
	// origin.x = s->cam_origin.x;
	// origin.y = s->cam_origin.y;
	// origin.z = s->cam_origin.z;*/
		//lower_left_corner = sub_(sub_(origin, div_(horizon, 2)), sub_(div_(vertical, 2), s->cam_vec_dir/*init_vector(0, 0, focal_length*/));
	
