#include "miniRT.h"

void	set_face_normal(const t_rayon *r, t_hit_record *rec,
		t_vector outward_normal)
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

int	scatter_lambertian(const t_rayon *r, const t_hit_record *rec,
	t_color *attenuation, t_rayon *scattered)
{
	t_vector	scatter_dir;
	(void)r;
	scatter_dir = add_(vec3_unit_vector(rec->normal), random_in_unit_sphere());
	if (near_zero(&scatter_dir))
		scatter_dir = rec->normal;
	*scattered = init_rayon(rec->p, scatter_dir);
	*attenuation = rec->mat_ptr->albedo;
	return (1);
}

int	scatter_light(const t_rayon *r, const t_hit_record *rec,
	t_color *attenuation, t_rayon *scattered)
{
	t_vector	scatter_dir;
	(void) r;

	scatter_dir = add_(vec3_unit_vector(rec->normal), random_in_unit_sphere());
	if (near_zero(&scatter_dir))
		scatter_dir = rec->normal;
	*scattered = init_rayon(rec->p, scatter_dir);
	*attenuation = rec->mat_ptr->albedo;
	return (1);
}

t_vector	refract(const t_vector uv, const t_vector n, double etai_over_etat)
{
	double		cos_thtta;
	t_vector	r_out_perp;
	t_vector	r_out_parallel;

	cos_thtta = fmin(dot(mul_(uv, -1), n), 1.0);
	r_out_perp = mul_(add_(uv, mul_(n, cos_thtta)), etai_over_etat);
	r_out_parallel = mul_(n, -1 * sqrt(fabs(1.0 - length_squared(r_out_perp))));
	return (add_(r_out_perp, r_out_parallel));
}

t_vector	reflect(const t_vector v, const t_vector n)
{
	return (sub_(v, mul_(n, 2 * dot(v, n))));
}

// int	scatter_metal(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered)
// {
// 	t_vector	reflected;

// 	reflected = reflect(vec3_unit_vector(r->direction),
// 				vec3_unit_vector(rec->normal));
// 	*scattered = init_rayon(rec->p, add_(reflected, mul_(random_in_unit_sphere(),
// 				rec->mat_ptr->fuzz)));
// 	*attenuation = rec->mat_ptr->albedo;
// 	return (dot(scattered->direction, rec->normal) > 0);
// }

double	reflectance(double cos, double ref_i)
{
	double	r0;

	r0 = (1 - ref_i) / (1 + ref_i);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cos), 5));
}


// int	scatter_dielectric(const t_rayon *r, const t_hit_record *rec, t_color *attenuation, t_rayon *scattered)
// {
// 	double		refraction_ratio;
// 	t_vector	unit_dir;
// 	double		cos_theta;
// 	double		sin_theta;
// 	int			cannot_refract;
// 	t_vector	dir;

// 	*attenuation = init_color(1.0, 1.0, 1.0);
// 	if (rec->front_face)
// 		refraction_ratio = 1.0 / rec->mat_ptr->ir;
// 	else
// 		refraction_ratio = rec->mat_ptr->ir;
// 	unit_dir = vec3_unit_vector(r->direction);
// 	cos_theta = fmin(dot(mul_(unit_dir, -1), rec->normal), 1.0);
// 	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
// 	cannot_refract = refraction_ratio * sin_theta > 1.0;
// 	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
// 		dir = reflect(unit_dir, rec->normal);
// 	else
// 		dir = refract(unit_dir, rec->normal, refraction_ratio);
// 	*scattered = init_rayon(rec->p, dir);
// 	return (1);
// }

int	near_zero(const t_vector *vec)
{
	const double	s = 1e-8;

	return ((fabs(vec->x) < s) && (fabs(vec->y) < s) && fabs(vec->z) < s);
}
