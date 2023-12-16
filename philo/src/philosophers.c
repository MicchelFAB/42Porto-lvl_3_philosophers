/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:06:19 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 18:02:26 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	serving(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->common->fork_hold[philo->fork[0]]);
		checking_table(philo, "\thas taken a fork\n");
		pthread_mutex_lock(&philo->common->fork_hold[philo->fork[1]]);
		checking_table(philo, "\thas taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->common->fork_hold[philo->fork[1]]);
		checking_table(philo, "\thas taken a fork\n");
		pthread_mutex_lock(&philo->common->fork_hold[philo->fork[0]]);
		checking_table(philo, "\thas taken a fork\n");
	}
	checking_table(philo, "\tis eating\n");
	queued(philo, philo->common->eat_delay);
	pthread_mutex_lock(&philo->common->chew);
	philo->eating++;
	philo->lst_meal = queued(philo, -1);
	pthread_mutex_unlock(&philo->common->chew);
	pthread_mutex_unlock(&philo->common->fork_hold[philo->fork[0]]);
	pthread_mutex_unlock(&philo->common->fork_hold[philo->fork[1]]);
}

void	*table_for_one(t_common *common)
{
	checking_table(&common->philo[0], "\thas taken a fork\n");
	queued(&common->philo[0], common->death_clock);
	checking_table(&common->philo[0], "sike");
	remove_plates(&common->philo[0], YES);
	return (0);
}

void	*symposium(void *group)
{
	t_philo	*philo;

	philo = (t_philo *)group;
	if (philo->id % 2 == 0)
		usleep(philo->common->eat_delay * 1000);
	while (1)
	{
		if (philo->common->philo_on_table == 1)
			return (table_for_one(philo->common));
		serving(philo);
		if (remove_plates(philo, NO))
			return (0);
		if (philo->eating == philo->common->nbr_of_meals)
			return (0);
		checking_table(philo, "\tis sleeping\n");
		queued(philo, philo->common->sleeping_time);
		checking_table(philo, "\tis thinking\n");
		if (philo->common->philo_on_table % 2 != 0
			&& philo->common->philo_on_table <= 127)
			queued(philo, philo->common->eat_delay);
	}
	return (0);
}

int	table_service(t_philo *philo)
{
	long long	now;

	now = queued(philo, -1);
	pthread_mutex_lock(&philo->common->chew);
	if ((now - philo->lst_meal) >= philo->common->death_clock)
	{
		remove_plates(philo, YES);
		checking_table(philo, "\tdied\n");
		pthread_mutex_unlock(&philo->common->chew);
		return (1);
	}
	else if (philo->common->nbr_of_meals > 0 && philo->eating >= philo
		->common->nbr_of_meals)
	{
		philo->common->tummy_hurts++;
		if (philo->common->tummy_hurts >= philo->common->philo_on_table)
		{
			remove_plates(philo, YES);
			checking_table(philo, "Number of meals reached\n");
			pthread_mutex_unlock(&philo->common->chew);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->common->chew);
	return (0);
}

void	waiter(t_common *guests)
{
	int	i;
	int	meals;

	meals = 1;
	while (meals)
	{
		i = -1;
		guests->tummy_hurts = 0;
		while (++i < guests->philo_on_table)
		{
			if (meals && table_service(&guests->philo[i]))
				meals = 0;
		}
		usleep(10);
	}
	clean_table(guests);
}
