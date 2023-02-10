#include "miniRT_bonus.h"

void	key_backspace(t_minirt *s, char *tmp)
{
	if (s->prompt)
	{
		tmp = ft_strdup(s->prompt);
		ft_free(&s->prompt);
		s->prompt = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		ft_free(&tmp);
	}
}

int	key_enter(t_minirt *s)
{
	char *help;

	if (!ft_strncmp(s->prompt, "print", 6))
		print_params(s);
	else if (!ft_strncmp(s->prompt, "help", 5))
	{
		help = ft_strdup("[F1] prompt [F2] cam param [OTHER] help, print or leaks");
		mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xFF0000, help);
		ft_free(&help);
	}
	else if (!ft_strncmp(s->prompt, "leaks", 4))
		system("leaks miniRT");
	ft_free(&s->prompt);
	return (1);
}

void	get_prompt(t_minirt *s, int key)
{
	char *tmp = NULL;

	push_img_to_win(s, PROMPT);
	if (s->prompt_stat == 1 && key != 122)
	{
		if (key == BACKSP)
			key_backspace(s, tmp);
		else if (key == ENTER && s->prompt)
			key_enter(s);
		else if (key >= 0 && key < 53)
			type_key(s, tmp, key);
		if (s->prompt)
			mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xBA55D3, s->prompt);
		
	}
}

void key_up_vec(double *value)
{
	if (vec_limit(*value + INTERVAL_VEC))
		*value += INTERVAL_VEC;
	else
		*value = 1;
}

void key_down_vec(double *value)
{
	if (vec_limit(*value - INTERVAL_VEC))
		*value -= INTERVAL_VEC;
	else
		*value = -1;
}

void	function_keys(int key, t_minirt *s)
{
	if (key == F2)
	{
		if (s->cam_param_display == 1)
			s->cam_param_display = 0;
		else
			s->cam_param_display = 1;
		display_scene(s);
	}
	else if (key == F1)
	{
		if (s->prompt_stat == 1)
		{
			s->prompt_stat = 0;
			s->prompt = NULL;
		}
		else if (s->prompt_stat == 0)
			s->prompt_stat = 1;
	}
}


int	key_press(int key, t_minirt *s)
{
	if (key == ESCAPE)
		red_cross(s);
	else if (key == F1 || key == F2)
		function_keys(key, s);
	else if (is_key_move(key) && s->prompt_stat == 0)
	{
		if (!s->hit_obj)
		{
			if (key == A) // A
				s->cam_origin.x -= INTERVAL;
			else if (key == S) // S
				s->cam_origin.z -= INTERVAL;
			else if (key == D) // D
				s->cam_origin.x += INTERVAL;
			else if (key == W) // W
				s->cam_origin.z += INTERVAL;
			else if (key == SPACE) // +
				s->cam_origin.y += INTERVAL;
			else if (key == BACKSP) // -
				s->cam_origin.y -= INTERVAL;
			else if (key == EIGHT) // 8
				key_up_vec(&s->cam_vec_dir.y);
			else if (key == FOUR) // 4
				key_down_vec(&s->cam_vec_dir.x);
			else if (key == FIVE) // 5
				key_down_vec(&s->cam_vec_dir.y);
			else if (key == SIX) // 6
				key_up_vec(&s->cam_vec_dir.x);
			else if (key == ONE) // 1
				key_down_vec(&s->cam_vec_dir.z);
			else if (key == THREE) // 3
				key_up_vec(&s->cam_vec_dir.z);
		}
		else if (s->hit_obj)
		{
			// 	if (key == 126) // haut
			// 	s->cam_origin.y += INTERVAL;
			// else if (key == 123) // gauche
			// 	s->cam_origin.x -= INTERVAL;
			// else if (key == 124) // droite
			// 	s->cam_origin.x += INTERVAL;
			// else if (key == 125) // bas
			if (s->hit_obj->type == SPHERE)
			{
				if (key == A) // A
					s->hit_obj->u.sp.center_axis.x -= INTERVAL;
				else if (key == S) // S
					s->hit_obj->u.sp.center_axis.z -= INTERVAL;
				else if (key == D) // D
					s->hit_obj->u.sp.center_axis.x += INTERVAL;
				else if (key == W) // W
					s->hit_obj->u.sp.center_axis.z += INTERVAL;
				else if (key == SPACE) // +
					s->hit_obj->u.sp.center_axis.y += INTERVAL;
				else if (key == BACKSP) // -
					s->hit_obj->u.sp.center_axis.y -= INTERVAL;
			}
			else if (s->hit_obj->type == PLANE)
			{
				if (key == A) // A
					s->hit_obj->u.pl.axis.x -= INTERVAL;
				else if (key == S) // S
					s->hit_obj->u.pl.axis.z -= INTERVAL;
				else if (key == D) // D
					s->hit_obj->u.pl.axis.x += INTERVAL;
				else if (key == W) // W
					s->hit_obj->u.pl.axis.z += INTERVAL;
				else if (key == SPACE) // +
					s->hit_obj->u.pl.axis.y += INTERVAL;
				else if (key == BACKSP) // -
					s->hit_obj->u.pl.axis.y -= INTERVAL;
			}
			else if (s->hit_obj->type == CYLINDER)
			{
				if (key == A) // A
					s->hit_obj->u.cy.center.x -= INTERVAL;
				else if (key == S) // S
					s->hit_obj->u.cy.center.z -= INTERVAL;
				else if (key == D) // D
					s->hit_obj->u.cy.center.x += INTERVAL;
				else if (key == W) // W
					s->hit_obj->u.cy.center.z += INTERVAL;
				else if (key == SPACE) // +
					s->hit_obj->u.cy.center.y += INTERVAL;
				else if (key == BACKSP) // -
					s->hit_obj->u.cy.center.y -= INTERVAL;
			}
			else if (s->hit_obj->type == CONE)
			{
				if (key == A) // A
					s->hit_obj->u.co.center.x -= INTERVAL;
				else if (key == S) // S
					s->hit_obj->u.co.center.z -= INTERVAL;
				else if (key == D) // D
					s->hit_obj->u.co.center.x += INTERVAL;
				else if (key == W) // W
					s->hit_obj->u.co.center.z += INTERVAL;
				else if (key == SPACE) // +
					s->hit_obj->u.co.center.y += INTERVAL;
				else if (key == BACKSP) // -
					s->hit_obj->u.co.center.y -= INTERVAL;
			}
			display_scene(s);
		}
	}
	else if (s->prompt_stat == 1)
		get_prompt(s, key);
	if (s->prompt_stat == 1)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0x00FF00, "*");
	else
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
	return (0);
}







