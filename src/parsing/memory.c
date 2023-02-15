/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:51:21 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/14 17:02:45 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_set(t_minirt *s)
{
	s->hit_obj = NULL;
	s->prompt_stat = 1;
	s->s_pixel = SAMPLE_P_PIX;
	s->params = NULL;
	s->prompt = NULL;
	s->amb_light_ratio = 0;
	s->cam_fov = 0;
	s->light_brightness_ratio = 0;
	s->cam_param_display = 1;
	s->obj = NULL;
	s->mlx = NULL;
	s->win = NULL;
	s->title = ft_strdup("miniRT");
	s->k = "asdfhgzxcv\0bqweryt123465+97-80]ou[ip\0lj'k;\\,/nm.\0 `\0";
}

void	free_split(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
		{
			ft_free(((*str) + i));
			i++;
		}
		free(*str);
		*str = 0;
	}
}

void	ft_free(char **to_free)
{
	if (*to_free)
		free(*to_free);
	*to_free = NULL;
}
