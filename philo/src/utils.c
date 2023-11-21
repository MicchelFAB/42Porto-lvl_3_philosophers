/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/21 18:21:58 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi_philo(char *str)
{
	int r = 0;
	int sg = 1;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1); 
	return (sg * r);
}

int waiting(t_philo *philo, struct timeval start, long wait_time)
{
	struct timeval now;
	long time;

	while (1)
	{
		if (*(philo->dead) == 1 || philo->meal == 1)
			return (-1);
		gettimeofday(&now, NULL);
		time = ((now.tv_sec - start.tv_sec) * 1000000 + now.tv_usec - start.tv_usec);
		if(time >= wait_time)
			break;
		usleep(100);
	}
	return (0);
}