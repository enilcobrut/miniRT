#include "miniRT.h"

int	is_key_move(int key)
{
	if (key == 126 || key == 123 || key == 124 || key == 125 || key == 69
		|| key == 78|| key == 91|| key == 86|| key == 84 || key == 88
		|| key == 83 || key == 85)
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
