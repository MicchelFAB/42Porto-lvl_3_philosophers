/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/13 15:32:31 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

unsigned long	ft_atol_philo(char *str)
{
	unsigned long	r;

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

// void	clean_table(t_common *common)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < common->philo_on_table)
// 		pthread_join(common->philo[i].p_thread, NULL);
// 	i = -1;
// 	while (++i < common->philo_on_table)
// 		pthread_mutex_destroy(&common->fork_hold[i]);
// 	free(common->philo);
// 	free(common->fork_hold);
// 	pthread_mutex_destroy(&common->print_status);
// 	pthread_mutex_destroy(&common->chew);
// 	pthread_mutex_destroy(&common->session_end);
// }

void	checking_table(t_philo *philo, const char *status)
{
	long long	time;

	sem_wait(philo->common->print_status);
	time = get_now() - philo->common->begin;
	printf("%lld %d %s\n", time, philo->id, status);
	sem_post(philo->common->print_status);
}

// long long	queued(t_philo *philo, long long end)
// {
// 	long long		begin;
// 	long long		now;
// 	struct timeval	timeval;

// 	now = 0;
// 	gettimeofday(&timeval, NULL);
// 	begin = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
// 	if (end == -1)
// 		return (begin);
// 	else
// 	{
// 		while (!remove_plates(philo, NO) && (now - begin) < end)
// 		{
// 			gettimeofday(&timeval, NULL);
// 			now = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
// 			usleep(100);
// 		}
// 	}
// 	return (0);
// }

long long	get_now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

// int	remove_plates(t_philo *philo, int dinner_end)
// {
// 	pthread_mutex_lock(&philo->common->session_end);
// 	if (dinner_end || philo->common->finish_flag)
// 	{
// 		if (dinner_end)
// 			philo->common->finish_flag = 1;
// 		pthread_mutex_unlock(&philo->common->session_end);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->common->session_end);
// 	return (0);
// }
