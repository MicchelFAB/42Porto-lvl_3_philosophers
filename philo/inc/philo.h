/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/07 18:49:15 by mamaral-         ###   ########.fr       */
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
	int				fork[2];
	long long		lst_meal;
	pthread_t		p_thread;
	struct s_common	*common;
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
	long long		begin;
	pthread_mutex_t	*fork_hold;
	pthread_mutex_t	print_status;
	pthread_mutex_t	chew;
	pthread_mutex_t	session_end;
	t_philo			*philo;
}					t_common;

int			ft_atoi_philo(char *str);
void		clean_table(t_common *common);
long long	queued(t_philo *philo, long long end);
void		*symposium(void *group);
void		checking_table(t_philo *philo, const char *status);
long long	get_now(void);
int			remove_plates(t_philo *philo, int dinner_end);
int			check_args(int ac, char **av, t_common *args);
int			putting_the_table(t_common *setup);
int			putting_the_cutlery(t_common *silverware);
int			start_event(t_common *data);
void		waiter(t_common *guests);

#endif