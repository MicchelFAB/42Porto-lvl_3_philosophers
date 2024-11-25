/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbl_serv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 16:38:28 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"
#include <iostream>
#include <chrono>

std::chrono::time_point<std::chrono::steady_clock> get_now()
{
    return std::chrono::steady_clock::now();
}

unsigned long ft_atol_philo(char *str)
{
    unsigned long r = 0;
    if (str == NULL || str[0] == '-')
        return -1;
    while (*str >= '0' && *str <= '9')
    {
        r = r * 10 + (*str - '0');
        str++;
    }
    if (*str != '\0')
        return -1;
    return r;
}

static int decimal_places(long n)
{
    int i = 0;
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
    return i;
}

char *ft_itoa_philo(int nbr)
{
    long n = nbr;
    int i = decimal_places(n);
    char *s = (char *)malloc(sizeof(char) * (i + 1));
    if (!s)
        return NULL;
    s[i--] = '\0';
    if (n == 0)
    {
        s[0] = '0';
        return s;
    }
    while (n)
    {
        s[i] = n % 10 + '0';
        n /= 10;
        i--;
    }
    return s;
}
