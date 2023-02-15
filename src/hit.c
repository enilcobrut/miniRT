/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:14:44 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 12:46:06 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	register_hit(int *h, double *c, t_hit *rec, t_hit *t)
{
	*h = 1;
	*c = t->t;
	*rec = *t;
}

int	hit(const t_rayon *r, double t_max, t_hit *rec, t_obj *obj)
{
	t_hit	tp;
	int		hit_anything;
	double	closest;

	hit_anything = 0;
	closest = t_max;
	while (obj)
	{
		if ((obj->type == SPHERE && hit_sphere(&obj->u_.sp, r, &tp, closest))
			|| (obj->type == PLANE && hit_plane(&obj->u_.pl, r, &tp, closest))
			|| (obj->type == CYLINDER
				&& hit_cylinder(&obj->u_.cy, r, &tp, closest)))
		{
			register_hit(&hit_anything, &closest, rec, &tp);
			rec->mat_ptr = &obj->mat;
			rec->hit_obj = obj;
		}
		obj = obj->next;
	}
	if (hit_anything)
		rec->normal = norm_(rec->normal);
	return (hit_anything);
}
