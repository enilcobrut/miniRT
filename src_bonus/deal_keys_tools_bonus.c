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