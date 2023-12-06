/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:06:19 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/06 15:01:49 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	serving(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->common->fork_hold[philo->l_fork]);
		pthread_mutex_lock(&philo->common->fork_hold[philo->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->common->fork_hold[philo->r_fork]);
		pthread_mutex_lock(&philo->common->fork_hold[philo->l_fork]);
	}
	checking_table(philo, "has taken a fork");
	checking_table(philo, "has taken a fork");
	checking_table(philo, "is eating");
	queued(philo, philo->common->eat_delay);
	pthread_mutex_lock(&philo->common->chew);
	philo->eating++;
	philo->lst_meal = get_now();
	pthread_mutex_unlock(&philo->common->chew);
	pthread_mutex_unlock(&philo->common->fork_hold[philo->l_fork]);
	pthread_mutex_unlock(&philo->common->fork_hold[philo->r_fork]);
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

void	table_for_one(t_common *common)
{
	checking_table(&common->philo[0], "has taken a fork");
	queued(&common->philo[0], common->death_clock);
	checking_table(&common->philo[0], "died");
	remove_plates(&common->philo[0], YES);
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
		{
			table_for_one(philo->common);
			return (0);
		}
		serving(philo);
		if (remove_plates(philo, NO))
			return (0);
		checking_table(philo, "is sleeping");
		queued(philo, philo->common->sleeping_time);
		checking_table(philo, "is thinking"); 
		if (philo->common->philo_on_table % 2 != 0
			&& philo->common->philo_on_table <= 127)
			queued(philo, philo->common->eat_delay);
	}
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

int putting_the_cutlery(t_common *silverware)
{
	int				i;

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

int	putting_the_table(t_common *setup)
{
	int				i;

	i = -1;
	setup->philo = malloc(sizeof(t_philo) * setup->philo_on_table);
	if (!setup->philo)
		return (-1);
	while (++i < setup->philo_on_table)
	{
		setup->begin = get_now();
		setup->philo[i].id = i + 1;
		setup->philo[i].r_fork = i;
		if (i == setup->philo_on_table - 1)
			setup->philo[i].l_fork = 0;
		else
			setup->philo[i].l_fork = i + 1;
		setup->philo[i].eating = 0;
		setup->philo[i].lst_meal = setup->begin;
		setup->philo[i].common = setup;
	}
	if (putting_the_cutlery(setup) == -1)
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
	if (args->philo_on_table == -1 || args->death_clock == -1 || args->eat_delay
		== -1 || args->sleeping_time == -1)
		return (-1);
	if (!av[5])
		args->number_of_meals = -1;
	else
	{
		args->number_of_meals = ft_atoi_philo(av[5]);
		if (args->number_of_meals == -1)
			return (-1);
	}
	args->finish_flag = 0;
	args->tummy_hurts = 0;
	return (0);
}

int table_service(t_philo *philo)
{
	long long	now;

	now = get_now();
	pthread_mutex_lock(&philo->common->chew);
	if((now - philo->lst_meal) >= philo->common->death_clock)
	{
		remove_plates(philo, YES);
		checking_table(philo, "died");
		pthread_mutex_unlock(&philo->common->chew);
		return (1);
	}
	else if(philo->common->number_of_meals > 0 && philo->eating >= philo->common->number_of_meals)
	{
		philo->common->tummy_hurts++;
		if (philo->common->tummy_hurts >= philo->common->philo_on_table)
		{
			remove_plates(philo, YES);
			checking_table(philo, "A");
			pthread_mutex_unlock(&philo->common->chew);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->common->chew);
	return (0);
}

void waiter(t_common *guests)
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

int	main(int ac, char **av)
{
	t_common	common;

	if (check_args(ac, av, &common) == -1)
		return (printf("Error: Invalid arguments.\n"));
	if (putting_the_table(&common) == -1)
		return (printf("Error: Failed to put the table.\n"));
	if (start_event(&common) == -1)
		return(printf("Error: Failed to create thread.\n"));
	waiter(&common);
}