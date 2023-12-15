/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbl_gov.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaral- <mamaral-@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:39:26 by mamaral-          #+#    #+#             */
/*   Updated: 2023/12/15 13:38:20 by mamaral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	tbl_unavail(t_common *setup)
{
	unlink_tableware(setup);
	free(setup->philo);
	return (-1);
}

void	leaving_tbl(t_philo *philo, const char *str)
{
	sem_wait(philo->common->print_status);
	if (*str == ' ')
	{
		ft_putnbr(get_now() - philo->common->begin);
		write(1, "\t", 1);
		ft_putnbr(philo->id + 1);
	}
	write(1, str, ft_strlen(str));
	sem_post(philo->common->session_end);
}

void	checking_table(t_philo *philo, const char *status)
{
	sem_wait(philo->common->print_status);
	ft_putnbr(get_now() - philo->common->begin);
	write(1, "\t", 1);
	ft_putnbr(philo->id + 1);
	write(1, status, ft_strlen(status));
	sem_post(philo->common->print_status);
}

char	*get_philo_name(char *s, int n)
{
	size_t	size;
	char	*str;
	char	*tmp;

	tmp = ft_itoa_philo(n);
	if (!tmp)
		return (NULL);
	size = ft_strlen(s) + ft_strlen(tmp);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	ft_strlcpy(str, s, size);
	ft_strlcpy(str + ft_strlen(s), tmp, size);
	free(tmp);
	return (str);
}

void	unlink_tableware(t_common *setup)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < setup->philo_on_table)
	{
		str = get_philo_name("/lst_meal", i);
		sem_unlink(str);
		free(str);
	}
	sem_unlink("/forks");
	sem_unlink("/print_status");
	sem_unlink("/chew");
	sem_unlink("/session_end");
}
