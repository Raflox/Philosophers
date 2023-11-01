/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:34:06 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/31 20:49:47 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_config	*data(void)
{
	static t_config	data;

	return (&data);
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 != 0)
	{
		think(philo);
		ft_usleep(50);
	}
	while (philo->n_meal != data()->total_meals && !grim_reaper(philo) && !data()->is_dead)
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
