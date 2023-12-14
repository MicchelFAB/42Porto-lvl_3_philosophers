/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:06:19 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/14 13:26:45 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	serving(t_philo *philo)
{
	sem_wait(philo->common->forks);
	checking_table(philo, " has taken a fork\n");
	sem_wait(philo->common->forks);
	checking_table(philo,  " has taken a fork\n");
	checking_table(philo, " is eating\n");
	sem_wait(philo->lst_meal);
	philo->time_lst_meal = get_now();
	sem_post(philo->lst_meal);
	usleep(philo->common->eat_delay);
	sem_post(philo->common->forks);
	sem_post(philo->common->forks);
	if (++philo->eating == philo->common->nbr_of_meals)
		sem_post(philo->common->chew);
}

void	banquet(t_philo *philo)
{
	char		*str;

	philo->eating = 0;
	philo->common->forks = sem_open("/forks", 0644);
	philo->common->print_status = sem_open("/print_status", 0644);
	philo->common->chew = sem_open("/chew", 0644);
	philo->common->session_end = sem_open("/session_end", 0644);
	str = get_philo_name("/lst_meal", philo->id);
	philo->lst_meal = sem_open(str, 0644);
	free(str);
	philo->time_lst_meal = philo->common->begin;
	pthread_create(&philo->p_thread, NULL, monitor_death, philo);
	while (1)
	{
		serving(philo);
		checking_table(philo, " is sleeping\n");
		usleep(philo->common->sleeping_time);
		checking_table(philo, " is thinking\n");
	}
}

pid_t	monitor_meals(void *ph)
{
	t_philo			*philo;
	int				count;
	pid_t pid;
	
	philo = ph;
	count = 0;
	pid = fork();
	if(pid == 0)
	{
		while (1)
		{
			sem_wait(philo->common->chew);
			if (++count >= philo->common->philo_on_table)
			{
				leaving_tbl(ph, "Number of meals reached!\n");
				exit(0);
			}
		}
	}
	return (pid);
}

void	*monitor_death(void *ph)
{
	t_philo			*philo;
	long long	timestamp;

	philo = ph;
	while (1)
	{
		sem_wait(philo->lst_meal);
		if ((timestamp = get_now()) - philo->time_lst_meal > philo->common->death_clock)
		{
			sem_post(philo->lst_meal);
			leaving_tbl(ph, " has died\n");
			return (NULL);
		}
		sem_post(philo->lst_meal);
		usleep(10);
	}
}

int	remove_plates(t_common *dishes, pid_t *pid, pid_t pid2)
{
	int i;

	sem_wait(dishes->session_end);
	i = -1;
	while (++i < dishes->philo_on_table)
		kill(pid[i], SIGKILL);
	if(dishes->nbr_of_meals > 0) 
		kill(pid2, SIGKILL);
	unlink_tableware(dishes);
	free(pid);
	return (0);
}