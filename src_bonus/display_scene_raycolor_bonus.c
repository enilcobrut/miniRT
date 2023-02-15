/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scene_raycolor_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:41:10 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 13:57:56 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	get_light_data(t_minirt *s, t_rayon *r, t_hit *rec, t_light *light1)
{
	t_vector	light_dir;

	light_dir = sub_(light1->light_axis, rec->p);
	s->speculaire = fmax(0, dot(norm_(light_dir),
				norm_(reflect(r->direction, rec->normal))));
	s->light_dist = vec3_length(light_dir) / 1000;
	s->ambiante = fmax(0, dot(norm_(light_dir),
				norm_(rec->normal)))
		/ (1 + s->light_dist * s->light_dist);
}

t_color	compute_lighting(t_rayon *r, t_hit *rec, t_minirt *s)
{
	t_color	light;
	t_hit	rec2;
	t_rayon	verif;
	t_light	*light1;

	light1 = s->li;
	light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
	while (light1)
	{
		verif = init_rayon(rec->p, norm_(sub_(light1->light_axis, rec->p)));
		if (!hit(&verif, vec3_length(sub_(light1->light_axis, rec->p)),
				&rec2, s->obj))
		{
			get_light_data(s, r, rec, light1);
			light = color_add_(light, color_mul_scalar(light1->light_color,
						light1->light_brightness_ratio
						* (s->ambiante + pow(s->speculaire, 20))));
		}
		light1 = light1->next;
	}
	return (light);
}

t_color	ray_color(t_rayon *r, t_minirt *s)
{
	t_hit	rec;
	t_color	light;
	t_rayon	scattered;
	t_color	attenuation;
	int		(*scatter)(const t_rayon *r,
			const t_hit *rec, t_color *attenuation,
			t_rayon *scattered);

	r->direction = norm_(r->direction);
	if (!hit(r, INF, &rec, s->obj))
		return (init_color(0, 0, 0));
	light = compute_lighting(r, &rec, s);
	scatter = rec.mat_ptr->scatter;
	if (rec.hit_obj == s->hit_obj)
		scatter = scat_check;
	if (scatter(r, &rec, &attenuation, &scattered))
		return (color_mul(attenuation, clamp_color(light)));
	return (color_mul(attenuation, clamp_color(light)));
}
