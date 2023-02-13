#include "miniRT_bonus.h"

void	write_params(t_minirt *s, int fd)
{
	char	*tmp;

	t_obj *obj = s->obj;

	while (obj)
	{
		if (obj->type == SPHERE)
		{
			ft_putstr_fd("sp ", fd);
			print_axis(obj->u_.sp.center_axis, fd);
			ft_putnbr_fd(obj->u_.sp.diameter, fd);
			ft_putstr_fd(" ", fd);
			print_rgb(obj->mat.albedo, fd);			
		}
		else if (obj->type == CYLINDER)
		{
			ft_putstr_fd("cy ", fd);
			print_axis(obj->u_.cy.center, fd);
			print_axis(obj->u_.cy.dir_ax, fd);
			ft_putnbr_fd(obj->u_.cy.diameter, fd);
			ft_putstr_fd(" ", fd);
			ft_putnbr_fd(obj->u_.cy.height, fd);
			ft_putstr_fd(" ", fd);
			print_rgb(obj->mat.albedo, fd);
		}
		else if (obj->type == CONE)
		{
			ft_putstr_fd("co ", fd);
			print_axis(obj->u_.co.center, fd);
			print_axis(obj->u_.co.dir_ax, fd);
			ft_putnbr_fd(obj->u_.co.diameter, fd);
			ft_putstr_fd(" ", fd);
			ft_putnbr_fd(obj->u_.co.height, fd);
			ft_putstr_fd(" ", fd);
			print_rgb(obj->mat.albedo, fd);
		}
		else if (obj->type == PLANE)
		{
			ft_putstr_fd("pl ", fd);
			print_axis(obj->u_.pl.axis, fd);
			print_axis(obj->u_.pl.dir_ax, fd);
			print_rgb(obj->mat.albedo, fd);
		}
		ft_putstr_fd("\n", fd);
		obj = obj->next;
	}
	ft_putstr_fd("C ", fd);
	print_axis(s->cam_origin, fd);
	print_axis(s->cam_vec_dir, fd);
	ft_putnbr_fd(s->cam_fov, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("A ", fd);
	tmp = ft_itof_print(s->amb_light_ratio);
	ft_putstr_fd(tmp, fd);
	free(tmp);
	ft_putstr_fd(" ", fd);
	print_rgb(s->amb_light_color, fd);
	ft_putstr_fd("\n", fd);

	t_light *li = s->li;
	while (li)
	{
		ft_putstr_fd("L ", fd);
		print_axis(li->light_axis, fd);
		tmp = ft_itof_print(li->light_brightness_ratio);
		ft_putstr_fd(tmp, fd);
		free(tmp);
		ft_putstr_fd(" ", fd);
		print_rgb(li->light_color, fd);
		ft_putstr_fd("\n", fd);
		li = li->next;
	}
}

void	export_file_save(t_minirt *s, int opt)
{
	int fd;
	if (opt == 1)
		fd = open("save.rt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
	{
		fd = open("autosave.rt", O_WRONLY | O_CREAT | O_APPEND, 0777);
		ft_putstr_fd("============\n", fd);
	}
	write_params(s, fd);
	close(fd);

}

