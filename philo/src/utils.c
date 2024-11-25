/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 18:10:15 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

int	ft_atoi_philo(char *str)
{
	int	r;

	r = 0;
	if (str == NULL || str[0] == '-')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (r);
}

void	clean_table(Common *common)
{
	int	i;

	i = -1;
	while (++i < common->philo_on_table)
		common->philo[i].p_thread.join();
	i = -1;
	while (++i < common->philo_on_table)
		common->fork_hold[i].unlock();
	free(common->philo);
	free(common->fork_hold);
	common->print_status.unlock();
	common->chew.unlock();
	common->session_end.unlock();
}

void	checking_table(Philo *philo, const char *status)
{
	philo->common->print_status.lock();
	if (!remove_plates(philo, NO))
	{
		std::cout << queued(philo, -1) - philo->common->begin << "\t";
		std::cout << philo->id << status;
	}
	if (status[0] == 'N')
		std::cout << status;
	else if (status[1] == 'd')
	{
		std::cout << queued(philo, -1) - philo->common->begin << "\t";
		std::cout << philo->id << status;
	}
	philo->common->print_status.unlock();
}

std::chrono::time_point<std::chrono::steady_clock> queued(Philo *philo, std::chrono::milliseconds end)
{
	auto begin = std::chrono::steady_clock::now();
	if (end == std::chrono::milliseconds(-1))
		return begin;
	else
	{
		auto now = begin;
		while (!remove_plates(philo, NO) && (now - begin) < end)
		{
			now = std::chrono::steady_clock::now();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
	return std::chrono::time_point<std::chrono::steady_clock>();
}

int	remove_plates(Philo *philo, int dinner_end)
{
	philo->common->session_end.lock();
	if (dinner_end || philo->common->finish_flag)
	{
		if (dinner_end)
			philo->common->finish_flag = 1;
		philo->common->session_end.unlock();
		return (1);
	}
	philo->common->session_end.unlock();
	return (0);
}
