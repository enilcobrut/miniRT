/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys_tools_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:18:32 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 21:18:34 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	is_key_move(int key)
{
	if (key == A || key == S || key == D || key == W || key == BACKSP
		|| key == SPACE || key == EIGHT || key == FOUR || key == SIX
		|| key == FIVE || key == ONE || key == THREE)
		return (1);
	return (0);
}

int	vec_limit(double value)
{
	if (value <= 1 && value >= -1)
		return (1);
	return (0);
}

void	key_up_vec(double *value)
{
	if (vec_limit(*value + INTERVAL_VEC))
		*value += INTERVAL_VEC;
	else
		*value = 1;
}

void	key_down_vec(double *value)
{
	if (vec_limit(*value - INTERVAL_VEC))
		*value -= INTERVAL_VEC;
	else
		*value = -1;
}
