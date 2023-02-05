
#include "miniRT.h"

void	init_set(t_minirt *s)
{
	s->on = 0;
	s->prompt_stat = 1;
	s->nt = NUMBER_THREAD;
	s->samples_per_pixel = SAMPLE_P_PIX;
	s->depth = DEPTH;
	s->params = NULL;
	s->prompt = NULL;
	s->amb_light_ratio = 0;
	s->cam_fov = 0;
	s->light_brightness_ratio = 0;
	s->cam_param_display = 1;
	s->obj = NULL;
	s->mlx = NULL;
	s->win = NULL;
	s->img.img = ft_calloc(2, sizeof(void *));
	s->img.add_r = ft_calloc(2, sizeof(char *));
	s->title = ft_strdup("miniRT");
	s->k = "asdfhgzxcv\0bqweryt123465+97-80]ou[ip\0lj'k;\\,/nm.\0 `\0";
}

void	free_split(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
		{
			ft_free(((*str) + i));
			i++;
		}
		free(*str);
		*str = 0;
	}
}

void	ft_free(char **to_free)
{
	if (*to_free)
		free(*to_free);
	*to_free = NULL;
}

void	mem_alloc_with_calloc(t_minirt *s, void ***ptr, size_t size)
{
	*ptr = ft_calloc(size, sizeof(void *));
	if (*ptr == NULL)
		exit_error(s, "Malloc error", 0);
}
