/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:53:44 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/04 18:53:46 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	red_cross(t_minirt *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit_error(s, 0, -1);
	return (0);
}

void	put_str(t_minirt *s, int x, int y, char *str)
{
	int	color;

	if (ft_strncmp(str, "RINGS", ft_strlen(str)) == 0
		|| ft_strncmp(str, "TIME", ft_strlen(str)) == 0
		|| ft_strncmp(str, "SCORE", ft_strlen(str)) == 0)
		color = 0x00FFFF00;
	else
		color = 0x00FFFFFF;
	mlx_string_put(s->mlx, s->win, x + 2, y + 2, 0x00000000, str);
	mlx_string_put(s->mlx, s->win, x, y, color, str);
}
