/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:51:55 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 17:30:55 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_puterr(char *str)
{
	write(2, str, ft_strlen(str));
	return (-1);
}

void	ft_putnbr(long long n)
{
	char	*str;

	str = ft_itoa_philo(n);
	write(1, str, ft_strlen(str));
	free(str);
}

static int	decimal_places(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n = -n;
	}
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa_philo(int nbr)
{
	long	n;
	int		i;
	char	*s;

	n = nbr;
	i = decimal_places(n);
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	s[i--] = '\0';
	if (n == 0)
	{
		s[0] = '0';
		return (s);
	}
	while (n)
	{
		s[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	return (s);
}
