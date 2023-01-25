#include "miniRT.h"

void	get_prompt_bar(t_minirt *s)
{
	for (int j = 0; j < 32; j++)
	{
		for (int i = 0; i < WIDTH; i++)
			mlx_pixel_put(s->mlx, s->win, i, HEIGHT + j, 0xE6E6FA);
	}
}

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

int	key_enter(t_minirt *s, char *tmp)
{
	(void)tmp;
	if (!ft_strncmp(s->prompt, "print", 6))
			print_params(s);
		else if (!ft_strncmp(s->prompt, "help", 5))
		{
			char *help = ft_strdup("[help] : print help [print] : print params");
			mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xFF0000, help);
			ft_free(&help);
		}
		ft_free(&s->prompt);
	return (0);
}

void	type_key(t_minirt *s, char *tmp, int key)
{
	if (!s->prompt)
			s->prompt = ft_strdup("");
	tmp = ft_strjoin_char(s->prompt, s->k[key]);
	ft_free(&s->prompt);
	s->prompt = ft_strdup(tmp);
	ft_free(&tmp);
}

int	key_press(int key, t_minirt *s)
{
	char *tmp = NULL;
	
	push_img_to_win(s, PROMPT);
	if (key == ESCAPE)
		red_cross(s);
	else if (key == BACKSP)
		key_backspace(s, tmp);
	else if (key == ENTER && s->prompt)
		return(key_enter(s, tmp));
	else if (key >= 0 && key < 53)
		type_key(s, tmp, key);
	if (s->prompt)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xBA55D3, s->prompt);
	return (0);
}
/*
int	button_press(int i, int y, int x, t_minirt *s)
{
	t_rayon		r;
	t_vector	p;
	t_vector	n;
	t_sphere	*sphere;
	t_sphere	*sphere_tmp;
	float		t;
	float		t1;
	(void ) i;
	r = init_rayon(s->cam_origin, get_normalize_vector(vector_director(s, &x, &y)));
	sphere = s->sp;
	t = FLT_MAX;
	sphere_tmp = NULL;
	while (sphere != NULL)
	{
		if (intersection_sphere(&r, sphere, &p, &n))
		{
			t1 = get_norme_vector(div_(sub_(r.origine, p), get_norme_vector(r.direction)));
			if (t1 < t)
			{
				t = t1;
				sphere_tmp = sphere;
			}
		}
		sphere = sphere->next;
	}
	if (sphere_tmp != NULL) {
		get_buffer(s, SCENE);
		push_img_to_win(s, SCENE);
		sphere_tmp->center_axis.x += 2;
	}
	return (0);
}
*/
int	key_release(int key, t_minirt *s)
{
	(void)key;
	(void)s;
	return (0);
}
