/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys_display_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:20:52 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/14 17:02:45 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	itof_to_win(t_minirt *s, double n, int x, int y)
{
	char	*tmp;

	tmp = ft_itof(n);
	mlx_string_put(s->mlx, s->win, x, y, 0xFFFFFF, tmp);
	free(tmp);
}

void	itoa_to_win(t_minirt *s, int n, int x, int y)
{
	char	*tmp;

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
	itoa_to_win(s, s->s_pixel, 125, 130);
	mlx_string_put(s->mlx, s->win, 10, 150, 0xFFFFFF, "DEPTH :");
	itoa_to_win(s, s->depth, 125, 150);
}
