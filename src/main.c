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
	printf("\033[35m Color \033[0m[%x]\n\n", print_color(sp->color));
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
	printf("\033[35m Color                            \033[0m[%x]\n\n", print_color(pl->color));
}

void	print_cylinder(t_cylinder *cy, int nb)
{
	printf("\033[45m 🧨 Cylinder #%d  \033[0m\n", nb);
	printf("\033[35m Coordinates \033[0m                     ");
	printf("[%0.1f]", cy->axis.x);
	printf("[%0.1f]", cy->axis.y);
	printf("[%0.1f]\n", cy->axis.z);
	printf("\033[35m 3d normalized orientation vector \033[0m");
	printf("[%0.1f]", cy->norm_or_vector.x);
	printf("[%0.1f]", cy->norm_or_vector.y);
	printf("[%0.1f]\n", cy->norm_or_vector.z);
	printf("\033[35m Diameter \033[0m[%0.1f]", cy->diameter);
	printf("\033[35m Height \033[0m[%0.2f]", cy->height);
	printf("\033[35m Color \033[0m[%x]\n\n", print_color(cy->color));
}

void	print_params(t_minirt *s)
{
	printf("\n\033[45m 🕯  Ambient lightning  \033[0m\n");
	printf("\033[35m Ratio \033[0m[%0.1f]             ", s->amb_light_ratio);
	printf("\033[35mColor\033[0m [%x]\n\n", print_color(s->amb_light_color));
	printf("\033[45m 🎥 Camera  \033[0m\n");
	printf("\033[35m View point\033[0m                    ");
	printf("[%0.1f]", s->cam_view_point_axis.x);
	printf("[%0.1f]", s->cam_view_point_axis.y);
	printf("[%0.1f]\n", s->cam_view_point_axis.z);
	printf("\033[35m Normalized orientation vector \033[0m");
	printf("[%0.1f]", s->cam_norm_or_vector_axis.x);
	printf("[%0.1f]", s->cam_norm_or_vector_axis.y);
	printf("[%0.1f]\n", s->cam_norm_or_vector_axis.z);
	printf("\033[35m Horizontal field of view \033[0m     ");
	printf("[%d]°\n\n", s->cam_hor_field_view);
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
		obj = obj->next;
	}
}


void	get_keyboard(t_minirt *s)
{
	s->k[0] = "a";
	s->k[1] = "s";
	s->k[2] = "d";
	s->k[3] = "f";
	s->k[4] = "h";
	s->k[5] = "g";
	s->k[6] = "z";
	s->k[7] = "x";
	s->k[8] = "c";
	s->k[9] = "v";
	s->k[10] = "";
	s->k[11] = "b";
	s->k[12] = "q";
	s->k[13] = "w";
	s->k[14] = "e";
	s->k[15] = "r";
	s->k[16] = "y";
	s->k[17] = "t";
	s->k[18] = "1";
	s->k[19] = "2";
	s->k[20] = "3";
	s->k[21] = "4";
	s->k[22] = "6";
	s->k[23] = "5";
	s->k[24] = "+";
	s->k[25] = "9";
	s->k[26] = "7";
	s->k[27] = "-";
	s->k[28] = "8";
	s->k[29] = "0";
	s->k[30] = "]";
	s->k[31] = "o";
	s->k[32] = "u";
	s->k[33] = "[";
	s->k[34] = "i";
	s->k[35] = "p";
	s->k[36] = ""; // enter
	s->k[37] = "l";
	s->k[38] = "j";
	s->k[39] = "'";
	s->k[40] = "k";
	s->k[41] = ";";
	s->k[42] = "\\";
	s->k[43] = ",";
	s->k[44] = "/";
	s->k[45] = "n";
	s->k[46] = "m";
	s->k[47] = ".";
	s->k[48] = ""; //tab
	s->k[49] = " ";
	s->k[50] = "`";
	s->k[51] = "";//backspace
	// CAPS 264/*
	// - pav*/e 78
}

int	main(int argc, char **argv)
{
	t_minirt	*s;

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
	get_keyboard(s);
	if (PRINT == 1)
		print_params(s);
	if (EXEC == 1)
		start_ray_tracing(s);
	if (LEAKS == 1)
		system("leaks miniRT");
	exit(EXIT_SUCCESS);
}
