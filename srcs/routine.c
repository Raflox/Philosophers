/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:45:08 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/31 20:49:49 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo	*philo)
{
	int	l_fork;
	int	r_fork;

	l_fork = philo->id - 1;
	r_fork = (l_fork + 1) % data()->philos_nb;
	lock_fork(l_fork, philo);
	lock_fork(r_fork, philo);
	if (death_check())
		return ;
	philo->last_meal = get_time();
	logger("is eating", GREEN, philo);
	ft_usleep(data()->t_eat, philo);
	philo->n_meal++;
	unlock_forks(r_fork, philo);
	unlock_forks(l_fork, philo);
}

void	rest(t_philo *philo)
{
	logger("is sleeping", ORANGE, philo);
	ft_usleep(data()->t_sleep, philo);
}

void	think(t_philo *philo)
{
	logger("is thinking", YELLOW, philo);
}

int	grim_reaper(t_philo *philo)
{
	pthread_mutex_lock(&data()->death);
	if (get_time() - philo->last_meal >= data()->t_die)
	{
		if (data()->is_dead == 0)
		{
			logger("died", RED, philo);
			data()->is_dead = 1;
			pthread_mutex_unlock(&data()->death);
			return (1);
		}
	}
	pthread_mutex_unlock(&data()->death);
	return (0);
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 != 0)
	{
		think(philo);
		ft_usleep(10, philo);
	}
	while (!grim_reaper(philo) && philo->n_meal != data()->total_meals)
	{
		eat(philo);
		if (death_check())
			break ;
		rest(philo);
		if (death_check())
			break ;
		think(philo);
	}
	return (NULL);
}
