/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/14 13:43:58 by mamaral-         ###   ########.fr       */
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

# define TOOK_FORK 0
# define IS_EATING 1
# define IS_SLEEPING 2
# define IS_THINKING 3

# define HAS_DIED 0
# define ARE_SATIATED 1

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
	struct s_philo	*philo;
}					t_common;

typedef struct s_philo
{
	pthread_t		p_thread;
	int				id;
	int				eating;
	long long		time_lst_meal;
	sem_t			*lst_meal;
	t_common		*common;
}					t_philo;


long long	ft_atol(const char *str);
long long	get_now(void);
void			ft_putnbr(long long n);
unsigned long	ft_atol_philo(char *str);
int		main(int ac, char **av);
int	check_args(int ac, char **av, t_common *args);
int		putting_fancy_table(t_common *common);
int	putting_fancy_cutlery(t_common *silver);
int	start_fancy_event(t_common *common);
char	*ft_itoa_philo(int nbr);
size_t ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int ft_puterr(char *str);
void	serving(t_philo *philo);
void	banquet(t_philo *philo);
pid_t	monitor_meals(void *ph);
void	*monitor_death(void *ph);
int	remove_plates(t_common *dishes, pid_t *pid, pid_t pid2);
int	tbl_unavail(t_common *setup);
void	checking_table(t_philo *philo, const char *status);
char	*get_philo_name(char *s, int n);
void	unlink_tableware(t_common *setup);
void	leaving_tbl(t_philo *philo, const char *str);



#endif