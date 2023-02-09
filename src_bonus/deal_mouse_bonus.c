#include "miniRT_bonus.h"

void	display_hit_obj_params(t_minirt *s)
{
	// center axis -> 4
	// dir_ax pl cy co
	// diam sp cy co
	// height cy, co
	
	mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xBA55D3, "OBJECT SELECTED #");
	itoa_to_win(s, s->hit_obj->n, 200, HEIGHT + 2);
	if (s->hit_obj->type == PLANE)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "PLANE");
	else if (s->hit_obj->type == SPHERE)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "SPHERE");
	else if (s->hit_obj->type == CYLINDER)
	{
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "CYLINDER");

		/*mlx_string_put(s->mlx, s->win, 30, 10, 0xFFFFFF, "CENTER [");
		itof_to_win(s, s->hit_obj->u.cy.center.x, 125, HEIGHT + 2);
		itof_to_win(s, s->hit_obj->u.cy.center.y, 125, HEIGHT + 2);
		itof_to_win(s, s->hit_obj->u.cy.center.z, 125, HEIGHT + 2);

		mlx_string_put(s->mlx, s->win, 30, 30, 0xFFFFFF, "2");
		itof_to_win(s, s->cam_origin.y, 125, 30);
		mlx_string_put(s->mlx, s->win, 30, 50, 0xFFFFFF, "3");
		itof_to_win(s, s->cam_origin.z, 125, 50);
		mlx_string_put(s->mlx, s->win, 30, HEIGHT - 20, 0xFFFFFF, "4");
		itof_to_win(s, s->cam_vec_dir.x, 125, HEIGHT - 20);*/
	}
	else if (s->hit_obj->type == CONE)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "CONE");
	/*
	mlx_string_put(s->mlx, s->win, 30, 10, 0xFFFFFF, "1");
	itof_to_win(s, s->cam_origin.x, 125, 10);
	mlx_string_put(s->mlx, s->win, 30, 30, 0xFFFFFF, "2");
	itof_to_win(s, s->cam_origin.y, 125, 30);
	mlx_string_put(s->mlx, s->win, 30, 50, 0xFFFFFF, "3");
	itof_to_win(s, s->cam_origin.z, 125, 50);
	mlx_string_put(s->mlx, s->win, 30, HEIGHT - 20, 0xFFFFFF, "4");
	itof_to_win(s, s->cam_vec_dir.x, 125, HEIGHT - 20);*/
}

void hit_something(t_minirt *s, int x, int y)
{
	t_hit_record rec;

	s->r.mul_t_u = 1 - (double)x / (double)(WIDTH - 1);
	s->r.mul_t_v = 1 - (double)y / (double)(HEIGHT - 1);
	s->r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.lower_left_corner, mul_(s->r.horizon, s->r.mul_t_u)), mul_(s->r.vertical, s->r.mul_t_v)), s->cam_origin));
	if (hit(&s->r.r, INF, &rec, s->obj, s))
	{
		s->hit_obj = rec.hit_obj;
	}
}

int	button_press(int i, int x, int y, t_minirt *s)
{
	push_img_to_win(s, PROMPT);
	if (i == 1 || i == 2)
	{
		s->hit_obj = NULL;
		if (i == 1)
			hit_something(s, x, y);
	}
	else if (i == 4 || i == 5) // scroll up
	{
		if (i == 4)
			s->cam_origin.z += INTERVAL;
		else
			s->cam_origin.z -= INTERVAL;
	}
	display_scene(s);
	if (s->prompt_stat == 1)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0x00FF00, "*");
	else
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
	return (0);
}