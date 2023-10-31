/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:34:06 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/31 16:47:22 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_config	*data(void)
{
	static t_config	data;

	return (&data);
}

int	grim_reaper(t_philo *philo)
{
	if (get_time() - philo->last_meal > data()->t_die)
	{
		logger("is pepsi", RED, philo);
		return (1);
	}
	return (0);
}

void	lock_fork(int fork, t_philo *philo)
{
	while (true)
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
	while (true)
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

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 != 0)
		ft_usleep(1);
	while (philo->n_meal != data()->total_meals && !grim_reaper(philo))
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	if (check_args(ac, av))
	{
		data_init(av);
		threads_init();
	}
}
