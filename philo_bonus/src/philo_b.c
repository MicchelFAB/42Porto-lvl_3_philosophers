/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:06:51 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 16:42:40 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"
#include <iostream>
#include <thread>
#include <mutex>

int	main(int ac, char **av)
{
	Common	common;

	if (check_args(ac, av, &common) == -1)
		return (ft_puterr("Error: Invalid arguments.\n"));
	if (putting_fancy_table(&common) == -1)
		return (ft_puterr("Error: Failed to put the table.\n"));
	if (start_fancy_event(&common) == -1)
		return (ft_puterr("Error: Failed to create processes.\n"));
	free(common.philo);
	return (0);
}

int	check_args(int ac, char **av, Common *args)
{
	if (ac < 5 || ac > 6)
	{
		ft_puterr("Arguments should be: [nbr_of_philo] [time_to_die] [time_to_eat]\
		 [time_to_sleep] *optional: [nbr_of_times_each_philo_must_eat]");
		return (-1);
	}
	args->philo_on_table = ft_atol_philo(av[1]);
	args->death_clock = std::chrono::milliseconds(ft_atol_philo(av[2]));
	args->eat_delay = std::chrono::milliseconds(ft_atol_philo(av[3]));
	args->sleeping_time = std::chrono::milliseconds(ft_atol_philo(av[4]));
	if (args->philo_on_table < 1 || args->death_clock.count() == -1 || args->eat_delay.count() == -1 || args->sleeping_time.count() == -1)
		return (-1);
	if (!av[5])
		args->nbr_of_meals = -1;
	else
	{
		args->nbr_of_meals = ft_atol_philo(av[5]);
		if (args->nbr_of_meals == -1)
			return (-1);
	}
	return (0);
}

int	putting_fancy_table(Common *common)
{
	int		i;
	int		err_flag;
	char	*str;

	i = -1;
	err_flag = 0;
	common->philo.resize(common->philo_on_table);
	while (++i < common->philo_on_table)
	{
		str = get_philo_name("/lst_meal", i);
		common->philo[i].lst_meal = std::binary_semaphore(1);
		free(str);
	}
	err_flag += putting_fancy_cutlery(common);
	if (err_flag)
		return (tbl_unavail(common));
	return (0);
}

int	putting_fancy_cutlery(Common *silver)
{
	silver->forks = std::binary_semaphore(silver->philo_on_table);
	silver->print_status = std::binary_semaphore(1);
	silver->chew = std::binary_semaphore(0);
	silver->session_end = std::binary_semaphore(0);
	return (0);
}

int	start_fancy_event(Common *common)
{
	int			i;
	std::vector<pid_t> philo_pid(common->philo_on_table);
	pid_t		food_pid;
	Philo		philo;

	i = -1;
	common->begin = get_now();
	while (++i < common->philo_on_table)
	{
		philo.id = i;
		philo.common = common;
		if (i == 0 && common->nbr_of_meals > 0)
			food_pid = monitor_meals(&philo);
		philo_pid[i] = fork();
		if (philo_pid[i] == 0)
		{
			banquet(&philo);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
	return (remove_plates(common, philo_pid.data(), food_pid));
}
