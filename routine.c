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

#include "philo.h"

void	eat(t_philo	*philo)
{
	int	l_fork;
	int	r_fork;

	l_fork = philo->id - 1;
	r_fork = (l_fork + 1) % data()->philos_nb;
	lock_fork(l_fork, philo);
	lock_fork(r_fork, philo);
	philo->last_meal = get_time();
	logger("is eating", GREEN, philo);
	ft_usleep(data()->t_eat);
	philo->n_meal++;
	unlock_forks(r_fork, philo);
	unlock_forks(l_fork, philo);

}

void	rest(t_philo *philo)
{
	logger("is sleeping", ORANGE, philo);
	ft_usleep(data()->t_sleep);
}

void	think(t_philo *philo)
{
	logger("is thinking", YELLOW, philo);
}

int	grim_reaper(t_philo *philo)
{
	if (get_time() - philo->last_meal > data()->t_die)
	{
		logger("died", RED, philo);
		pthread_mutex_lock(&data()->death);
		data()->is_dead = 1;
		pthread_mutex_unlock(&data()->death);
		return (1);
	}
	return (0);
}