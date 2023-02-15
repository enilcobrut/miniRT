/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:46:31 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 13:46:33 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vector	sub_(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vector	add_(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vector	div_(t_vector v, float n)
{
	t_vector	new_v;

	new_v.x = v.x / n;
	new_v.y = v.y / n;
	new_v.z = v.z / n;
	return (new_v);
}

t_vector	mul_(t_vector v, double n)
{
	t_vector	new_v;

	new_v.x = v.x * n;
	new_v.y = v.y * n;
	new_v.z = v.z * n;
	return (new_v);
}

t_vector	vec_cross(const t_vector u, const t_vector v)
{
	return ((t_vector){u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x});
}
