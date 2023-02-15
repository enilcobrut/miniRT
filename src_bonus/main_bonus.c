/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:13:40 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 14:13:43 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	red_cross(t_minirt *s)
{
	mlx_destroy_window(s->mlx, s->win);
	export_file_save(s, 2);
	exit_error(s, 0, -1);
	return (0);
}

void	print_cone(t_cone *co, int nb)
{
	printf("\033[45m 🍦 Cone #%d  \033[0m\n", nb);
	printf("\033[35m Coordinates \033[0m                     ");
	printf("[%0.1f]", co->center.x);
	printf("[%0.1f]", co->center.y);
	printf("[%0.1f]\n", co->center.z);
	printf("\033[35m 3d normalized orientation vector \033[0m");
	printf("[%0.1f]", co->dir_ax.x);
	printf("[%0.1f]", co->dir_ax.y);
	printf("[%0.1f]\n", co->dir_ax.z);
	printf("\033[35m Diameter \033[0m[%0.1f]", co->diameter);
	printf("\033[35m Height \033[0m[%0.2f]", co->height);
}

void	print_obj(t_obj *obj)
{
	while (obj)
	{
		if (obj->type == SPHERE)
			print_sphere(&obj->u_.sp, obj->n);
		else if (obj->type == PLANE)
			print_plane(&obj->u_.pl, obj->n);
		else if (obj->type == CYLINDER)
			print_cylinder(&obj->u_.cy, obj->n);
		else if (obj->type == CONE)
			print_cone(&obj->u_.co, obj->n);
		printf("\033[35m Color \033[0m[%x]\n\n", print_color(obj->mat.albedo));
		obj = obj->next;
	}
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
	print_lights(s->li);
	print_obj(s->obj);
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
	check_void(s, 0);
	check_directory(s);
	check_extension_rt(s);
	init_set(s);
	get_params(s);
	get_identifiers(s, 0, 0, 0);
	start_ray_tracing(s);
}
