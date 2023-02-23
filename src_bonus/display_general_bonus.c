/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_general_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:22:56 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/16 11:34:27 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	push_img_to_win(t_minirt *s, int opt)
{
	if (opt == PROMPT || opt == ALL)
	{
		mlx_put_image_to_window(s->mlx, s->win, s->img.img[1], 0, HEIGHT);
		display_prompt_status(s);
	}
	if (opt == SCENE || opt == ALL)
		mlx_put_image_to_window(s->mlx, s->win, s->img.img[0], 0, 0);
	return (0);
}

void	init_rtx(t_minirt *s)
{
	s->win = mlx_new_window(s->mlx, WIDTH, HEIGHT + 32, s->title);
	if (s->win == NULL)
		exit_error(s, 0, -1);
	s->img.img[0] = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	s->img.add_r[0] = mlx_get_data_addr(s->img.img[0], &s->img.bits_ppix[0],
			&s->img.line_length[0], &s->img.endian[0]);
	s->img.img[1] = mlx_new_image(s->mlx, WIDTH, 32);
	s->img.add_r[1] = mlx_get_data_addr(s->img.img[1], &s->img.bits_ppix[1],
			&s->img.line_length[1], &s->img.endian[1]);
}

void	start_ray_tracing(t_minirt *s)
{
	init_rtx(s);
	get_prompt_color(s);
	get_pixels_to_img(s);
	push_img_to_win(s, ALL);
	mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
	mlx_hook(s->win, 2, 1L << 0, key_press, s);
	mlx_mouse_hook(s->win, button_press, s);
	mlx_hook(s->win, 17, 1L << 0, red_cross, s);
	mlx_loop(s->mlx);
}
