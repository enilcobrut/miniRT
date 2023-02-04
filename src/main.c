#include "miniRT.h"

int	print_color(t_color color)
{	
	return ((int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

void print_sphere(t_sphere *sp, int nb)
{

	printf("\033[45m ⚪️ Sphere #%d  \033[0m\n", nb);
	printf("\033[35m Coordinates of the sphere center \033[0m");
	printf("[%0.1f]", sp->center_axis.x);
	printf("[%0.1f]", sp->center_axis.y);
	printf("[%0.1f]\n", sp->center_axis.z);
	printf("\033[35m Diameter \033[0m[%0.1f]           ", sp->diameter);
	// printf("\033[35m Color \033[0m[%x]\n\n", print_color(sp->color));
}

void print_plane(t_plane *pl, int nb)
{
	printf("\033[45m 🛩  Plane #%d  \033[0m\n", nb);
	printf("\033[35m Coordinates\033[0m                      ");
	printf("[%0.1f]", pl->axis.x);
	printf("[%0.1f]", pl->axis.y);
	printf("[%0.1f]\n", pl->axis.z);
	printf("\033[35m 3d normalized orientation vector \033[0m");
	printf("[%0.1f]", pl->norm_or_vector.x);
	printf("[%0.1f]", pl->norm_or_vector.y);
	printf("[%0.1f]\n", pl->norm_or_vector.z);
	// printf("\033[35m Color                            \033[0m[%x]\n\n", print_color(pl->color));
}

void	print_cylinder(t_cylinder *cy, int nb)
{
	printf("\033[45m 🧨 Cylinder #%d  \033[0m\n", nb);
	printf("\033[35m Coordinates \033[0m                     ");
	printf("[%0.1f]", cy->center.x);
	printf("[%0.1f]", cy->center.y);
	printf("[%0.1f]\n", cy->center.z);
	printf("\033[35m 3d normalized orientation vector \033[0m");
	printf("[%0.1f]", cy->dir_ax.x);
	printf("[%0.1f]", cy->dir_ax.y);
	printf("[%0.1f]\n", cy->dir_ax.z);
	printf("\033[35m Diameter \033[0m[%0.1f]", cy->diameter);
	printf("\033[35m Height \033[0m[%0.2f]", cy->height);
	// printf("\033[35m Color \033[0m[%x]\n\n", print_color(cy->color));
}

void	print_params(t_minirt *s)
{
	printf("\n\033[45m 🕯  Ambient lightning  \033[0m\n");
	printf("\033[35m Ratio \033[0m[%0.1f]             ", s->amb_light_ratio);
	printf("\033[35mColor\033[0m [%x]\n\n", print_color(s->amb_light_color));
	printf("\033[45m 🎥 Camera  \033[0m\n");
	printf("\033[35m View point\033[0m                    ");
	printf("[%0.1f]", s->cam_origin.x);
	printf("[%0.1f]", s->cam_origin.y);
	printf("[%0.1f]\n", s->cam_origin.z);
	printf("\033[35m Normalized orientation vector \033[0m");
	printf("[%0.1f]", s->cam_vec_dir.x);
	printf("[%0.1f]", s->cam_vec_dir.y);
	printf("[%0.1f]\n", s->cam_vec_dir.z);
	printf("\033[35m Horizontal field of view \033[0m     ");
	printf("[%d]°\n\n", s->cam_fov);
	printf("\033[45m 🔦 Light  \033[0m\n");
	printf("\033[35m Light point \033[0m");
	printf("[%0.1f]", s->light_axis.x);
	printf("[%0.1f]", s->light_axis.y);
	printf("[%0.1f]", s->light_axis.z);
	printf("\033[35m View point \033[0m");
	printf("[%0.1f]\n", s->light_brightness_ratio);
	printf("\033[35m Color\033[0m       [%x]\n\n", print_color(s->light_color));
	t_obj *obj = s->obj;
	while (obj)
	{
		if (obj->type == SPHERE)
			print_sphere(&obj->u.sp, obj->n);
		else if (obj->type == PLANE)
			print_plane(&obj->u.pl, obj->n);
		else if (obj->type == CYLINDER)
			print_cylinder(&obj->u.cy, obj->n);
		printf("\033[35m Color \033[0m[%x]\n\n", print_color(obj->mat.albedo));
		obj = obj->next;
	}
}


int	main(int argc, char **argv)
{
	t_minirt	*s;

	srand(time(NULL));
	s = ft_calloc(sizeof(t_minirt), 1);
	if (!s)
		exit_error(s, 0, 0);
	s->argv = argv;
	s->argc = argc;
	if (PARSING == 1)
	{
		check_void(s, 0);
		check_directory(s);
		check_extension_rt(s);
	}
	init_set(s);
	get_params(s);
	get_identifiers(s, 0, 0, 0);
	if (PRINT == 1)
		print_params(s);
	if (EXEC == 1)
		start_ray_tracing(s);
	if (LEAKS == 1)
		system("leaks miniRT");
	exit(EXIT_SUCCESS);
}
