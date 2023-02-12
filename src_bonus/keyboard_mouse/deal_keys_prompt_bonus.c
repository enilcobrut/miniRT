
#include "miniRT_bonus.h"

void	type_key(t_minirt *s, char *tmp, int key)
{
	if (!s->prompt)
			s->prompt = ft_strdup("");
	tmp = ft_strjoin_char(s->prompt, s->k[key]);
	ft_free(&s->prompt);
	s->prompt = ft_strdup(tmp);
	ft_free(&tmp);
}

void	key_backspace(t_minirt *s, char *tmp)
{
	if (s->prompt)
	{
		tmp = ft_strdup(s->prompt);
		ft_free(&s->prompt);
		s->prompt = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		ft_free(&tmp);
	}
}

void	display_prompt_status(t_minirt *s)
{
	if (s->prompt_stat == 1)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0x00FF00, "*");
	else
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
}

void	write_params(t_minirt *s, int fd)
{
	(void)fd;
	printf("C %0.1f,%0.1f,%0.1f %0.1f,%0.1f,%0.1f %d\n", s->cam_origin.x,
			s->cam_origin.y, s->cam_origin.z,
	s->cam_vec_dir.x, s->cam_vec_dir.y, s->cam_vec_dir.z, s->cam_fov);
	printf("A %0.1f %0.1f,%0.1f,%0.1f\n", s->amb_light_ratio,
			s->amb_light_color.r * 255, s->amb_light_color.g * 255,
			s->amb_light_color.b * 255);
	
	while (s->li)
	{
		printf("L %0.1f,%0.1f,%0.1f %0.1f %0.1f,%0.1f,%0.1f\n", s->li->light_axis.x, s->li->light_axis.y, s->li->light_axis.z,
			   s->li->light_brightness_ratio, s->li->light_color.r, s->li->light_color.g, s->li->light_color.b);
		s->li = s->li->next;
	}
	while (s->obj)
	{
		if (s->obj->type == SPHERE)
		{
			printf("sp %0.1f,%0.1f,%0.1f %0.1f %0.1f,%0.1f,%0.1f\n", s->obj->u_.sp.center_axis.x, s->obj->u_.sp.center_axis.y,
				   s->obj->u_.sp.center_axis.z, s->obj->u_.sp.diameter, s->obj->mat.albedo.r,
				   s->obj->mat.albedo.g, s->obj->mat.albedo.b);
		}
		else if (s->obj->type == CYLINDER)
		{
			printf("cy %0.1f,%0.1f,%0.1f %0.1f,%0.1f,%0.1f %0.1f %0.1f %0.1f,%0.1f,%0.1f\n", s->obj->u_.cy.center.x, s->obj->u_.cy.center.y, s->obj->u_.cy.center.z,
			 s->obj->u_.cy.dir_ax.x, s->obj->u_.cy.dir_ax.y, s->obj->u_.cy.dir_ax.z, s->obj->u_.cy.diameter,
			 s->obj->u_.cy.height, s->obj->mat.albedo.r, s->obj->mat.albedo.g, s->obj->mat.albedo.b);
		}
		else if (s->obj->type == CONE)
		{
			printf("co %0.1f,%0.1f,%0.1f %0.1f,%0.1f,%0.1f %0.1f %0.1f %0.1f,%0.1f,%0.1f\n", s->obj->u_.co.center.x, s->obj->u_.co.center.y, s->obj->u_.co.center.z,
			 s->obj->u_.co.dir_ax.x, s->obj->u_.co.dir_ax.y, s->obj->u_.co.dir_ax.z, s->obj->u_.co.diameter,
			 s->obj->u_.co.height, s->obj->mat.albedo.r, s->obj->mat.albedo.g, s->obj->mat.albedo.b);
		}
		else if (s->obj->type == PLANE)
		{
			printf("pl %0.1f,%0.1f,%0.1f %0.1f,%0.1f,%0.1f %0.1f,%0.1f,%0.1f\n", s->obj->u_.pl.axis.x, s->obj->u_.pl.axis.y, s->obj->u_.pl.axis.z,
			s->obj->u_.pl.dir_ax.x, s->obj->u_.pl.dir_ax.y, s->obj->u_.pl.dir_ax.z,
			s->obj->mat.albedo.r, s->obj->mat.albedo.g, s->obj->mat.albedo.b);
		}
		s->obj = s->obj->next;
	}
}

void	export_file_save(t_minirt *s)
{
	/*time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    (void)s;
	int date = tm->tm_sec + (tm->tm_min * 100) + (tm->tm_hour * 100) + (tm->tm_mon * 100) + ((tm->tm_year + 1900) * 10000);
	printf("%d\n", date);
	printf("%d\n", tm->tm_yday);*/
	(void)s;
	//int fd = open("save", O_WRONLY | O_CREAT | O_APPEND, 0777);
	//printf("%d\n", fd);
	write_params(s, 0);

}

void	print_list_id(void)
{
	printf("C / coordinates of the view point / 3d normalized orientation ");
	printf("vector / FOV\n");
	printf("A / ambient lighting ratio in range [0.0,1.0] / Color RGB\n");
	printf("L / coordinates of the light point / light brightness ratio in ");
	printf("range [0.0,1.0] / Color RGB\n");
	printf("sp / coordinates of the sphere center / diameter / Color RGB\n");
	printf("pl / coordinates / 3d normalized orientation vector / Color RGB\n");
	printf("cy / coordinates / 3d normalized orientation vector / diameter ");
	printf("/ height / Color RGB\n");
	printf("co / coordinates / 3d normalized orientation vector / diameter ");
	printf("/ height / Color RGB\n");
}


int	key_enter(t_minirt *s)
{
	char	*help1;
	char	*help2;

	help1 = ft_strdup("[F1] prompt [F2] cam param ");
	help2 = ft_strdup("[OTHER] help, id, print, save, or leaks");
	if (!ft_strncmp(s->prompt, "print", 6))
		print_params(s);
	else if (!ft_strncmp(s->prompt, "help", 5))
	{
		mlx_string_put(s->mlx, s->win, 60, HEIGHT + 2, 0xFF0000, help1);
		mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xFF0000, help2);
	}
	else if (!ft_strncmp(s->prompt, "leaks", 6))
		system("leaks miniRT");
	else if (!ft_strncmp(s->prompt, "save", 5))
		export_file_save(s);
	else if (!ft_strncmp(s->prompt, "id", 3))
		print_list_id();
	ft_free(&s->prompt);
	ft_free(&help1);
	ft_free(&help2);
	return (1);
}

void	get_prompt(t_minirt *s, int key)
{
	char	*tmp;

	tmp = NULL;
	push_img_to_win(s, PROMPT);
	if (key == BACKSP)
		key_backspace(s, tmp);
	else if (key == ENTER && s->prompt)
		key_enter(s);
	else if (key >= 0 && key < 53)
		type_key(s, tmp, key);
	if (s->prompt)
		mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xBA55D3, s->prompt);
}
