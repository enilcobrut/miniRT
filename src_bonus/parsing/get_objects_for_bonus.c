#include "miniRT_bonus.h"

int	get_cone(t_minirt *s, t_list *p)
{
	t_obj		*new_obj;
	t_cone		*co;

	new_obj = NULL;
	if (nb_arg_tab(p->content) != 6 && nb_arg_tab(p->content) != 7)
		exit_error(s, "A cylinder parameters aren't compliant", 1);
	new_obj = lst_add_obj(&s->obj, lst_new_obj(CONE));
	co= &new_obj->u.co;
	get_axis(s, &co->center, p->content[1], 0);
	get_axis(s, &co->dir_ax, p->content[2], 0);
	check_vector_range(s, &co->dir_ax);
	check_float_format(s, p->content[3]);
	co->diameter = ft_atof(s, p->content[3], 0, 0);
	co->radius = co->diameter / 2;
	check_float_format(s, p->content[4]);
	co->height = ft_atof(s, p->content[4], 0, 0);
	/*new_obj->mat.albedo = map_color(get_rgb_str_to_color(s, p->content[5], 0));
	new_obj->mat.scatter = MATERIAL(new_obj);*/
	if (p->content[7])
	{
		new_obj->xpm = p->content[7];
		check_xpm(s, new_obj);
	}
	return (1);
}