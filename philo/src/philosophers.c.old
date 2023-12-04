/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:30 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/22 15:49:25 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philosophers.c
 * @author Michel Batista (mamaral-@student.42porto.com)
 * @brief This file contains the implementation of the philosophers' functions.
 * 
 * @version 0.1
 * @date 2023/11/20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "philo.h"

int	contemplating_and_napping(t_philo *philo)
{
	struct timeval	actual;
	long			this_moment;

	gettimeofday(&actual, NULL);
	this_moment = elapsed_time(actual, philo->common.begin);
	if (*(philo->dead) == 1 || philo->meals == 1)
		return (-1);
	printf("%3ldms %d is sleeping\n", this_moment, philo->id + 1);
	if (queued(philo, actual, philo->common.sleeping_time) == -1)
		return (-1);
	gettimeofday(&actual, NULL);
	this_moment = elapsed_time(actual, philo->common.begin);
	if (*(philo->dead) == 1 || philo->meals == 1)
		return (-1);
	printf("%3ldms %d is thinking\n", this_moment, philo->id + 1);
	return (0);
}

int	munching(t_philo *philo)
{
	struct timeval	actual;
	long			this_moment;

	gettimeofday(&actual, NULL);
	this_moment = elapsed_time(actual, philo->common.begin);
	if (*(philo->dead) == 1 || philo->meals == 1)
		return (-1);
	printf("%3ldms %d has taken a fork\n", this_moment, philo->id + 1);
	gettimeofday(&actual, NULL);
	this_moment = elapsed_time(actual, philo->common.begin);
	if (*(philo->dead) == 1 || philo->meals == 1)
		return (-1);
	philo->lst_meal = actual;
	printf("%3ldms %d is eating\n", this_moment, philo->id + 1);
	(philo->eating)++;
	if (queued(philo, actual, philo->common.eat_delay) == -1)
		return (-1);
	return (0);
}

int	pick_fork(t_philo *philo, pthread_mutex_t *r_hand, pthread_mutex_t *l_hand)
{
	if (r_hand == l_hand)
		while (1)
			if (*(philo->dead) == 1)
				return (-1);
	pthread_mutex_lock(r_hand);
	pthread_mutex_lock(l_hand);
	return (0);
}
void	release_fork(pthread_mutex_t *r_hand, pthread_mutex_t *l_hand)
{
	pthread_mutex_unlock(r_hand);
	pthread_mutex_unlock(l_hand);
}
int	serving(t_philo *philo)
{
	int	num_of_philo;

	num_of_philo = philo->common.philo_on_table;
	if (pick_fork(philo, &philo->fork[philo->id],
			&philo->fork[(philo->id + 1) % num_of_philo]) == -1)
		return (-1);
	if (munching(philo) == -1)
	{
		release_fork(&philo->fork[philo->id],
			&philo->fork[(philo->id + 1) % num_of_philo]);
		return (-1);
	}
	release_fork(&philo->fork[philo->id],
		&philo->fork[(philo->id + 1) % num_of_philo]);
	if (contemplating_and_napping(philo) == -1)
		return (-1);
	return (0);
}

long	elapsed_time(struct timeval a, struct timeval b)
{
	return (((a.tv_sec - b.tv_sec) * 1000000 + a.tv_usec - b.tv_usec) / 1000);
}

void	starvin_philo(t_philo *philo, struct timeval actual)
{
	long	time;

	pthread_mutex_lock(&philo->p_dead);
	if (*(philo->dead) == 0)
	{
		*(philo->dead) = 1;
		pthread_mutex_unlock(&philo->fork[philo->id]);
		time = elapsed_time(actual, philo->common.begin);
		printf("%3ldms %d died\n", time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->p_dead);
}

void	*waiter(void *guest)
{
	struct timeval	now;
	t_philo			*philo;
	long			time;

	philo = (t_philo *)guest;
	while (1)
	{
		if (philo->common.number_of_meals != -1	&& philo->eating >= philo->common.number_of_meals)
		{
			philo->meals = 1;
			return (NULL);
		}
		gettimeofday(&now, NULL);
		time = elapsed_time(now, philo->lst_meal);
		if (time > philo->common.death_clock)
		{
			starvin_philo(philo, now);
			return (NULL);
		}
		queued(philo, now, 1);
	}
}

void *symposium(void *group)
{
	t_philo	*philo;
	pthread_t	monitoring;

	philo = (t_philo *)group;
	pthread_create(&monitoring, NULL, waiter, philo);
	if(philo->id % 2 == 0)
		queued(philo, philo->common.begin, philo->common.eat_delay / 2);
	while (1)
	{
		if (serving(philo) == -1)
			return (NULL);
		usleep(500);
	}
	pthread_join(monitoring, NULL);
	return (NULL);
}

int putting_the_cutlery(t_common silverware, t_philo **philo)
{
	pthread_mutex_t	*fork;
	int				*invite;
	int				i;
	
	fork = malloc(sizeof(pthread_mutex_t) * silverware.philo_on_table);
	invite = malloc(sizeof(int) * silverware.philo_on_table);
	if (!fork || !invite)
		return (-1);
	i = -1;
	while (++i < silverware.philo_on_table)
	{
		pthread_mutex_init(&fork[i], NULL);
		invite[i] = 1;
	}
	i = -1;
	while (++i < silverware.philo_on_table)
	{
		(*philo)[i].fork = fork;
		(*philo)[i].alive_guest = invite;
	}
	return (0);

}

int putting_the_table(t_common setup, t_philo **philo)
{
	pthread_mutex_t	conflict_resolution;
	int				i;
	int				*dead;
	
	*philo = malloc(sizeof(t_philo) * setup.philo_on_table);
	dead = malloc(sizeof(int));
	if (!*philo || !dead)
		return (-1);
	*dead = 0;
	pthread_mutex_init(&conflict_resolution, NULL);
	i = -1;
	while (++i < setup.philo_on_table)
	{
		(*philo)[i].id = i;
		(*philo)[i].eating = 0;
		(*philo)[i].meals = 0;
		(*philo)[i].dead = dead;
		(*philo)[i].lst_meal = setup.begin;
		(*philo)[i].p_dead = conflict_resolution;
		(*philo)[i].common = setup;
	}
	if(putting_the_cutlery(setup, philo) == -1)
		return (-1);
	return (0);
}

int check_args(int ac, char **av, t_common *args)
{
	if (ac < 5 || ac > 6)
		return (-1);
	args->philo_on_table = ft_atoi_philo(av[1]);
	args->death_clock = ft_atoi_philo(av[2]);
	args->eat_delay = ft_atoi_philo(av[3]);
	args->sleeping_time = ft_atoi_philo(av[4]);
	if(args->philo_on_table == -1 || args->death_clock == -1
		|| args->eat_delay == -1 || args->sleeping_time == -1)
		return (-1);
	if(!av[5])
		args->number_of_meals = -1;
	else
	{
		args->number_of_meals = ft_atoi_philo(av[5]);
		if (args->number_of_meals == -1)
			return (-1);
	}
	gettimeofday(&args->begin, NULL);
	return (0);
}

int	start_event(t_philo *visitor, t_common data)
{
	int			i;
	int			status;
	
	i = -1;
	while (++i < data.philo_on_table)
	{
		status = pthread_create(&visitor[i].p_thread, NULL, symposium, &visitor[i]);
		if (status < 0)
		{
			clean_table(visitor, data);
			return (-1);
		}
	}
	return (0);
}
int main(int ac, char **av)
{
	t_philo		*philo;
	t_common	common;
	
	if (check_args(ac, av, &common) == -1)
		return (printf("Error: Invalid arguments.\n"));
	if (putting_the_table(common, &philo) == -1)
		return (printf("Error: Failed to put the table.\n"));
	if (start_event(philo, common) == -1)
		return(printf("Error: Failed to create thread.\n"));
	clean_table(philo, common);
	return (0);
}

/* memset - In the Philosopher project, this function is used to initialize the
 * philosophers' structure. 
 * 
 * printf - In the Philosopher project, this function is used to print the
 * philosophers' status. 
 * 
 * malloc - In the Philosopher project, this function is used to allocate memory
 * for the philosophers' structure.
 * 
 * free - In the Philosopher project, this function is used to free the memory
 * allocated for the philosophers' structure.
 * 
 * write - In the Philosopher project, this function is used to write the 
 * philosophers' status. 
 * 
 * usleep - In the Philosopher project, this function is used to make the
 * philosophers sleep.
 * 
 * gettimeofday - In the Philosopher project, this function is used to get the
 * current time, and to calculate the time elapsed since the start of the
 * simulation.
 * 
 * pthread_create - In the Philosopher project, this function is used to create
 * the threads for the philosophers.
 * 
 * pthread_detach - In the Philosopher project, this function is used to detach
 * the threads for the philosophers. 
 * 
 * pthread_join - In the Philosopher project, this function is used to join the
 * threads for the philosophers. 
 * 
 * pthread_mutex_init - In the Philosopher project, this function is used to
 * initialize the mutexes for the forks. 
 * 
 * pthread_mutex_destroy - In the Philosopher project, this function is used to
 * destroy the mutexes for the forks. 
 * 
 * pthread_mutex_lock - In the Philosopher project, this function is used to
 * lock the mutexes for the forks. 
 * 
 * pthread_mutex_unlock - In the Philosopher project, this function is used to
 * unlock the mutexes for the forks.
 */