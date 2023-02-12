/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:46:57 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 20:49:22 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	type_key(t_minirt *s, char *tmp, int key)
{
	if (!s->prompt)
			s->prompt = ft_strdup("");
	tmp = ft_strjoin_char(s->prompt, s->k[key]);
	ft_free(&s->prompt);
	s->prompt = ft_strdup(tmp);
	ft_free(&tmp);
}

void	display_prompt_status(t_minirt *s)
{
	if (s->prompt_stat == 1)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0x00FF00, "*");
	else
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
}

void	print_list_id(void)
{
	printf("C / coordinates of the view point / 3d normalized orientation");
	printf(" vector / FOV\n");
	printf("A / ambient lighting ratio in range [0.0,1.0] / Color RGB\n");
	printf("L / coordinates of the light point / light brightness ratio in ");
	printf(" range [0.0,1.0] / Color RGB\n");
	printf("sp / coordinates of the sphere center / diameter / Color RGB\n");
	printf("pl / coordinates / 3d normalized orientation vector / Color RGB\n");
	printf("cy / coordinates / 3d normalized orientation vector / diameter ");
	printf("/ height / Color RGB\n");
	printf("co / coordinates / 3d normalized orientation vector / diameter ");
	printf("/ height / Color RGB\n");
}

int	key_enter(t_minirt *s)
{
	char	*help1;
	char	*help2;

	help1 = ft_strdup("[F1] prompt [F2] cam param ");
	help2 = ft_strdup("[OTHER] help, id, print, or leaks");
	if (!ft_strncmp(s->prompt, "print", 6))
		print_params(s);
	else if (!ft_strncmp(s->prompt, "help", 5))
	{
		mlx_string_put(s->mlx, s->win, 60, HEIGHT + 2, 0xFF0000, help1);
		mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xFF0000, help2);
	}
	else if (!ft_strncmp(s->prompt, "leaks", 6))
		system("leaks miniRT");
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
	if (key == BACKSP && s->prompt)
	{
		tmp = ft_strdup(s->prompt);
		ft_free(&s->prompt);
		s->prompt = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		ft_free(&tmp);
	}
	else if (key == ENTER && s->prompt)
		key_enter(s);
	else if (key >= 0 && key < 53)
		type_key(s, tmp, key);
	if (s->prompt)
		mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xBA55D3, s->prompt);
}
