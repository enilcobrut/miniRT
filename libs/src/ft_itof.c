/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:11:42 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/16 12:15:15 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_recursive_counter(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n >= 10)
	{
		n = n / 10;
		ft_recursive_counter(n);
		len++;
	}
	return (len);
}

char	*ft_itof_next(char *integer, char *tmp_, long tmp)
{
	int		len;
	char	*str;

	len = ft_recursive_counter(tmp) + 1;
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (0);
	while (len)
	{
		len--;
		str[len] = tmp % 10 + '0';
		tmp = tmp / 10;
	}
	str[len] = '.';
	tmp_ = ft_strjoin(integer, str);
	free(str);
	return (tmp_);
}

char	*ft_itof(double n)
{
	char	*str;
	long	tmp;
	char	*integer;
	char	*tmp_;

	str = NULL;
	tmp_ = NULL;
	if ((n < 0 && n > -1))
		integer = ft_strdup("-0");
	else
		integer = ft_itoa(n);
	n -= (int)n;
	tmp = n * 1000;
	if (n < 0)
		tmp = -tmp;
	if (tmp == 0)
		tmp_ = ft_strjoin(integer, ".000");
	else
		tmp_ = ft_itof_next(integer, tmp_, tmp);
	free(integer);
	free(str);
	return (tmp_);
}
