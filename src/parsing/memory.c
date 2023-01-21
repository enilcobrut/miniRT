/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:50:23 by flemaitr          #+#    #+#             */
/*   Updated: 2023/01/20 11:37:13 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_set(t_minirt *s)
{
	s->params = NULL;
	s->prompt = NULL;
	s->amb_light_ratio = 0;
	s->cam_hor_field_view = 0;
	s->light_brightness_ratio = 0;
	s->obj = NULL;
	s->mlx = NULL;
	s->win = NULL;
	s->img.img = ft_calloc(2, sizeof(void *));
	s->img.add_r = ft_calloc(2, sizeof(char *));
	s->title = ft_strdup("miniRT");
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

void	mem_alloc_with_calloc(t_minirt *s, void ***ptr, size_t size)
{
	*ptr = ft_calloc(size, sizeof(void *));
	if (*ptr == NULL)
		exit_error(s, "Malloc error", 0);
}
