/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:46:03 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 14:13:09 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	register_hit(int *h, double *c, t_hit *rec, t_hit *t)
{
	*h = 1;
	*c = t->t;
	*rec = *t;
}

void	apply_bump_map(t_hit *rec)
{
	int	col;

	rec->normal = norm_(rec->normal);
	col = rec->hit_obj->bump_map_addr[
		(super_mod(rec->p.x * 100.0, rec->hit_obj->bump_height))
		* rec->hit_obj->bump_width
		+ (super_mod((double)rec->p.z * 100.0, rec->hit_obj->bump_width))];
	rec->p = add_(rec->p, mul_(rec->normal,
				((col & 0xff) / 255.0 - .5) / 100.0));
}

int	hit(const t_rayon *r, double t_max, t_hit *rec, t_obj *obj)
{
	t_hit			tp;
	int				hit_anything;
	double			c;

	hit_anything = 0;
	c = t_max;
	while (obj)
	{
		if ((obj->type == SPHERE && hit_sphere(&obj->u_.sp, r, &tp, c))
			|| (obj->type == PLANE && hit_plane(&obj->u_.pl, r, &tp, c))
			|| (obj->type == CYLINDER && hit_cylinder(&obj->u_.cy, r, &tp, c))
			|| (obj->type == CONE && hit_cone(&obj->u_.co, r, &tp, c)))
		{
			register_hit(&hit_anything, &c, rec, &tp);
			rec->mat_ptr = &obj->mat;
			rec->hit_obj = obj;
		}
		obj = obj->next;
	}
	if (hit_anything && (rec->hit_obj->bump_map))
		apply_bump_map(rec);
	return (hit_anything);
}
