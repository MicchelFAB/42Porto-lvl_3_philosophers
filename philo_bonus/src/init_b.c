/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:06:51 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/13 16:08:03 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	main(int ac, char **av)
{
	t_common	common;

	if (check_args(ac, av, &common) == -1)
		return (printf("Error: Invalid arguments.\n"));
	if (putting_the_table(&common) == -1)
		return (printf("Error: Failed to put the table.\n"));
	if (start_event(&common) == -1)
		return (printf("Error: Failed to create thread.\n"));
	return (0);
}

int	check_args(int ac, char **av, t_common *args)
{
	if (ac < 5 || ac > 6)
	{
		printf("Arguments should be: [nbr_of_philo] [time_to_die] [time_to_eat]\
		 [time_to_sleep] *optional: [nbr_of_times_each_philo_must_eat]");
		return (-1);
	}
	args->philo_on_table = ft_atol_philo(av[1]);
	args->death_clock = ft_atol_philo(av[2]);
	args->eat_delay = ft_atol_philo(av[3]);
	args->sleeping_time = ft_atol_philo(av[4]);
	if (args->philo_on_table == -1 || args->death_clock == -1 || args->eat_delay
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

char	*get_philo_name(char *s, int n)
{
	size_t	size;
	char	*str;
	char	*tmp;

	tmp = ft_itoa_philo(n);
	if (!tmp)
		return (NULL);
	size = ft_strlen(s) + ft_strlen(tmp);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	ft_strlcpy(str, s, size);
	ft_strlcpy(str + ft_strlen(s), tmp, size);
	free(tmp);
	return (str);
}

void	unlink_tableware(t_common *setup)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < setup->philo_on_table)
	{
		str = get_philo_name("/lst_meal", i);
		sem_unlink(str);
		free(str);
	}
	sem_unlink("/forks");
	sem_unlink("/print_status");
	sem_unlink("/chew");
	sem_unlink("/session_end");
}

int	tbl_unavail(t_common *setup)
{
	unlink_tableware(setup);
	free(setup->philo);
	return (-1);
}

int	putting_the_table(t_common *setup)
{
	int		i;
	int		chk_err;
	char	*str;

	i = -1;
	chk_err = 0;
	setup->philo = malloc(sizeof(t_philo) * setup->philo_on_table);
	if (!setup->philo)
		return (-1);
	while (++i < setup->philo_on_table)
	{
		str = get_philo_name("/lst_meal", i);
		setup->philo[i].lst_meal = sem_open(str, O_CREAT | O_EXCL, 0644, 1);
		free(str);
		if (setup->philo[i].lst_meal == SEM_FAILED)
			chk_err++;
	}
	if (chk_err || putting_the_cutlery(setup) == -1)
		return (tbl_unavail(setup));
	return (0);
}

int	putting_the_cutlery(t_common *silverware)
{
	silverware->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			silverware->philo_on_table);
	silverware->print_status = sem_open("/print_status", O_CREAT | O_EXCL,
			0644, 1);
	silverware->chew = sem_open("/chew", O_CREAT | O_EXCL, 0644, 0);
	silverware->session_end = sem_open("/session_end", O_CREAT | O_EXCL,
			0644, 0);
	if (silverware->forks == SEM_FAILED || silverware->print_status
		== SEM_FAILED || silverware->chew == SEM_FAILED
		|| silverware->session_end == SEM_FAILED)
		return (-1);
	return (0);
}

void	leaving_tbl(t_philo *philo, const char *str)
{
	sem_wait(philo->common->print_status);
	if (*str == 'd')
		printf("%lld %d %s\n", get_now() - philo->common->begin, philo->id,
		 str);
	else if (*str == 'N')
		printf("%s\n", "Number of meals reached!");
	sem_post(philo->common->session_end);
}

void	*monitor_meals(void *ph)
{
	t_philo			*philo;
	int				count;

	philo = ph;
	count = 0;
	while (1)
	{
		sem_wait(philo->common->chew);
		if (++count >= philo->common->philo_on_table)
		{
			leaving_tbl(ph, "Number of meals reached!");
			exit(0);
		}
	}
}

void	*philo_life(void *ph)
{
	t_philo			*philo;
	long long		timestamp;

	philo = ph;
	timestamp = get_now();
	while (1)
	{
		sem_wait(philo->lst_meal);
		if (timestamp - philo->time_lst_meal > philo->common->death_clock)
		{
			sem_post(philo->lst_meal);
			leaving_tbl(ph, "died");
			return (NULL);
		}
		sem_post(philo->lst_meal);
		usleep(10);
	}
}

void	serving(t_philo *philo)
{
	sem_wait(philo->common->forks);
	checking_table(philo, "has taken a fork");
	sem_wait(philo->common->forks);
	checking_table(philo, "has taken a fork");
	checking_table(philo, "is eating");
	sem_wait(philo->lst_meal);
	philo->time_lst_meal = get_now();
	sem_post(philo->lst_meal);
	usleep(philo->common->eat_delay);
	sem_post(philo->common->forks);
	sem_post(philo->common->forks);
	if (++philo->eating == philo->common->nbr_of_meals)
		sem_post(philo->common->chew);
}

void	invite_philo(t_philo **invitecard)
{
	char *str;
	
	if ((*invitecard)->id == (*invitecard)->common->philo_on_table)
		(*invitecard)->id_next_philo = 0;
	else
		(*invitecard)->id_next_philo = (*invitecard)->id + 1;
	str = get_philo_name("/lst_meal", (*invitecard)->id);
	(*invitecard)->lst_meal = sem_open(str, 0644);
	free(str);
	(*invitecard)->eating = 0;
	(*invitecard)->common->forks = sem_open("/forks", 0644);
	(*invitecard)->common->print_status = sem_open("/print_status", 0644);
	(*invitecard)->common->chew = sem_open("/chew", 0644);
	(*invitecard)->common->session_end = sem_open("/session_end", 0644);
	(*invitecard)->time_lst_meal = (*invitecard)->common->begin;
}

void	table_for_one(t_common *common)
{
	checking_table(&common->philo[0], "has taken a fork");
	usleep(common->death_clock);
	leaving_tbl(&common->philo[0], "died");
	// exit (0);
}

void	banquet(t_philo *group)
{
	invite_philo(&group);
	pthread_create(&group->p_thread, NULL, philo_life, group);
	while(1)
	{
		if (group->common->philo_on_table == 1)
		{
			table_for_one(group->common);
			break;
		}
		serving(group);
		checking_table(group, "is sleeping");
		usleep(group->common->sleeping_time);
		checking_table(group, "is thinking");
	}
}
	// 	usleep(philo->common->eat_delay * 1000);
	// while (1)
	// {
	// 	if (philo->common->philo_on_table == 1)
	// 		return (table_for_one(philo->common));
	// 	serving(philo);
	// 	if (philo->eating == philo->common->nbr_of_meals)
	// 		return (0);
	// 	if (remove_plates(philo, NO))
	// 		return (0);
	// 	checking_table(philo, "is sleeping");
	// 	queued(philo, philo->common->sleeping_time);
	// 	checking_table(philo, "is thinking");
	// 	if (philo->common->philo_on_table % 2 != 0
	// 		&& philo->common->philo_on_table <= 127)
	// 		queued(philo, philo->common->eat_delay);
	// }

int	remove_plates(t_common *dishes, pid_t *pid, pid_t pid2)
{
	int	i;

	sem_wait(dishes->session_end);
	i = -1;
	while (++i < dishes->philo_on_table)
		kill(pid[i], SIGKILL);
	if(dishes->philo_on_table > 0)
		kill(pid2, SIGKILL);
	unlink_tableware(dishes);
	free(dishes->philo);
	free(dishes);
	free(pid);
	return (0);
}

int	start_event(t_common *data)
{
	int			i;
	pid_t		*philo_pid;
	pid_t		pid2;
	t_philo		philo;

	philo_pid = malloc(sizeof(*philo_pid) * data->philo_on_table);
	if (!philo_pid)
		return (-1);
	i = -1;
	while (++i < data->philo_on_table)
	{
		philo.id = i + 1;
		philo.common = data->philo->common;
		if (i == 0 && data->philo_on_table > 0)
			if (!(pid2 = fork()))
				monitor_meals(&philo);
		philo_pid[i] = fork();
		if (philo_pid[i] == 0)
		{
			free(philo_pid);
			banquet(&philo);
		}
		usleep(30);
	}
	return (remove_plates(data, philo_pid, pid2));
}
