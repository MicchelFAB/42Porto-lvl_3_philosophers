/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 18:10:15 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_philo(char *str)
{
	int	r;

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

void	clean_table(t_common *common)
{
	int	i;

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

void	checking_table(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->common->print_status);
	if (!remove_plates(philo, NO))
	{
		ft_putnbr(queued(philo, -1) - philo->common->begin);
		write(1, "\t", 1);
		ft_putnbr(philo->id);
		write(1, status, ft_strlen(status));
	}
	if (status[0] == 'N')
		write(1, status, ft_strlen(status));
	else if (status[1] == 'd')
	{
		ft_putnbr(queued(philo, -1) - philo->common->begin);
		write(1, "\t", 1);
		ft_putnbr(philo->id);
		write(1, status, ft_strlen(status));
	}
	pthread_mutex_unlock(&philo->common->print_status);
}

long long	queued(t_philo *philo, long long end)
{
	long long		begin;
	long long		now;
	struct timeval	timeval;

	now = 0;
	gettimeofday(&timeval, NULL);
	begin = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	if (end == -1)
		return (begin);
	else
	{
		while (!remove_plates(philo, NO) && (now - begin) < end)
		{
			gettimeofday(&timeval, NULL);
			now = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
			usleep(500);
		}
	}
	return (0);
}

int	remove_plates(t_philo *philo, int dinner_end)
{
	pthread_mutex_lock(&philo->common->session_end);
	if (dinner_end || philo->common->finish_flag)
	{
		if (dinner_end)
			philo->common->finish_flag = 1;
		pthread_mutex_unlock(&philo->common->session_end);
		return (1);
	}
	pthread_mutex_unlock(&philo->common->session_end);
	return (0);
}
