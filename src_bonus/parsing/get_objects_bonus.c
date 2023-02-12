/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:13:10 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 21:14:11 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

#define FUZZ 0.5
#define IR 1.5
//#define MATERIAL scatter_metal

void	check_xpm(t_minirt *s, t_obj *obj)
{
	int	null;

	obj->bump_map = mlx_xpm_file_to_image(s, obj->xpm, &obj->bump_width,
			&obj->bump_height);
	if (!obj->bump_map)
		exit_error(s, "Error with the xpm file", 1);
	obj->bump_map_addr = (int *)mlx_get_data_addr(obj->bump_map, &null,
			&null, &null);
}

int	get_sphere(t_minirt *s, t_list *p)
{
	t_obj		*new_obj;
	t_sphere	*sp;

	new_obj = NULL;
	if (nb_arg_tab(p->content) != 4 && nb_arg_tab(p->content) != 5)
		exit_error(s, "A sphere parameters aren't compliant", 1);
	new_obj = lst_add_obj(&s->obj, lst_new_obj(SPHERE));
	sp = &new_obj->u_.sp;
	get_axis(s, &sp->center_axis, p->content[1], 0);
	sp->diameter = ft_atof(s, p->content[2], 0, 0);
	sp->radius = sp->diameter / 2;
	new_obj->mat.albedo = map_color(get_rgb_str_to_color(s, p->content[3], 0));
	new_obj->mat.scatter = MATERIAL(new_obj);
	new_obj->mat.fuzz = FUZZ;
	new_obj->mat.ir = IR;
	if (new_obj->mat.fuzz > 1)
		new_obj->mat.fuzz = 1;
	if (p->content[4])
	{
		new_obj->xpm = p->content[4];
		check_xpm(s, new_obj);
	}
	return (1);
}

int	get_plane(t_minirt *s, t_list *p)
{
	t_obj		*new_obj;
	t_plane		*pl;

	new_obj = NULL;
	if (nb_arg_tab(p->content) != 4 && nb_arg_tab(p->content) != 5)
		exit_error(s, "A plane parameters aren't compliant", 1);
	new_obj = lst_add_obj(&s->obj, lst_new_obj(PLANE));
	pl = &new_obj->u_.pl;
	get_axis(s, &pl->axis, p->content[1], 0);
	get_axis(s, &pl->dir_ax, p->content[2], 0);
	check_vector_range(s, &pl->dir_ax);
	new_obj->mat.albedo = map_color(get_rgb_str_to_color(s, p->content[3], 0));
	new_obj->mat.scatter = MATERIAL(new_obj);
	if (p->content[4])
	{
		new_obj->xpm = p->content[4];
		check_xpm(s, new_obj);
	}
	return (1);
}

int	get_cylinder(t_minirt *s, t_list *p)
{
	t_obj		*new_obj;
	t_cylinder	*cy;

	new_obj = NULL;
	if (nb_arg_tab(p->content) != 6 && nb_arg_tab(p->content) != 7)
		exit_error(s, "A cylinder parameters aren't compliant", 1);
	new_obj = lst_add_obj(&s->obj, lst_new_obj(CYLINDER));
	cy = &new_obj->u_.cy;
	get_axis(s, &cy->center, p->content[1], 0);
	get_axis(s, &cy->dir_ax, p->content[2], 0);
	check_vector_range(s, &cy->dir_ax);
	check_float_format(s, p->content[3]);
	cy->diameter = ft_atof(s, p->content[3], 0, 0);
	cy->radius = cy->diameter / 2;
	check_float_format(s, p->content[4]);
	cy->height = ft_atof(s, p->content[4], 0, 0);
	new_obj->mat.albedo = map_color(get_rgb_str_to_color(s, p->content[5], 0));
	new_obj->mat.scatter = MATERIAL(new_obj);
	cy->ratio = cy->height / cy->diameter;
	if (p->content[6])
	{
		new_obj->xpm = p->content[6];
		check_xpm(s, new_obj);
	}
	return (1);
}
