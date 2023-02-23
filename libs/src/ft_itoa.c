/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:15:53 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/15 19:21:54 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_recursive_counter(long n)
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

char	*ft_itoa(int n)
{
	char	*str;
	long	tmp;
	int		len;

	tmp = n;
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_recursive_counter(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (0);
	str[0] = 0;
	if (n < 0)
	{
		str[0] = '-';
		tmp = -tmp;
	}
	str[len] = '\0';
	while (tmp != 0)
	{
		len--;
		str[len] = tmp % 10 + '0';
		tmp = tmp / 10;
	}
	return (str);
}
