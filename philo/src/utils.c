/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/04 17:12:52 by mamaral-         ###   ########.fr       */
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

// int queued(t_philo *philo, struct timeval start, long wait_time)
// {
// 	struct timeval now;
// 	long time;

// 	while (1)
// 	{
// 		if (*(philo->dead) == 1 || philo->meals == 1)
// 			return (-1);
// 		gettimeofday(&now, NULL);
// 		time = ((now.tv_sec - start.tv_sec) * 1000000 + now.tv_usec - 
// 					start.tv_usec);
// 		if(time >= wait_time * 1000)
// 			break;
// 		usleep(100);
// 	}
// 	return (0);
// }

void	clean_table(t_common *common)
{
	int i;

	i = -1;
	while (++i < common->philo_on_table)
		pthread_join(common->philo[i].p_thread, NULL);
	i = -1;
	while (++i < common->philo_on_table)
		pthread_mutex_destroy(&common->fork_hold[i]);
	free(common->philo);
	free(common->fork_hold);
	pthread_mutex_destroy(&common->print_status);
	pthread_mutex_destroy(&common->chew);
	pthread_mutex_destroy(&common->session_end);
}

long	elapsed_time(struct timeval a, struct timeval b)
{
	return (((a.tv_sec - b.tv_sec) * 1000000 + a.tv_usec - b.tv_usec) / 1000);
}

void	checking_table(t_philo *philo, const char *status)
{
	long long	time;
	struct timeval now;
	
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->common->print_status);
	if (!remove_plates(philo, NO))
	{
		time = elapsed_time(now, philo->common->begin);
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->common->print_status);
	if (status[0] == 'A')
		printf("%s\n", "All philosophers ate enough!");
}

void	queued(t_philo *philo, long long end)
{
	long long	begin;

	begin = get_now();
	while (!remove_plates(philo, NO) && (get_now() - begin) < end)
		usleep(100);
}

long long	get_now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}
