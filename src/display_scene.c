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

t_color	ray_color(const t_rayon *r, t_minirt *s, int depth)
{
	t_vector unit_dir;
	t_hit_record rec;
	
	if (depth <= 0)
		return (init_color(0, 0, 0));

	if (hit(r, 0.001, INF, &rec, s->obj))
	{
		t_rayon scattered;
		t_color attenuation;
		// t_vector target = add_(add_(rec.p, get_normalize_vector(rec.normal)), random_in_unit_vector());
		// t_rayon new_ray = init_rayon(rec.p, sub_(target, rec.p));
		if (rec.mat_ptr->scatter(r, &rec, &attenuation, &scattered))
			return (color_mul(attenuation, ray_color(&scattered, s, depth - 1)));
		return (init_color(0,0,0));
		//return (color_mul_scalar(ray_color(&new_ray, s, depth - 1), 0.5));
		//double light = dot(get_normalize_vector(sub_(s->light_axis, rec.p)), get_normalize_vector(rec.normal));
		//if (light < 0) light = 0;
	
		// t_vector N = rec.normal;
		// /*t_color color;
		//  = {color.r, a.g + b.g, a.b + b.b};*/
		// const t_color test = (t_color) {N.x + 1, N.y + 1, N.z + 1};
		

		//return (color_mul_scalar(rec.color, light * .5 + .5));
	}
	unit_dir = vec3_unit_vector(r->direction);
	double t = 0.5 * (unit_dir.y + 1.0);
	t_color white = (t_color) {1.0, 1, 1};
	t_color blue = (t_color) {0.5, 0.7, 1};
	return (color_add_(color_mul_scalar(white, 1.0 - t), color_mul_scalar(blue, t)));
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



int	hit_plane(t_plane *pl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
  //  if (denom > 0.000001/*1e-6*/) {
      //  t_vector p0l0 = sub_(pl->axis, r->origine);
        //t = dot(get_normalize_vector(p0l0), get_normalize_vector(pl->norm_or_vector)) / denom;
	double t = dot(sub_(pl->axis, r->origine), pl->norm_or_vector) / dot(r->direction, pl->norm_or_vector);
		if (t < t_min || t_max < t)
		{
			return (0);
			//rec->t = t;
       	//	return (t >= 0);
		}
		rec->t = t;
		rec->p = add_(r->origine, mul_(r->direction, rec->t));
		rec->normal = pl->norm_or_vector;
		return (1);
}
	
/*
	t_vector oc = sub_(r->origine, sp->center_axis);
	double a = length_squared(r->direction);
	double half_b = dot(oc, r->direction);
	double c = length_squared(oc) - sp->radius * sp->radius;
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
	set_face_normal(r, rec, div_(sub_(rec->p, sp->center_axis), sp->radius));
	*/




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
		/*else if (obj->type == CYLINDER && hit_plane(&obj->u.cy, r, &temp_rec, t_min, t_max))*/
		obj = obj->next;
	}
	return (hit_anything);
}

int	hit_sphere(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	t_vector oc = sub_(r->origine, sp->center_axis);
	double a = length_squared(r->direction);
	double half_b = dot(oc, r->direction);
	double c = length_squared(oc) -  sp->radius*  sp->radius;
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
	t_vector scatter_dir = add_(vec3_unit_vector(rec->normal), random_in_unit_vector());
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
	double scale = 1.0 / sample_per_pixel;
	t_color new_c;
	new_c.r = sqrt(pixel_color.r * scale);
	new_c.g = sqrt(pixel_color.g * scale);
	new_c.b = sqrt(pixel_color.b * scale);
	return (create_trgb(0, clamp(new_c.r, 0.0, 0.999) * 256,  clamp(new_c.g, 0.0, 0.999) * 256,  clamp(new_c.b, 0.0, 0.999) * 255));
}

void	get_buffer(t_minirt *s, int opt)
{
	(void)opt;
	t_vector horizon;
	t_vector vertical;
	t_vector lower_left_corner;
	t_vector origin;
	t_vector vup;
	double	theta = degrees_to_radians(s->cam_hor_field_view);
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
	t_vector w = vec3_unit_vector(sub_(s->cam_origin, s->cam_norm_or_vector_axis));
	t_vector u = vec3_unit_vector(vec_cross(vup, w));
	t_vector v = vec_cross(w, u);
	origin = s->cam_origin;
	horizon = mul_(u, viewport_width);
	vertical = mul_(v, viewport_height);
	const int samples_per_pixel = 50;
	const int max_depth = 10;
	// Camera
	//double focal_length = 1.0;
	// origin.x = s->cam_origin.x;
	// origin.y = s->cam_origin.y;
	// origin.z = s->cam_origin.z;
	lower_left_corner = sub_(origin, sub_())
	lower_left_corner = sub_(sub_(origin, div_(horizon, 2)), sub_(div_(vertical, 2), s->cam_norm_or_vector_axis/*init_vector(0, 0, focal_length*/));
	
	// Render
	
	for (int y = HEIGHT - 1; y >= 0; --y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			pixel_color.r = 0;
			pixel_color.g = 0;
			pixel_color.b = 0;
			for (int i = 0; i < samples_per_pixel; ++i)
			{
				mul_t_u = ((double)x + random_double()) / (double)(WIDTH - 1);
				mul_t_v = ((double)y + random_double()) / (double)(HEIGHT - 1);
				r = init_rayon(origin, add_(add_(lower_left_corner, mul_(horizon, mul_t_u)), sub_(mul_(vertical, mul_t_v), origin)));
				pixel_color = color_add_(pixel_color, ray_color(&r, s, max_depth));
			}
			s->buf[HEIGHT - y - 1][x] = write_color(pixel_color, samples_per_pixel);
		}
	}
}