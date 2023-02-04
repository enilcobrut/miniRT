#include "miniRT_bonus.h"

void	get_prompt_bar(t_minirt *s)
{
	for (int j = 0; j < 32; j++)
	{
		for (int i = 0; i < WIDTH; i++)
			mlx_pixel_put(s->mlx, s->win, i, HEIGHT + j, 0xE6E6FA);
	}
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

int	key_enter(t_minirt *s)
{
	char *help;

	if (!ft_strncmp(s->prompt, "print", 6))
		print_params(s);
	else if (!ft_strncmp(s->prompt, "help", 5))
	{
		help = ft_strdup("[help] : help [print] : print params [cam] : cam params");
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xFF0000, help);
		ft_free(&help);
	}
	else if (!ft_strncmp(s->prompt, "cam", 4))
	{
		if (s->cam_param_display == 1)
			s->cam_param_display = 0;
		else
			s->cam_param_display = 1;
		display_scene(s);
	}
	ft_free(&s->prompt);
	return (0);
}

void	type_key(t_minirt *s, char *tmp, int key)
{
	if (!s->prompt)
			s->prompt = ft_strdup("");
	tmp = ft_strjoin_char(s->prompt, s->k[key]);
	ft_free(&s->prompt);
	s->prompt = ft_strdup(tmp);
	ft_free(&tmp);
}

void	itof_to_win(t_minirt *s, double n, int x, int y)
{
	char *tmp;

	tmp = ft_itof(n);
	mlx_string_put(s->mlx, s->win, x, y, 0xFFFFFF, tmp);
	free(tmp);
}

void	itoa_to_win(t_minirt *s, int n, int x, int y)
{
	char *tmp;

	tmp = ft_itoa(n);
	mlx_string_put(s->mlx, s->win, x, y, 0xFFFFFF, tmp);
	free(tmp);
}

void	display_param_cam(t_minirt *s)
{
	mlx_string_put(s->mlx, s->win, 10, 10, 0xFFFFFF, "CAM.OR.X :");
	itof_to_win(s, s->cam_origin.x, 125, 10);
	mlx_string_put(s->mlx, s->win, 10, 30, 0xFFFFFF, "CAM.OR.Y :");
	itof_to_win(s, s->cam_origin.y, 125, 30);
	mlx_string_put(s->mlx, s->win, 10, 50, 0xFFFFFF, "CAM.OR.Z :");
	itof_to_win(s, s->cam_origin.z, 125, 50);
	mlx_string_put(s->mlx, s->win, 10, 70, 0xFFFFFF, "CAM.DIR.X :");
	itof_to_win(s, s->cam_vec_dir.x, 125, 70);
	mlx_string_put(s->mlx, s->win, 10, 90, 0xFFFFFF, "CAM.DIR.Y :");
	itof_to_win(s, s->cam_vec_dir.y, 125, 90);
	mlx_string_put(s->mlx, s->win, 10, 110, 0xFFFFFF, "CAM.DIR.Z :");
	itof_to_win(s, s->cam_vec_dir.z, 125, 110);
	mlx_string_put(s->mlx, s->win, 10, 130, 0xFFFFFF, "S/PIX :");
	itoa_to_win(s, s->samples_per_pixel, 125, 130);
	mlx_string_put(s->mlx, s->win, 10, 150, 0xFFFFFF, "DEPTH :");
	itoa_to_win(s, s->depth, 125, 150);
	/*mlx_string_put(s->mlx, s->win, 10, 170, 0xFFFFFF, "ANTI-AL :");
	itoa_to_win(s, s->depth, 125, 170);*/
}

int	is_key_move(int key)
{
	if (key == 126 || key == 123 || key == 124 || key == 125 || key == 69
		|| key == 78|| key == 91|| key == 86|| key == 84 || key == 88
		|| key == 83 || key == 85)
		return (1);
	return (0);
}

int	vec_limit(double value)
{
	if (value <= 1 && value >= -1)
		return (1);
	return (0);
}



int	key_press(int key, t_minirt *s)
{
	char *tmp = NULL;

	if (is_key_move(key))
	{
		if (key == 126) // haut
			s->cam_origin.y += INTERVAL;
		else if (key == 123) // gauche
			s->cam_origin.x -= INTERVAL;
		else if (key == 124) // droite
			s->cam_origin.x += INTERVAL;
		else if (key == 125) // bas
			s->cam_origin.y -= INTERVAL;
		else if (key == 69) // +
			s->cam_origin.z += INTERVAL;
		else if (key == 78) // -
			s->cam_origin.z -= INTERVAL;
		else if (key == 91)
		{
			if(vec_limit(s->cam_vec_dir.y + INTERVAL_VEC)) // 8
				s->cam_vec_dir.y += INTERVAL_VEC;
			else
				s->cam_vec_dir.y = 1;
		}
		else if (key == 86)
		{
			if (vec_limit(s->cam_vec_dir.x - INTERVAL_VEC)) // 4
				s->cam_vec_dir.x -= INTERVAL_VEC;
			else
				s->cam_vec_dir.x = -1;
		}
		else if (key == 84)
		{
			if (vec_limit(s->cam_vec_dir.y - INTERVAL_VEC)) // 2
				s->cam_vec_dir.y -= INTERVAL_VEC;
			else
				s->cam_vec_dir.y = -1;

		}
		else if (key == 88)
		{
			if (vec_limit(s->cam_vec_dir.x + INTERVAL_VEC)) // 6
				s->cam_vec_dir.x += INTERVAL_VEC;
			else
				s->cam_vec_dir.x = 1;

		}
		else if (key == 83)
		{
			if (vec_limit(s->cam_vec_dir.z - INTERVAL_VEC)) // 1
				s->cam_vec_dir.z -= INTERVAL_VEC;
			else
				s->cam_vec_dir.z = -1;

		}
		else if (key == 85)
		{
			if (vec_limit(s->cam_vec_dir.z + INTERVAL_VEC)) // 3
				s->cam_vec_dir.z += INTERVAL_VEC;
			else
				s->cam_vec_dir.z = 1;
		}
		display_scene(s);
	}
	else
	{
		push_img_to_win(s, PROMPT);
		if (key == ESCAPE)
			red_cross(s);
		else if (key == BACKSP)
			key_backspace(s, tmp);
		else if (key == ENTER && s->prompt)
			return (key_enter(s));
		else if (key >= 0 && key < 53)
			type_key(s, tmp, key);
		if (s->prompt)
			mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xBA55D3, s->prompt);
	}
	return (0);
}

int	button_press(int i, int y, int x, t_minirt *s)
{
	(void)y;
	(void)x;
	
	if (i == 1)
	{
		printf("Clic gauche\n");
	}
	else if (i == 4 || i == 5) // scroll up
	{
		if (i == 4)
			s->cam_origin.z += INTERVAL;
		else
			s->cam_origin.z -= INTERVAL;
		get_buffer(s);
		get_pixels_to_img(s, HEIGHT, SCENE);
		push_img_to_win(s, SCENE);
		if (s->cam_param_display == 1)
			display_param_cam(s);
	}
	return (0);
}

