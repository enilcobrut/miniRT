/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:44:05 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/11 11:22:18 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_sphere(t_sphere *sp, int nb)
{
	printf("\033[45m ⚪️ Sphere #%d  \033[0m\n", nb);
	printf("\033[35m Coordinates of the sphere center \033[0m");
	printf("[%0.1f]", sp->center_axis.x);
	printf("[%0.1f]", sp->center_axis.y);
	printf("[%0.1f]\n", sp->center_axis.z);
	printf("\033[35m Diameter \033[0m[%0.1f]           ", sp->diameter);
}

void	print_plane(t_plane *pl, int nb)
{
	printf("\033[45m 🛩  Plane #%d  \033[0m\n", nb);
	printf("\033[35m Coordinates\033[0m                      ");
	printf("[%0.1f]", pl->axis.x);
	printf("[%0.1f]", pl->axis.y);
	printf("[%0.1f]\n", pl->axis.z);
	printf("\033[35m 3d normalized orientation vector \033[0m");
	printf("[%0.1f]", pl->dir_ax.x);
	printf("[%0.1f]", pl->dir_ax.y);
	printf("[%0.1f]\n", pl->dir_ax.z);
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
	printf("\033[45m 🔦 Light  \033[0m\n");
	printf("\033[35m Light point \033[0m");
	printf("[%0.1f]", s->light_axis.x);
	printf("[%0.1f]", s->light_axis.y);
	printf("[%0.1f]", s->light_axis.z);
	printf("\033[35m View point \033[0m");
	printf("[%0.1f]\n", s->light_brightness_ratio);
	printf("\033[35m Color\033[0m       [%x]\n\n", print_color(s->light_color));
	print_obj(s->obj);
}
