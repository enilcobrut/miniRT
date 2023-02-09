#include "miniRT_bonus.h"

/*inth	hit_something(t_rayon *r, t_minirt *s, int depth)
{



	
}*/


int	button_press(int i, int x, int y, t_minirt *s)
{
	(void)y;
	(void)x;
	t_hit_record rec;
	if (i == 1)
	{
		s->r.mul_t_u = 1 - (double)x / (double)(WIDTH - 1);
		s->r.mul_t_v = 1 - (double)y / (double)(HEIGHT - 1);
		s->r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.lower_left_corner, mul_(s->r.horizon, s->r.mul_t_u)), mul_(s->r.vertical, s->r.mul_t_v)), s->cam_origin));
		if (hit(&s->r.r, INF, &rec, s->obj, s))
		{
			push_img_to_win(s, PROMPT);
			mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xFF0000, "OBJECT SELECTED");
			s->obj_selected_stat = 1;
		}
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