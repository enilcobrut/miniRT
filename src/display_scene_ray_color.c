/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scene_ray_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:35:36 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 11:04:27 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_light_color(t_rayon *r, t_hit *rec, t_minirt *s)
{
	t_color		light;
	t_hit		rec2;
	t_rayon		verif;
	t_vector	light_dir;

	light = color_mul_scalar(s->amb_light_color, s->amb_light_ratio);
	light_dir = sub_(s->light_axis, rec->p);
	verif = init_rayon(rec->p, vec3_unit_vector(light_dir));
	if (!hit(&verif, vec3_length(sub_(s->light_axis, rec->p)), &rec2, s->obj))
	{
		s->speculaire = fmax(0, dot(vec3_unit_vector(light_dir),
					vec3_unit_vector(reflect(r->direction, rec->normal))));
		s->light_dist = vec3_length(light_dir) / 1000;
		s->ambiante = fmax(0, dot(vec3_unit_vector(light_dir),
					vec3_unit_vector(rec->normal)))
			/ (1 + s->light_dist * s->light_dist);
		light = color_add_(light, color_mul_scalar(s->light_color,
					s->light_brightness_ratio
					* (s->ambiante + pow(s->speculaire, 30))));
	}
	return (light);
}

t_color	ray_color(t_rayon *r, t_minirt *s)
{
	t_hit	rec;
	t_color	light;

	r->direction = vec3_unit_vector(r->direction);
	if (!hit(r, INF, &rec, s->obj))
		return (init_color(0, 0, 0));
	light = get_light_color(r, &rec, s);
	return (color_mul(rec.mat_ptr->albedo, clamp_color(light)));
}
