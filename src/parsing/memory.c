/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:51:21 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/15 14:34:06 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_set(t_minirt *s)
{
	s->s_pixel = SAMPLE_P_PIX;
	s->params = NULL;
	s->amb_light_ratio = 0;
	s->obj = NULL;
	s->mlx = NULL;
	s->win = NULL;
	s->ambiante = 0;
	s->speculaire = 0;
	s->light_dist = 0;
	s->title = ft_strjoin("Happy Tree miniRT - ", s->argv[1]);
}

void	ft_free(char **to_free)
{
	if (*to_free)
		free(*to_free);
	*to_free = NULL;
}
