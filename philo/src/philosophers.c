/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:30 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/21 11:15:07 by mamaral-         ###   ########.fr       */
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

void *symposium(void *group)
{
	t_philo	*philo;
	pthread_t	monitoring;

	philo = (t_philo *)group;
	pthread_create(&monitoring, NULL, monitor, philo);
	if(philo->id % 2 == 0)
		waiting(philo, philo->common.begin, philo->common.eat_delay / 2);
	while (1)
	{
		if (routine(philo) == -1)
			return (NULL);
		usleep(500);
	}
	pthread_join(monitoring, NULL);
	return (NULL);
}
}

int putting_the_cutlery(t_common silverware, t_philo **philo)
{
	pthread_mutex_t	*fork;
	int				*ticket;
	int				i;
	
	fork = malloc(sizeof(pthread_mutex_t) * silverware.philo_on_table);
	ticket = malloc(sizeof(int) * silverware.philo_on_table);
	if (!fork || !ticket)
		return (-1);
	i = -1;
	while (++i < silverware.philo_on_table)
	{
		pthread_mutex_init(&fork[i], NULL);
		ticket[i] = 1;
	}
	i = -1;
	while (++i < silverware.philo_on_table)
	{
		(*philo)[i].fork = fork;
		(*philo)[i].alive_n = ticket;
	}
	return (0);

}

int putting_the_table(t_common setup, t_philo **philo)
{
	pthread_mutex_t	conf_res;
	int				i;
	int				*dead;
	
	*philo = malloc(sizeof(t_philo) * setup.philo_on_table);
	dead = malloc(sizeof(int));
	if (!*philo || !dead)
		return (-1);
	*dead = 0;
	pthread_mutex_init(&conf_res, NULL);
	i = -1;
	while (++i < setup.philo_on_table)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].eating = 0;
		(*philo)[i].meals = 0;
		(*philo)[i].dead = dead;
		(*philo)[i].lst_meal = setup.begin;
		(*philo)[i].p_dead = conf_res;
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
	args->philo_on_table = ft_atoi(av[1]);
	args->death_clock = ft_atoi(av[2]);
	args->eat_delay = ft_atoi(av[3]);
	args->sleeping_time = ft_atoi(av[4]);
	if(args->philo_on_table == -1 || args->death_clock == -1
		|| args->eat_delay == -1 || args->sleeping_time == -1)
		return (-1);
	if(!av[5])
		args->number_of_meals = -1;
	else
	{
		args->number_of_meals = ft_atoi(av[5]);
		if (args->number_of_meals == -1)
			return (-1);
	}
	gettimeofday(&args->begin, NULL);
	return (0);
}

int main(int ac, char **av)
{
	int			i;
	int			status;
	t_philo		*philo;
	t_common	common;
	
	i = -1;
	if (check_args(ac, av, &common) == -1)
		return (printf("Error: Invalid arguments.\n"));
	if (putting_the_table(common, &philo) == -1)
		return (printf("Error: Failed to put the table.\n"));
	while (++i < common.philo_on_table)
	{
		status = pthread_create(&philo[i].p_thread, NULL, symposium, &philo[i]);
		if (status < 0)
		{
			clean_table(philo, common);
			printf("Error: Failed to create thread.\n");
			return (-1);
		}
	}
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