/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:06:19 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/13 14:57:20 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

// int	table_service(t_philo *philo)
// {
// 	long long	now;

// 	now = queued(philo, -1);
// 	pthread_mutex_lock(&philo->common->chew);
// 	if ((now - philo->lst_meal) >= philo->common->death_clock)
// 	{
// 		remove_plates(philo, YES);
// 		checking_table(philo, "died");
// 		pthread_mutex_unlock(&philo->common->chew);
// 		return (1);
// 	}
// 	else if (philo->common->nbr_of_meals > 0 && philo->eating >= philo
// 		->common->nbr_of_meals)
// 	{
// 		philo->common->tummy_hurts++;
// 		if (philo->common->tummy_hurts >= philo->common->philo_on_table)
// 		{
// 			remove_plates(philo, YES);
// 			checking_table(philo, "A");
// 			pthread_mutex_unlock(&philo->common->chew);
// 			return (1);
// 		}
// 	}
// 	pthread_mutex_unlock(&philo->common->chew);
// 	return (0);
// }

// void	waiter(t_common *guests)
// {
// 	int	i;
// 	int	meals;

// 	meals = 1;
// 	while (meals)
// 	{
// 		i = -1;
// 		guests->tummy_hurts = 0;
// 		while (++i < guests->philo_on_table)
// 		{
// 			if (meals && table_service(&guests->philo[i]))
// 				meals = 0;
// 		}
// 		usleep(10);
// 	}
// 	clean_table(guests);
// }
