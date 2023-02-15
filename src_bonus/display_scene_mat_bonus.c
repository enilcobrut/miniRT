/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scene_mat_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:53:38 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 14:09:08 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	super_mod(int div, int mod)
{
	return (((div % mod) + mod) % mod);
}

t_vector	reflect(const t_vector v, const t_vector n)
{
	return (sub_(v, mul_(n, 2 * dot(v, n))));
}

int	near_zero(const t_vector *vec)
{
	double	s;

	s = 1e-8;
	return ((fabs(vec->x) < s) && (fabs(vec->y) < s)
		&& fabs(vec->z) < s);
}

int	scat_check(const t_rayon *r, const t_hit *rec, t_color *a, t_rayon *s)
{
	double	size;

	size = 20;
	if (rec->hit_obj->type == CYLINDER)
		size = rec->hit_obj->u_.cy.radius / 20.0;
	else if (rec->hit_obj->type == SPHERE)
		size = rec->hit_obj->u_.sp.radius / 20.0;
	else if (rec->hit_obj->type == CONE)
		size = rec->hit_obj->u_.co.radius / 20.0;
	if (sin((PI / size) * rec->p.x) * sin((PI / size) * rec->p.z) >= 0)
	{
		*a = init_color(1, 0.67843, 0);
		return (0);
	}
	return (rec->mat_ptr->scatter(r, rec, a, s));
}

int	scat_lamb(const t_rayon *r, const t_hit *rec, t_color *a, t_rayon *s)
{
	t_vector	scatter_dir;

	(void)r;
	scatter_dir = add_(norm_(rec->normal), random_in_unit_sphere());
	if (near_zero(&scatter_dir))
		scatter_dir = rec->normal;
	*s = init_rayon(rec->p, scatter_dir);
	*a = rec->mat_ptr->albedo;
	return (1);
}
