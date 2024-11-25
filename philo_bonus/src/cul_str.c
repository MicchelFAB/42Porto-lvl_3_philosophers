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
#include <iostream>
#include <string>

size_t	ft_strlen(const char *s)
{
	return std::strlen(s);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (!src)
		return 0;
	std::strncpy(dst, src, size);
	return std::strlen(src);
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
