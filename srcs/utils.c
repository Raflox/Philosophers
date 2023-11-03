/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:39:09 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/31 20:50:23 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' && (str[i + 1] >= 48 && str[i + 1] <= 57))
		i++;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res);
}

void	ft_usleep(int time, t_philo *philo)
{
	int	start;

	(void)philo;
	start = get_time();
	while ((get_time() - start) < time)
	{
		if (grim_reaper(philo))
			return ;
		usleep(500);
	}
}

void	lock_fork(int fork, t_philo *philo)
{
	while (!grim_reaper(philo) && !death_check())
	{
		pthread_mutex_lock(&philo->forks[fork].hold);
		if (philo->forks[fork].status == 1)
		{
			philo->forks[fork].status = 0;
			logger("has taken a fork", PURPLE, philo);
			pthread_mutex_unlock(&philo->forks[fork].hold);
			break ;
		}
		pthread_mutex_unlock(&philo->forks[fork].hold);
	}
}

void	unlock_forks(int fork, t_philo *philo)
{
	while (!grim_reaper(philo))
	{
		pthread_mutex_lock(&philo->forks[fork].hold);
		if (philo->forks[fork].status == 0)
		{
			philo->forks[fork].status = 1;
			pthread_mutex_unlock(&philo->forks[fork].hold);
			break ;
		}
		pthread_mutex_unlock(&philo->forks[fork].hold);
	}
}

int	death_check(void)
{
	pthread_mutex_lock(&data()->death);
	if (data()->is_dead)
	{
		pthread_mutex_unlock(&data()->death);
		return (1);
	}
	pthread_mutex_unlock(&data()->death);
	return (0);
}
