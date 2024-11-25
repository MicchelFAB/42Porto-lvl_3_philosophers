/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/14 19:56:46 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

# include <iostream>
# include <vector>
# include <array>
# include <chrono>
# include <thread>
# include <mutex>
# include <semaphore>
# include <condition_variable>

class Common
{
public:
	int				nbr_of_meals;
	int				philo_on_table;
	std::binary_semaphore	chew;
	std::binary_semaphore	forks;
	std::binary_semaphore	session_end;
	std::binary_semaphore	print_status;
	std::chrono::time_point<std::chrono::steady_clock>	begin;
	std::chrono::milliseconds	eat_delay;
	std::chrono::milliseconds	death_clock;
	std::chrono::milliseconds	sleeping_time;
	std::vector<Philo>	philo;
};

class Philo
{
public:
	int				id;
	int				eating;
	std::binary_semaphore	lst_meal;
	std::chrono::time_point<std::chrono::steady_clock>	time_lst_meal;
	std::thread		p_thread;
	Common*			common;
};

std::chrono::time_point<std::chrono::steady_clock>	get_now();
unsigned long	ft_atol_philo(char *str);
void			ft_putnbr(long long n);
int				main(int ac, char **av);
int				check_args(int ac, char **av, Common *args);
int				putting_fancy_table(Common *common);
int				putting_fancy_cutlery(Common *silver);
int				start_fancy_event(Common *common);
char			*ft_itoa_philo(int nbr);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_puterr(char *str);
void			serving(Philo *philo);
void			banquet(Philo *philo);
pid_t			monitor_meals(void *ph);
void			*monitor_death(void *ph);
int				remove_plates(Common *dishes, pid_t *pid, pid_t pid2);
int				tbl_unavail(Common *setup);
void			checking_table(Philo *philo, const char *status);
char			*get_philo_name(char *s, int n);
void			unlink_tableware(Common *setup);
void			leaving_tbl(Philo *philo, const char *str);

#endif
