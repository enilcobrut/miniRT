/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayon_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:46:25 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 13:46:27 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_rayon	init_rayon(t_vector origine, t_vector direction)
{
	t_rayon	r;

	r.origine = origine;
	r.direction = direction;
	return (r);
}
