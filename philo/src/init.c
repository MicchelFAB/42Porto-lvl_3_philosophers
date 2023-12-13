/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:06:51 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/12 18:20:49 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_common	common;

	if (check_args(ac, av, &common) == -1)
		return (printf("Error: Invalid arguments.\n"));
	if (putting_the_table(&common) == -1)
		return (printf("Error: Failed to put the table.\n"));
	if (start_event(&common) == -1)
		return (printf("Error: Failed to create thread.\n"));
	waiter(&common);
	return (0);
}

int	check_args(int ac, char **av, t_common *args)
{
	if (ac < 5 || ac > 6)
		return (-1);
	args->philo_on_table = ft_atoi_philo(av[1]);
	args->death_clock = ft_atoi_philo(av[2]);
	args->eat_delay = ft_atoi_philo(av[3]);
	args->sleeping_time = ft_atoi_philo(av[4]);
	if (args->philo_on_table == -1 || args->death_clock == -1 || args->eat_delay
		== -1 || args->sleeping_time == -1)
		return (-1);
	if (!av[5])
		args->nbr_of_meals = -1;
	else
	{
		args->nbr_of_meals = ft_atoi_philo(av[5]);
		if (args->nbr_of_meals == -1)
			return (-1);
	}
	args->finish_flag = 0;
	args->tummy_hurts = 0;
	return (0);
}

int	putting_the_table(t_common *setup)
{
	int	i;

	i = -1;
	setup->philo = malloc(sizeof(t_philo) * setup->philo_on_table);
	if (!setup->philo)
		return (-1);
	while (++i < setup->philo_on_table)
	{
		setup->philo[i].id = i + 1;
		setup->philo[i].fork[0] = i;
		if (i == setup->philo_on_table - 1)
			setup->philo[i].fork[1] = 0;
		else
			setup->philo[i].fork[1] = i + 1;
		setup->philo[i].eating = 0;
		setup->begin = queued(setup->philo, -1);
		setup->philo[i].lst_meal = setup->begin;
		setup->philo[i].common = setup;
	}
	if (putting_the_cutlery(setup) == -1)
		return (-1);
	return (0);
}

int	putting_the_cutlery(t_common *silverware)
{
	int	i;

	i = -1;
	silverware->fork_hold = malloc(sizeof(pthread_mutex_t)
			* silverware->philo_on_table);
	if (!silverware->fork_hold)
		return (-1);
	while (++i < silverware->philo_on_table)
	{
		if (pthread_mutex_init(&silverware->fork_hold[i], NULL))
			return (-1);
	}
	if (pthread_mutex_init(&silverware->print_status, NULL))
		return (-1);
	if (pthread_mutex_init(&silverware->chew, NULL))
		return (-1);
	if (pthread_mutex_init(&silverware->session_end, NULL))
		return (-1);
	return (0);
}

int	start_event(t_common *data)
{
	int			i;

	i = -1;
	while (++i < data->philo_on_table)
	{
		if (pthread_create(&data->philo[i].p_thread, NULL, symposium,
				&data->philo[i]))
			return (-1);
	}
	return (0);
}
