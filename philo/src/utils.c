/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/04 15:17:25 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi_philo(char *str)
{
	int r;

	r = 0;
	if (str == NULL || str[0] == '-')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1); 
	return (r);
}

int queued(t_philo *philo, struct timeval start, long wait_time)
{
	struct timeval now;
	long time;

	while (1)
	{
		if (*(philo->dead) == 1 || philo->meals == 1)
			return (-1);
		gettimeofday(&now, NULL);
		time = ((now.tv_sec - start.tv_sec) * 1000000 + now.tv_usec - 
					start.tv_usec);
		if(time >= wait_time * 1000)
			break;
		usleep(100);
	}
	return (0);
}

void	clean_table(t_philo *group, t_common common)
{
	int	i;
	int	status;

	i = -1;
	while (++i < common.philo_on_table)
	{
		pthread_mutex_destroy(&group[0].fork[i]);
		pthread_join(group[i].p_thread, (void *)&status);
	}
	pthread_mutex_destroy(&group[0].p_dead);
	free(group[0].dead);
	free(group[0].fork);
	free(group[0].alive_guest);
	free(group);
}

void	checking_table(t_philo *philo, const char *status)
{
	long long	time;
	struct timeval now;
	
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->common->print_status);
	if (!free_table(philo, NO))
	{
		time = elapsed_time(now, philo->common->begin);
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->common->print_status);
}

void	queued(t_philo *philo, long long end)
{
	long long	begin;

	begin = get_now();
	while (!free_table(philo, NO) && (get_now() - begin) < end)
		usleep(100);
}

long long	get_now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}
