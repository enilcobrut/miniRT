#include "miniRT_bonus.h"

/*inth	hit_something(t_rayon *r, t_minirt *s, int depth)
{



	
}*/


int	button_press(int i, int y, int x, t_minirt *s)
{
	(void)y;
	(void)x;
	
	if (i == 1)
	{
		push_img_to_win(s, PROMPT);
		mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xFF0000, "OBJECT SELECTED");
		s->obj_selected_stat = 1;
		printf("x %d y %d\n", x, y);
		
	}
	else if (i == 2)
	{
		s->obj_selected_stat = 0;
		printf("x %d y %d\n", x, y);
		push_img_to_win(s, PROMPT);
	}
	else if (i == 4 || i == 5) // scroll up
	{
		if (i == 4)
			s->cam_origin.z += INTERVAL;
		else
			s->cam_origin.z -= INTERVAL;
		display_scene(s);
	}
	if (s->prompt_stat == 1)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0x00FF00, "*");
	else
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
	return (0);
}