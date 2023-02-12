
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

int	ft_recursive_counter(long n);
char	*ft_itof_print(double n)
{
	char	*str = NULL;
	long	tmp;
	int		len;
	char	*integer;
	char	*tmp_ = NULL;

	if ((n < 0 && n > -1))
		integer = ft_strdup("-0");
	else
		integer = ft_itoa(n);
	n -= (int)n;
	tmp = n * 10;
	if (n < 0)
		tmp = -tmp;
	if (tmp == 0)
		tmp_ = ft_strjoin(integer, ".0");
	else
	{
		len = ft_recursive_counter(tmp) + 1;
		str = ft_calloc(len + 1, sizeof(char));
		if (str == NULL)
			return (0);
		while (len)
		{
			len--;
			str[len] = tmp % 10 + '0';
			tmp = tmp / 10;
		}
		str[len] = '.';
		tmp_ = ft_strjoin(integer, str);
	}
	free(integer);
	free(str);
	return (tmp_);
}


void print_rgb(t_color color, int fd)
{
	ft_putnbr_fd(color.r * 255, fd);
	ft_putstr_fd(",", fd);
	ft_putnbr_fd(color.g * 255, fd);
	ft_putstr_fd(",", fd);
	ft_putnbr_fd(color.b * 255, fd);
	ft_putstr_fd(" ", fd);
}

void print_axis(t_vector vec, int fd)
{
	ft_putstr_fd(ft_itof_print(vec.x), fd);
	ft_putstr_fd(",", fd);
	ft_putstr_fd(ft_itof_print(vec.y), fd);
	ft_putstr_fd(",", fd);
	ft_putstr_fd(ft_itof_print(vec.z), fd);
	ft_putstr_fd(" ", fd);
}

void	write_params(t_minirt *s, int fd)
{
	
	while (s->obj)
	{
		if (s->obj->type == SPHERE)
		{
			ft_putstr_fd("sp ", fd);
			print_axis(s->obj->u_.sp.center_axis, fd);
			ft_putnbr_fd(s->obj->u_.sp.diameter, fd);
			ft_putstr_fd(" ", fd);
			print_rgb(s->obj->mat.albedo, fd);			
		}
		else if (s->obj->type == CYLINDER)
		{
			ft_putstr_fd("cy ", fd);
			print_axis(s->obj->u_.cy.center, fd);
			print_axis(s->obj->u_.cy.dir_ax, fd);
			ft_putnbr_fd(s->obj->u_.cy.diameter, fd);
			ft_putstr_fd(" ", fd);
			ft_putnbr_fd(s->obj->u_.cy.height, fd);
			ft_putstr_fd(" ", fd);
			print_rgb(s->obj->mat.albedo, fd);
		}
		else if (s->obj->type == CONE)
		{
			ft_putstr_fd("co ", fd);
			print_axis(s->obj->u_.co.center, fd);
			print_axis(s->obj->u_.co.dir_ax, fd);
			ft_putnbr_fd(s->obj->u_.co.diameter, fd);
			ft_putstr_fd(" ", fd);
			ft_putnbr_fd(s->obj->u_.co.height, fd);
			ft_putstr_fd(" ", fd);
			print_rgb(s->obj->mat.albedo, fd);
		}
		else if (s->obj->type == PLANE)
		{
			ft_putstr_fd("pl ", fd);
			print_axis(s->obj->u_.pl.axis, fd);
			print_axis(s->obj->u_.pl.dir_ax, fd);
			print_rgb(s->obj->mat.albedo, fd);
		}
		ft_putstr_fd("\n", fd);
		s->obj = s->obj->next;
	}
	ft_putstr_fd("C ", fd);
	print_axis(s->cam_origin, fd);
	print_axis(s->cam_vec_dir, fd);
	ft_putnbr_fd(s->cam_fov, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("A ", fd);
	ft_putstr_fd(ft_itof_print(s->amb_light_ratio), fd);
	ft_putstr_fd(" ", fd);
	print_rgb(s->amb_light_color, fd);
	ft_putstr_fd("\n", fd);
	while (s->li)
	{
		ft_putstr_fd("L ", fd);
		print_axis(s->li->light_axis, fd);
		ft_putstr_fd(ft_itof_print(s->li->light_brightness_ratio), fd);
		ft_putstr_fd(" ", fd);
		print_rgb(s->li->light_color, fd);
		ft_putstr_fd("\n", fd);
		s->li = s->li->next;
	}
}

void	export_file_save(t_minirt *s, int opt)
{
	/*time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    (void)s;
	int date = tm->tm_sec + (tm->tm_min * 100) + (tm->tm_hour * 100) + (tm->tm_mon * 100) + ((tm->tm_year + 1900) * 10000);
	printf("%d\n", date);
	printf("%d\n", tm->tm_yday);*/
	
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
		export_file_save(s, 1);
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
