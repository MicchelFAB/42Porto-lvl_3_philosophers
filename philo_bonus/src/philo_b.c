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

int	main(int ac, char **av)
{
	t_common	common;

	if (check_args(ac, av, &common) == -1)
		return (ft_puterr("Error: Invalid arguments.\n"));
	if (putting_fancy_table(&common) == -1)
		return (ft_puterr("Error: Failed to put the table.\n"));
	if (start_fancy_event(&common) == -1)
		return (ft_puterr("Error: Failed to create processes.\n"));
	free(common.philo);
	return (0);
}

int	check_args(int ac, char **av, t_common *args)
{
	if (ac < 5 || ac > 6)
	{
		ft_puterr("Arguments should be: [nbr_of_philo] [time_to_die] [time_to_eat]\
		 [time_to_sleep] *optional: [nbr_of_times_each_philo_must_eat]");
		return (-1);
	}
	args->philo_on_table = ft_atol_philo(av[1]);
	args->death_clock = ft_atol_philo(av[2]);
	args->eat_delay = ft_atol_philo(av[3]) * 1000;
	args->sleeping_time = ft_atol_philo(av[4]) * 1000;
	if (args->philo_on_table < 1 || args->death_clock == -1 || args->eat_delay
		== -1 || args->sleeping_time == -1)
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

int	putting_fancy_table(t_common *common)
{
	int		i;
	int		err_flag;
	char	*str;

	i = -1;
	err_flag = 0;
	common->philo = malloc(sizeof(t_philo) * common->philo_on_table);
	if (!common->philo)
		return (-1);
	while (++i < common->philo_on_table)
	{
		str = get_philo_name("/lst_meal", i);
		sem_unlink(str);
		common->philo[i].lst_meal = sem_open(str, O_CREAT | O_EXCL, 0644, 1);
		free(str);
		if (common->philo[i].lst_meal == SEM_FAILED)
			err_flag++;
	}
	err_flag += putting_fancy_cutlery(common);
	if (err_flag)
		return (tbl_unavail(common));
	return (0);
}

int	putting_fancy_cutlery(t_common *silver)
{
	sem_unlink("/forks");
	sem_unlink("/print_status");
	sem_unlink("/chew");
	sem_unlink("/session_end");
	silver->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			silver->philo_on_table);
	silver->print_status = sem_open("/print_status", O_CREAT | O_EXCL, 0644, 1);
	silver->chew = sem_open("/chew", O_CREAT | O_EXCL,
			0644, 0);
	silver->session_end = sem_open("/session_end", O_CREAT | O_EXCL, 0644, 0);
	if (silver->forks == SEM_FAILED || silver->print_status == SEM_FAILED
		|| silver->chew == SEM_FAILED || silver->session_end == SEM_FAILED)
		return (1);
	return (0);
}

int	start_fancy_event(t_common *common)
{
	int			i;
	pid_t		*philo_pid;
	pid_t		food_pid;
	t_philo		philo;

	philo_pid = malloc(sizeof(*philo_pid) * common->philo_on_table);
	if (!philo_pid)
		return (-1);
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
			free(philo_pid);
			banquet(&philo);
		}
		usleep(30);
	}
	return (remove_plates(common, philo_pid, food_pid));
}
