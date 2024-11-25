/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gastr_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:06:19 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 13:38:08 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"
#include <iostream>
#include <thread>
#include <mutex>

void	serving(Philo *philo)
{
	philo->common->forks.acquire();
	checking_table(philo, " has taken a fork\n");
	philo->common->forks.acquire();
	checking_table(philo, " has taken a fork\n");
	checking_table(philo, " is eating\n");
	philo->lst_meal.acquire();
	philo->time_lst_meal = get_now();
	philo->lst_meal.release();
	std::this_thread::sleep_for(philo->common->eat_delay);
	philo->common->forks.release();
	philo->common->forks.release();
	if (++philo->eating == philo->common->nbr_of_meals)
		philo->common->chew.release();
}

void	banquet(Philo *philo)
{
	char		*str;

	philo->eating = 0;
	philo->common->forks = std::binary_semaphore(1);
	philo->common->print_status = std::binary_semaphore(1);
	philo->common->chew = std::binary_semaphore(0);
	philo->common->session_end = std::binary_semaphore(0);
	str = get_philo_name("/lst_meal", philo->id);
	philo->lst_meal = std::binary_semaphore(1);
	free(str);
	philo->time_lst_meal = philo->common->begin;
	philo->p_thread = std::thread(monitor_death, philo);
	while (1)
	{
		serving(philo);
		checking_table(philo, " is sleeping\n");
		std::this_thread::sleep_for(philo->common->sleeping_time);
		checking_table(philo, " is thinking\n");
	}
}

pid_t	monitor_meals(void *ph)
{
	Philo	*philo;
	int		count;
	pid_t	pid;

	philo = static_cast<Philo*>(ph);
	count = 0;
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			philo->common->chew.acquire();
			if (++count >= philo->common->philo_on_table)
			{
				leaving_tbl(ph, "Number of meals reached!\n");
				exit(0);
				return 0;
			}
		}
	}
	return (pid);
}

void	*monitor_death(void *ph)
{
	Philo		*philo;
	long long	timestamp;

	philo = static_cast<Philo*>(ph);
	while (1)
	{
		philo->lst_meal.acquire();
		timestamp = get_now();
		if (timestamp - philo->time_lst_meal > philo->common->death_clock)
		{
			philo->lst_meal.release();
			leaving_tbl(ph, " died\n");
			return NULL;
		}
		philo->lst_meal.release();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int	remove_plates(Common *dishes, pid_t *pid, pid_t pid2)
{
	int	i;

	dishes->session_end.acquire();
	i = -1;
	while (++i < dishes->philo_on_table)
		kill(pid[i], SIGKILL);
	if (dishes->nbr_of_meals > 0)
		kill(pid2, SIGKILL);
	unlink_tableware(dishes);
	free(pid);
	return (0);
}
