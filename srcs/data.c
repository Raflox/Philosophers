/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:51:50 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/31 19:11:59 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	threads_init(void)
{
	int		i;

	i = -1;
	while (++i < data()->philos_nb)
	{
		if (pthread_create(&data()->philos[i].philo, NULL, \
			&routine, &data()->philos[i]))
		{
			error("Error: Thread Creation", 1);
			return (0);
		}
	}
	i = -1;
	while (++i < data()->philos_nb)
	{
		if (pthread_join(data()->philos[i].philo, NULL))
			error("Error: Thread Join", 1);
	}
	return (0);
}

t_fork	*forks_init(void)
{
	int		i;
	t_fork	*forks;

	forks = malloc(sizeof(t_fork) * data()->philos_nb);
	if (!forks)
		error("Error: Forks Malloc", 2);
	i = -1;
	while (++i < data()->philos_nb)
	{
		forks[i].status = 1;
		if (pthread_mutex_init(&forks[i].hold, NULL))
			return (NULL);
	}
	return (forks);
}

void	philos_init(void)
{
	int		i;
	t_fork	*forks;

	data()->philos = malloc(sizeof(t_philo) * data()->philos_nb);
	if (!data()->philos)
		error("Error: Philos Malloc", 0);
	forks = forks_init();
	if (!forks)
		error("Error: Forks Mutex", 1);
	i = -1;
	while (++i < data()->philos_nb)
	{
		data()->philos[i].forks = forks;
		data()->philos[i].id = i + 1;
		data()->philos[i].n_meal = 0;
		data()->philos[i].last_meal = get_time();
	}
}

void	data_init(char **av)
{
	data()->start_time = get_time();
	data()->philos_nb = ft_atoi(av[1]);
	data()->t_die = ft_atoi(av[2]);
	data()->t_eat = ft_atoi(av[3]);
	data()->t_sleep = ft_atoi(av[4]);
	if (av[5])
		data()->total_meals = ft_atoi(av[5]);
	else
		data()->total_meals = INT_MAX;
	data()->is_dead = 0;
	pthread_mutex_init(&data()->log, NULL);
	pthread_mutex_init(&data()->death, NULL);
	philos_init();
}
