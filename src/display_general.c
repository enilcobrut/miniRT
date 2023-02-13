/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_general.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:37:43 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/10 17:37:45 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	red_cross(t_minirt *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit_error(s, 0, -1);
	return (0);
}

int	key_press(int key, t_minirt *s)
{
	if (key == ESCAPE)
		red_cross(s);
	return (0);
}

int	push_img_to_win(t_minirt *s)
{
	mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
	return (0);
}

void	init_rtx(t_minirt *s)
{
	s->mlx = mlx_init();
	if (s->mlx == NULL)
		exit_error(s, 0, -1);
	s->win = mlx_new_window(s->mlx, WIDTH, HEIGHT, s->title);
	if (s->win == NULL)
		exit_error(s, 0, -1);
	s->img.img = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	s->img.add_r = mlx_get_data_addr(s->img.img, &s->img.bits_ppix,
			&s->img.line_length, &s->img.endian);

}

void	start_ray_tracing(t_minirt *s)
{
	init_rtx(s);
	get_pixels_to_img(s);
	push_img_to_win(s);
	mlx_hook(s->win, 2, 1L << 0, key_press, s);
	mlx_hook(s->win, 17, 1L << 0, red_cross, s);
	mlx_loop(s->mlx);
}
