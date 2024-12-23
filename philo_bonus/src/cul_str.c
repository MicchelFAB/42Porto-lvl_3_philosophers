/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cul_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:51:55 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 16:36:47 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!src)
		return (0);
	i = 0;
	if (size > 0)
	{
		while (src[i] && (i < (size - 1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
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
