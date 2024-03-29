/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:39:28 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/15 19:12:21 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_sphere(t_minirt *s, t_list *p)
{
	t_obj		*new_obj;
	t_sphere	*sp;

	new_obj = NULL;
	if (nb_arg_tab(p->content) != 4)
		exit_error(s, "A sphere parameters aren't compliant", 1);
	new_obj = lst_add_obj(&s->obj, lst_new_obj(SPHERE));
	sp = &new_obj->u_.sp;
	get_axis(s, &sp->center_axis, p->content[1], 0);
	sp->diameter = ft_atof(s, p->content[2], 0, 0);
	sp->radius = sp->diameter / 2;
	new_obj->mat.albedo = map_color(get_rgb_str_to_color(s, p->content[3], 0));
	return (1);
}

int	get_plane(t_minirt *s, t_list *p)
{
	t_obj		*new_obj;
	t_plane		*pl;

	new_obj = NULL;
	if (nb_arg_tab(p->content) != 4)
		exit_error(s, "A plane parameters aren't compliant", 1);
	new_obj = lst_add_obj(&s->obj, lst_new_obj(PLANE));
	pl = &new_obj->u_.pl;
	get_axis(s, &pl->axis, p->content[1], 0);
	get_axis(s, &pl->dir_ax, p->content[2], 0);
	check_vector_range(s, &pl->dir_ax);
	pl->dir_ax = norm_(pl->dir_ax);
	new_obj->mat.albedo = map_color(get_rgb_str_to_color(s, p->content[3], 0));
	return (1);
}

int	get_cylinder(t_minirt *s, t_list *p)
{
	t_obj		*new_obj;
	t_cylinder	*cy;

	new_obj = NULL;
	if (nb_arg_tab(p->content) != 6)
		exit_error(s, "A cylinder parameters aren't compliant", 1);
	new_obj = lst_add_obj(&s->obj, lst_new_obj(CYLINDER));
	cy = &new_obj->u_.cy;
	get_axis(s, &cy->center, p->content[1], 0);
	get_axis(s, &cy->dir_ax, p->content[2], 0);
	check_vector_range(s, &cy->dir_ax);
	cy->dir_ax = norm_(cy->dir_ax);
	check_float_format(s, p->content[3]);
	cy->diameter = ft_atof(s, p->content[3], 0, 0);
	cy->radius = cy->diameter * 0.5;
	check_float_format(s, p->content[4]);
	cy->height = ft_atof(s, p->content[4], 0, 0);
	new_obj->mat.albedo = map_color(get_rgb_str_to_color(s, p->content[5], 0));
	cy->ratio = cy->height / cy->diameter;
	return (1);
}
