/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbl_gov.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 19:27:13 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

int	tbl_unavail(Common *setup)
{
	unlink_tableware(setup);
	free(setup->philo);
	return (-1);
}

void	leaving_tbl(Philo *philo, const char *str)
{
	philo->common->print_status.acquire();
	if (*str == ' ')
	{
		std::cout << get_now() - philo->common->begin << "\t" << philo->id + 1;
	}
	std::cout << str;
	philo->common->session_end.release();
}

void	checking_table(Philo *philo, const char *status)
{
	philo->common->print_status.acquire();
	std::cout << get_now() - philo->common->begin << "\t" << philo->id + 1 << status;
	philo->common->print_status.release();
}

char	*get_philo_name(char *s, int n)
{
	size_t	size;
	char	*str;
	char	*tmp;

	tmp = ft_itoa_philo(n);
	if (!tmp)
		return (NULL);
	size = std::strlen(s) + std::strlen(tmp);
	str = (char*)malloc(sizeof(char) * (size + 1));
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	std::strncpy(str, s, size);
	std::strncpy(str + std::strlen(s), tmp, size);
	free(tmp);
	return (str);
}

void	unlink_tableware(Common *setup)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < setup->philo_on_table)
	{
		str = get_philo_name("/lst_meal", i);
		sem_close(setup->philo[i].lst_meal);
		sem_unlink(str);
		free(str);
	}
	sem_close(setup->forks);
	sem_close(setup->print_status);
	sem_close(setup->chew);
	sem_close(setup->session_end);
	sem_unlink("/forks");
	sem_unlink("/print_status");
	sem_unlink("/chew");
	sem_unlink("/session_end");
}
