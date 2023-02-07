#include "miniRT.h"

int get_pixels_to_img(t_minirt *s, int h, int opt)
{
	int		x;
	int		y;
	char	*dst;

	y = -1;
	if (opt == ALL)
		h += 32;
	while (++y != h)
	{
		x = -1;
		while (++x != WIDTH)
		{
			if (opt == ALL && y >= HEIGHT)
				dst = s->img.add_r[1] + ((y - HEIGHT) * s->img.line_length[1] 
					+ x * (s->img.bits_per_pixel[1] / 8));
			else if ((opt == SCENE || opt == ALL) && y < HEIGHT)
				dst = s->img.add_r[0] + (y * s->img.line_length[0]
					+ x * (s->img.bits_per_pixel[0] / 8));
			*(unsigned int *)dst = s->buf[y][x];
		}
	}
	/*
	t_buf *b = s->b;
	if (opt == ALL)
		h += 32;
	while (b)
	{
		printf("%x ", b->hexa);
		if (opt == ALL && b->y >= HEIGHT && b->y < h)
			dst = s->img.add_r[1] + ((b->y - HEIGHT) * s->img.line_length[1] + b->x * (s->img.bits_per_pixel[1] / 8));
		else if ((opt == SCENE || opt == ALL) && b->y < HEIGHT && b->y < h)
			dst = s->img.add_r[0] + (b->y * s->img.line_length[0] + b->x * (s->img.bits_per_pixel[0] / 8));
		*(unsigned int *)dst = b->hexa;
		b = b->next;
	}*/
	return (0);
}

int push_img_to_win(t_minirt *s, int opt)
{
	if (opt == PROMPT || opt == ALL)
		mlx_put_image_to_window(s->mlx, s->win, s->img.img[1], 0, HEIGHT);
	if (opt == SCENE || opt == ALL)
		mlx_put_image_to_window(s->mlx, s->win, s->img.img[0], 0, 0);
	return (0);
}

void	init_rtx(t_minirt *s)
{
	s->mlx = mlx_init();
	if (s->mlx == NULL)
		exit_error(s, 0, -1);
	s->win = mlx_new_window(s->mlx, WIDTH, HEIGHT + 32, s->title);
	if (s->win == NULL)
		exit_error(s, 0, -1);
	s->img.img[0] = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	s->img.add_r[0] = mlx_get_data_addr(s->img.img[0], &s->img.bits_per_pixel[0],
								&s->img.line_length[0], &s->img.endian[0]);
	s->img.img[1] = mlx_new_image(s->mlx, WIDTH, 32);
	s->img.add_r[1] = mlx_get_data_addr(s->img.img[1], &s->img.bits_per_pixel[1],
								&s->img.line_length[1], &s->img.endian[1]);
}

void	start_ray_tracing(t_minirt *s)
{
	get_buffer(s);
	init_rtx(s);
	get_pixels_to_img(s, HEIGHT, ALL);
	push_img_to_win(s, ALL);
	display_param_cam(s);
	mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
	mlx_hook(s->win, 2, 1L << 0, key_press, s);
	mlx_mouse_hook(s->win, button_press, s);
	mlx_hook(s->win, 17, 1L << 0, red_cross, s);
	mlx_loop(s->mlx);
}
