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

double	reflectance(double cos, double ref_i)
{
	double	r0;

	r0 = (1 - ref_i) / (1 + ref_i);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cos), 5));
}

int	near_zero(const t_vector *vec)
{
	const double	s = 1e-8;

	return ((fabs(vec->x) < s) && (fabs(vec->y) < s) && fabs(vec->z) < s);
}
