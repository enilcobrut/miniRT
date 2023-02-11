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

void	type_key(t_minirt *s, char *tmp, int key)
{
	if (!s->prompt)
			s->prompt = ft_strdup("");
	tmp = ft_strjoin_char(s->prompt, s->k[key]);
	ft_free(&s->prompt);
	s->prompt = ft_strdup(tmp);
	ft_free(&tmp);
}
