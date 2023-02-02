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

char	*ft_itof(double n)
{
	char	*str = NULL;
	long	tmp;
	int		len;
	char	*integer;
	char	*tmp_ = NULL;

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
	{
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
	}
	free(integer);
	free(str);
	return (tmp_);
}