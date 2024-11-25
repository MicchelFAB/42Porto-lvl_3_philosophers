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
#include <iostream>
#include <string>

size_t	ft_strlen(const char *s)
{
	return std::strlen(s);
}

int	ft_puterr(char *str)
{
	std::cerr << str;
	return -1;
}

void	ft_putnbr(long long n)
{
	std::cout << n;
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
	s = (char*)malloc(sizeof(char) * (i + 1));
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
