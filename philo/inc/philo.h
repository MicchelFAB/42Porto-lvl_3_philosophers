/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/11/22 12:34:45 by mamaral-         ###   ########.fr       */
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

typedef struct s_common
{
	int				philo_on_table;
	int				death_clock;
	int				eat_delay;
	int				sleeping_time;
	int				number_of_meals;
	struct timeval	begin;
}				t_common;

typedef struct s_philo
{
	int				id;
	int				eating;
	int				meals;
	int				*dead;
	int				*alive_guest;
	struct timeval	lst_meal;
	pthread_mutex_t	*fork;
	pthread_mutex_t	p_dead;
	pthread_t		p_thread;
	t_common		common;
}					t_philo;

int	ft_atoi_philo(char *str);
void	clean_table(t_philo *group, t_common common);
int queued(t_philo *philo, struct timeval start, long wait_time);
long	elapsed_time(struct timeval a, struct timeval b);

#endif