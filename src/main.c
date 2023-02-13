/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:44:24 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/10 17:44:25 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt	*s;

	s = ft_calloc(sizeof(t_minirt), 1);
	if (!s)
		exit_error(s, 0, 0);
	s->argv = argv;
	s->argc = argc;
	check_void(s, 0);
	check_directory(s);
	check_extension_rt(s);
	init_set(s);
	get_params(s);
	get_identifiers(s, 0, 0, 0);
	start_ray_tracing(s);
}
