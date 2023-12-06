/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/04 17:13:03 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>

# define YES 1
# define NO 0

typedef struct s_philo
{
	int				id;
	int				eating;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct timeval	lst_meal;
	struct s_common	*common;
	pthread_t		p_thread;
}					t_philo;

typedef struct s_common
{
	int				philo_on_table;
	int				death_clock;
	int				eat_delay;
	int				sleeping_time;
	int				number_of_meals;
	int				tummy_hurts;
	int				finish_flag;
	struct timeval	begin;
	t_philo			*philo;
	pthread_mutex_t	*fork_hold;
	pthread_mutex_t	print_status;
	pthread_mutex_t	chew;
	pthread_mutex_t	session_end;
}					t_common;

int	ft_atoi_philo(char *str);
// void	clean_table(t_philo *group, t_common common);
void	clean_table(t_common *common);
void	queued(t_philo *philo, long long end);
// int queued(t_philo *philo, struct timeval start, long wait_time);
long	elapsed_time(struct timeval a, struct timeval b);
void *symposium(void *group);
void	checking_table(t_philo *philo, const char *status);
long long	get_now(void);
int	remove_plates(t_philo *philo, int dinner_end);

#endif