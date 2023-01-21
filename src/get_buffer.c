#include "miniRT.h"

int	hit_sphere(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max);
int	hit(const t_rayon *r, double t_min, double t_max, t_hit_record *rec, t_obj *obj);
static inline void set_face_normal(const t_rayon *r, t_hit_record *rec, t_vector outward_normal);


/****************************************************************************************************/

double	vec3_length(t_vector a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vector	vec3_unit_vector(t_vector a) 
{
    double length = vec3_length(a);

    return (t_vector) { a.x / length, a.y / length, a.z / length };
}

t_color color_add_(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_color	color_mul_scalar(t_color a, double b)
{
	return ((t_color){a.r * b, a.g * b, a.b * b});
}

t_color	ray_color(const t_rayon *r, t_minirt *s)
{
	t_vector unit_dir;
	t_hit_record rec;


	if (hit(r, 0, 10000, &rec, s->obj))
	{
		double light = dot(get_normalize_vector(sub_(s->light_axis, rec.p)), get_normalize_vector(rec.normal));
		if (light < 0) light = 0;
		// t_vector N = rec.normal;
		// /*t_color color;
		//  = {color.r, a.g + b.g, a.b + b.b};*/
		// const t_color test = (t_color) {N.x + 1, N.y + 1, N.z + 1};
		return (color_mul_scalar(rec.color, light * .5 + .5));
	}
	unit_dir = vec3_unit_vector(r->direction);
	double t = 0.5 * (unit_dir.y + 1.0);
	t_color white = (t_color) {1.0, 1, 1};
	t_color blue = (t_color) {0.5, 0.7, 1};
	return (color_add_(color_mul_scalar(white, 1.0 - t), color_mul_scalar(blue, t)));
}

static inline double length_squared(t_vector v)
{
	return (v.x*v.x + v.y*v.y + v.z*v.z);
}

static inline void set_face_normal(const t_rayon *r, t_hit_record *rec, t_vector outward_normal)
{
	rec->front_face = dot(r->direction, outward_normal) < 0;
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = mul_(outward_normal, -1);
}


t_color map_color(t_color color)
{
	return ((t_color) {color.r / 255, color.g / 255, color.b / 255});

}

int	hit(const t_rayon *r, double t_min, double t_max, t_hit_record *rec, t_obj *obj)
{
	t_hit_record temp_rec;
	int	hit_anything = 0;
	double closest_so_far = t_max;

	while (obj)
	{
		if (obj->type == SPHERE && hit_sphere(&obj->u.sp, r, &temp_rec, t_min, t_max))
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->color = map_color(obj->u.sp.color);
		}
		/*else if (obj->type == PLANE && hit_plane(&obj->u.pl, r, &temp_rec, t_min, t_max))
		else if (obj->type == CYLINDER && hit_plane(&obj->u.cy, r, &temp_rec, t_min, t_max))*/
		obj = obj->next;
	}
	return (hit_anything);
}

int	hit_sphere(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	t_vector oc = sub_(r->origine, sp->center_axis);
	double a = length_squared(r->direction);
	double half_b = dot(oc, r->direction);
	double c = length_squared(oc) - sp->radius*sp->radius;
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

void	get_buffer(t_minirt *s, int opt)
{
	t_vector horizon;
	t_vector vertical;
	t_vector lower_left_corner;
	t_vector origin; //camera
	t_vector vec3;
	double mul_t_u;
	double mul_t_v;
	t_rayon		r;
	t_color	 pixel_color;
	double viewport_height = 2.0;
	double viewport_width = ((double)WIDTH/HEIGHT) * viewport_height;
	horizon.x = viewport_width;
	horizon.y = 0;
	horizon.z = 0;
	vertical.x = 0;
	vertical.y = viewport_height;
	vertical.z = 0;

	origin.x = s->cam_view_point_axis.x;
	origin.y = s->cam_view_point_axis.y;
	origin.z = s->cam_view_point_axis.z;
	lower_left_corner = sub_(sub_(origin, div_(horizon, 2)), sub_(div_(vertical, 2), init_vector(0, 0, 1)));
	
	for (int y = HEIGHT - 1; y >= 0; --y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			mul_t_u = (double)x / (WIDTH - 1);
			mul_t_v = (double)y / (HEIGHT - 1);
			r = init_rayon(origin, add_(add_(lower_left_corner, mul_(horizon, mul_t_u)), sub_(mul_(vertical, mul_t_v), origin)));
			pixel_color = ray_color(&r, s);
			s->buf[HEIGHT - y - 1][x] = create_trgb(0, pixel_color.r * 255, pixel_color.g * 255, pixel_color.b * 255);
		}
	}
}