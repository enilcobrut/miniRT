/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:15:32 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 12:46:06 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	get_normalize_vector(t_vector v)
{
	t_vector	new_v;
	float		norm;

	new_v = v;
	norm = sqrt(get_norme_vector(v));
	new_v.x /= norm;
	new_v.y /= norm;
	new_v.z /= norm;
	return (new_v);
}

float	get_norme_vector(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector	init_vector(float x, float y, float z)
{
	return ((t_vector){x, y, z});
}

t_vector	norm_(t_vector a)
{
	double	length;

	length = vec3_length(a);
	return ((t_vector){a.x / length, a.y / length, a.z / length});
}

double	vec3_length(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}
