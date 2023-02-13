
#include "miniRT_bonus.h"

void	type_key(t_minirt *s, char *tmp, int key)
{
	if (!s->prompt)
			s->prompt = ft_strdup("");
	tmp = ft_strjoin_char(s->prompt, s->k[key]);
	ft_free(&s->prompt);
	s->prompt = ft_strdup(tmp);
	ft_free(&tmp);
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

void	display_prompt_status(t_minirt *s)
{
	if (s->prompt_stat == 1)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0x00FF00, "*");
	else
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
}





int	key_enter(t_minirt *s)
{
	char	*help1;
	char	*help2;

	help1 = ft_strdup("[F1] prompt [F2] cam param ");
	help2 = ft_strdup("[OTHER] help, id, print, save, or leaks");
	if (!ft_strncmp(s->prompt, "print", 6))
		print_params(s);
	else if (!ft_strncmp(s->prompt, "help", 5))
	{
		mlx_string_put(s->mlx, s->win, 60, HEIGHT + 2, 0xFF0000, help1);
		mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xFF0000, help2);
	}
	else if (!ft_strncmp(s->prompt, "leaks", 6))
		system("leaks miniRT");
	else if (!ft_strncmp(s->prompt, "save", 5))
		export_file_save(s, 1);
	else if (!ft_strncmp(s->prompt, "id", 3))
		print_list_id();
	ft_free(&s->prompt);
	ft_free(&help1);
	ft_free(&help2);
	return (1);
}

void	get_prompt(t_minirt *s, int key)
{
	char	*tmp;

	tmp = NULL;
	push_img_to_win(s, PROMPT);
	if (key == BACKSP)
		key_backspace(s, tmp);
	else if (key == ENTER && s->prompt)
		key_enter(s);
	else if (key >= 0 && key < 53)
		type_key(s, tmp, key);
	if (s->prompt)
		mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xBA55D3, s->prompt);
}
