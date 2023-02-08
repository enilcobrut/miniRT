#include "miniRT.h"

void display_scene(t_minirt *s)
{
	get_buffer(s);
	get_pixels_to_img(s, HEIGHT, SCENE);
	push_img_to_win(s, SCENE);
	if (s->cam_param_display == 1)
		display_param_cam(s);
}

t_color		clamp_color(t_color color)
{
	return ((t_color) {clamp(color.r, 0, 1), clamp(color.g, 0, 1), clamp(color.b, 0, 1)});
}

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
	*scattered = init_rayon(rec->p, dir);
	return (1);
}


int	near_zero(const t_vector *vec)
{
	const double s = 1e-8;
	return ((fabs(vec->x) < s) && (fabs(vec->y) < s) && fabs(vec->z) < s);
}

void	get_prompt_color(t_minirt *s)
{
	int x = 0;
	int y = HEIGHT;
	t_color color = init_color(100,100,100);

	while (y < HEIGHT + 32)
	{
		x = 0;
		while (x < WIDTH)
		{
			s->buf[y][x] = get_hexa_color(color);
			x++;
		}
		y++;
		color.r = color.r - 2;
		color.g = color.g - 2;
		color.b = color.b - 2;
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

	clock_t start, end;
	double elapsed;

	start = clock(); 
	//get_multi_threading(s);
	get_no_multi_threading(s); //sans thread pour la mandatory
	get_prompt_color(s);
	end = clock();
   	elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
   	printf("Temps d'exécution : %lf secondes\n", elapsed);
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
	
