/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:52:49 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 16:40:01 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <iostream>
# include <vector>
# include <array>
# include <chrono>
# include <thread>
# include <mutex>
# include <semaphore>
# include <condition_variable>

# define YES 1
# define NO 0

class Philo
{
public:
	int				id;
	int				eating;
	int				fork[2];
	std::chrono::time_point<std::chrono::steady_clock>	lst_meal;
	std::thread		p_thread;
	Common*			common;
};

class Common
{
public:
	int				philo_on_table;
	std::chrono::milliseconds	death_clock;
	std::chrono::milliseconds	eat_delay;
	std::chrono::milliseconds	sleeping_time;
	int				nbr_of_meals;
	int				tummy_hurts;
	int				finish_flag;
	std::chrono::time_point<std::chrono::steady_clock>	begin;
	std::vector<std::mutex>	fork_hold;
	std::mutex		print_status;
	std::mutex		chew;
	std::mutex		session_end;
	std::vector<Philo>	philo;
};

int			ft_atoi_philo(char *str);
void		clean_table(Common *common);
std::chrono::time_point<std::chrono::steady_clock>	queued(Philo *philo, std::chrono::milliseconds end);
void		*symposium(void *group);
void		checking_table(Philo *philo, const char *status);
std::chrono::time_point<std::chrono::steady_clock>	get_now(void);
int			remove_plates(Philo *philo, int dinner_end);
int			check_args(int ac, char **av, Common *args);
int			putting_the_table(Common *setup);
int			putting_the_cutlery(Common *silverware);
int			start_event(Common *data);
void		waiter(Common *guests);
size_t		ft_strlen(const char *s);
int			ft_puterr(char *str);
void		ft_putnbr(long long n);
char		*ft_itoa_philo(int nbr);

#endif
