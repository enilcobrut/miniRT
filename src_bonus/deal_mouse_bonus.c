#include "miniRT_bonus.h"

int	button_press(int i, int y, int x, t_minirt *s)
{
	(void)y;
	(void)x;
	
	if (i == 1)
	{
		printf("x %d y %d\n", x, y);
	}
	else if (i == 4 || i == 5) // scroll up
	{
		if (i == 4)
			s->cam_origin.z += INTERVAL;
		else
			s->cam_origin.z -= INTERVAL;
		display_scene(s);
	}
	return (0);
}