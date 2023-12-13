/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/13 15:30:18 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/time.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>

# define YES 1
# define NO 0

typedef struct s_philo
{
	pthread_t		p_thread;
	int				id;
	int				id_next_philo;
	int				eating;
	long long		time_lst_meal;
	sem_t			*lst_meal;
	struct s_common	*common;
}					t_philo;

typedef struct s_common
{
	int				philo_on_table;
	int				nbr_of_meals;
	long long		begin;
	long long		death_clock;
	long long		eat_delay;
	long long		sleeping_time;
	sem_t	*forks;
	sem_t	*print_status;
	sem_t	*chew;
	sem_t	*session_end;
	t_philo			*philo;
	// int				tummy_hurts;
	// int				finish_flag;
}					t_common;

unsigned long			ft_atol_philo(char *str);
char					*ft_itoa_philo(int nbr);
size_t ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

void		clean_table(t_common *common);
// long long	queued(t_philo *philo, long long end);
void		*symposium(void *group);
void		checking_table(t_philo *philo, const char *status);
long long	get_now(void);
// int			remove_plates(t_philo *philo, int dinner_end);
int			check_args(int ac, char **av, t_common *args);
int			putting_the_table(t_common *setup);
int			putting_the_cutlery(t_common *silverware);
int			start_event(t_common *data);
void		waiter(t_common *guests);

#endif