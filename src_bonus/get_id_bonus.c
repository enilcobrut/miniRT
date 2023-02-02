
#include "miniRT_bonus.h"

void	get_identifiers(t_minirt *s, int a, int c, int l)
{
	t_list	*cursor;

	cursor = s->params;
	printf("%d\n", ft_lstsize(s->params));
	while (cursor)
	{
		if (!ft_strncmp(cursor->content[0], "A", 2)
			&& get_ambient_light_scene_par(s, cursor))
			a++;
		else if (!ft_strncmp(cursor->content[0], "C", 2)
			&& get_camera_par(s, cursor))
			c++;
		else if (!ft_strncmp(cursor->content[0], "L", 2)
			&& get_light_scene_par(s, cursor))
			l++;
		else
			get_objects(s, cursor);
		cursor = cursor->next;
	}
	if (a != 1 || c != 1 || l == 0)
		exit_error(s, "Should get one A, one C & at least one L", 1);
}

int	get_ambient_light_scene_par(t_minirt *s, t_list *p)
{
	if (nb_arg_tab(p->content) != 3)
		exit_error(s, "Ambient light parameters not compliant", 1);
	check_float_format(s, p->content[1]);
	s->amb_light_ratio = ft_atof(s, p->content[1], 0, 0);
	if (s->amb_light_ratio < 0 || s->amb_light_ratio > 1)
		exit_error(s, "Ambient lighting ratio is not in range [0,1]", 1);
	s->amb_light_color = map_color(get_rgb_str_to_color(s, p->content[2], 0));
	return (1);
}

int	get_camera_par(t_minirt *s, t_list *p)
{
	if (nb_arg_tab(p->content) != 4)
		exit_error(s, "Camera parameters not compliant", 1);
	get_axis(s, &s->cam_origin, p->content[1], 0);
	get_axis(s, &s->cam_vec_dir, p->content[2], 0);
	check_vector_range(s, &s->cam_vec_dir);
	s->cam_vec_dir = vec3_unit_vector(s->cam_vec_dir);
	check_integer_format(s, p->content[3]);
	s->cam_fov = ft_atoi(p->content[3]);
	if (ft_strncmp(p->content[3], "0", 2) && !s->cam_fov)
		exit_error(s, "A number is > INT_MAX", 1);
	if (s->cam_fov >= 180 || s->cam_fov <= 0)
		exit_error(s, "Horizontal field of view not in range [0,180]", 1);
	return (1);
}

int	get_light_scene_par(t_minirt *s, t_list *p)
{	
	t_light *li;
	static int nb;
	
	nb++;
	if (nb_arg_tab(p->content) != 4)
		exit_error(s, "Light parameters not compliant", 1);
	li = lst_add_light(&s->li, lst_new_light(nb));
	get_axis(s, &li->light_axis, p->content[1], 0);
	check_float_format(s, p->content[2]);
	li->light_brightness_ratio = ft_atof(s, p->content[2], 0, 0);
	if (li->light_brightness_ratio < 0 || li->light_brightness_ratio > 1)
		exit_error(s, "Light brightness ratio are not in range [0,1]", 1);
	li->light_color = map_color(get_rgb_str_to_color(s, p->content[3], 0));
	return (1);
}

void	get_objects(t_minirt *s, t_list *p)
{
	static int nb;
	t_obj *curr;

	nb++;
	if (!ft_strncmp(p->content[0], "pl", 3))
		get_plane(s, p);
	else if (!ft_strncmp(p->content[0], "sp", 3))
		get_sphere(s, p);
	else if (!ft_strncmp(p->content[0], "cy", 3))
		get_cylinder(s, p);
	else
		exit_error(s, p->content[0], 1);
	curr = lst_last_obj(&s->obj);
	curr->n = nb;
}
