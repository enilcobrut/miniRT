
#include "miniRT_bonus.h"

int	red_cross(t_minirt *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit_error(s, 0, -1);
	return (0);
}
