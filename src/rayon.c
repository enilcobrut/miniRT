/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:16:55 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 11:16:57 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rayon	init_rayon(t_vector origine, t_vector direction)
{
	t_rayon	r;

	r.origine = origine;
	r.direction = direction;
	return (r);
}
