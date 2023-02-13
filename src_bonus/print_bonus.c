/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:21:46 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/13 19:56:39 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	print_color(t_color color)
{	
	return ((int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

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

void	print_lights(t_light *li)
{
	while (li)
	{
		printf("\033[45m 🔦 Light #%d  \033[0m\n", li->n);
		printf("\033[35m Light point \033[0m");
		printf("[%0.1f]", li->light_axis.x);
		printf("[%0.1f]", li->light_axis.y);
		printf("[%0.1f]", li->light_axis.z);
		printf("\033[35m View point \033[0m");
		printf("[%0.1f]\n", li->light_brightness_ratio);
		printf("\033[35m Color\033[0m       [%x]\n\n",
			print_color(li->light_color));
		li = li->next;
	}
}
