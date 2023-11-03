/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:45:49 by rafilipe          #+#    #+#             */
/*   Updated: 2023/10/26 13:02:58 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	logger(const char *msg, char *color, t_philo *philo)
{
	pthread_mutex_lock(&data()->log);
	printf("%s%d %d %s\n", color, time_elapsed(), philo->id, msg);
	pthread_mutex_unlock(&data()->log);
}
