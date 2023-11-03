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

#include "../include/philo.h"

t_config	*data(void)
{
	static t_config	data;

	return (&data);
}

int	main(int ac, char **av)
{
	if (check_args(ac, av))
	{
		data_init(av);
		threads_init();
	}
	//printf("AQUI\n");
	clean(1);
}
