/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:09:42 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/31 19:00:27 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clean(int mode)
{
	if (mode == 1)
	{
		free(data()->philos->forks);
		free(data()->philos);
	}
	else if (mode == 2)
		free(data()->philos);
}

void	error(const char *msg, int mode)
{
	if (mode == 1)
		clean(1);
	else if (mode == 2)
		clean(2);
	printf("%s\n", msg);
}
