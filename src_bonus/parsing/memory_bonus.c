/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:04:02 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/16 12:09:40 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	init_set_next(t_minirt *s)
{	
	int	null;
	int	w;
	int	h;

	s->hit_obj_xpm = mlx_xpm_file_to_image(s->mlx, "hit_obj.xpm", &w, &h);
	if (!s->hit_obj_xpm)
		exit_error(s, "Error with the xpm file", 1);
	s->hit_obj_xpm_addr = (int *)mlx_get_data_addr(s->hit_obj_xpm, &null,
			&null, &null);
	s->hit_obj = NULL;
}

void	init_set(t_minirt *s)
{
	s->hit_obj_xpm = NULL;
	s->hit_obj_xpm_addr = NULL;
	s->hit_obj = NULL;
	s->y = 0;
	s->obj = NULL;
	s->speculaire = 0;
	s->ambiante = 0;
	s->light_dist = 0;
	s->prompt_stat = 0;
	s->s_pixel = SAMPLE_P_PIX;
	s->depth = DEPTH;
	s->params = NULL;
	s->prompt = NULL;
	s->amb_light_ratio = 0;
	s->cam_fov = 0;
	s->cam_param_display = 0;
	s->obj = NULL;
	s->win = NULL;
	s->img.img = ft_calloc(2, sizeof(void *));
	s->img.add_r = ft_calloc(2, sizeof(char *));
	if (!s->img.img || !s->img.add_r)
		exit_error(s, "Error with malloc", 1);
	s->title = ft_strjoin("Happy Tree miniRT - ", s->argv[1]);
	s->k = "asdfhgzxcv\0bqweryt123465+97-80]ou[ip\0lj'k;\\,/nm.\0 `\0";
}

void	ft_free(char **to_free)
{
	if (*to_free)
		free(*to_free);
	*to_free = NULL;
}
